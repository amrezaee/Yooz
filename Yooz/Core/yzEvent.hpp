#pragma once

#include <yzpch.hpp>

#include <Core/yzDelegate.hpp>
#include <Core/yzLogger.hpp>
#include <Input/yzInputCodes.hpp>

namespace yz
{
enum class EventType
{
	None,

	Quit,
	Focus,
	Resize,

	KeyPress,
	KeyRelease,
	KeyText,

	MousePress,
	MouseRelease,
	MouseMove,
	MouseWheel
};

struct EventArg
{
	EventType type;

	union
	{
		int64_t  i64[2];
		uint64_t u64[2];

		double f64[2];
		float  f32[4];

		int32_t  i32[4];
		uint32_t u32[4];

		int16_t  i16[8];
		uint16_t u16[8];

		int8_t  i8[16];
		uint8_t u8[16];

		char c[16];
	};
};

class EventQueue
{
public:
	using handler_type            = Delegate<bool(const EventArg&)>;
	using handler_collection_type = std::vector<handler_type>;
	using queue_collection_type   = std::vector<EventArg>;

	EventQueue()  = default;
	~EventQueue() = default;

	EventQueue(const EventQueue&)            = default;
	EventQueue& operator=(const EventQueue&) = default;

	EventQueue(EventQueue&&)            = default;
	EventQueue& operator=(EventQueue&&) = default;

	// Romoves all handlers.
	void Reset()
	{
		ClearQueue();
		ClearHandlers();
	}

	void ClearQueue() { m_queue.clear(); }
	void ClearHandlers() { m_handlers.clear(); }

	void Push(const EventArg& arg) { m_queue.push_back(arg); }

	void Push(EventArg&& arg) { m_queue.push_back(arg); }

	template<typename... Args>
	void AddHandler(Args&&... args)
	{
		m_handlers.emplace_back(std::forward<Args>(args)...);
	}

	// Removes a handler.
	// if there are more than one copy of a handler, use RemoveAll.
	template<typename... Args>
	void RemoveHandler(Args&&... args)
	{
		auto end_it   = m_handlers.cend();
		auto begin_it = m_handlers.cbegin();

		auto found_it = std::find(begin_it, end_it,
		                          handler_type(std::forward<Args>(args)...));

		if(found_it != end_it)
			m_handlers.erase(found_it);
		else
			YZ_WARN("No such event handler found.");
	}

	// Constant raise.
	void CRaise() const
	{
		if(m_handlers.empty())
		{
			YZ_WARN("Event's handler list is empty.");
			return;
		}

		for(const auto& e : m_queue)
		{
			for(const auto& handler : m_handlers)
			{
				// if handler returns true it means that event is handled.
				// so, don't call other handlers.
				if(handler(e))
					break;
			}
		}
	}

	// Raise event and clear the queue.
	void Raise()
	{
		CRaise();
		ClearQueue();
	}

private:
	handler_collection_type m_handlers;
	queue_collection_type   m_queue;
};
}  // namespace yz
