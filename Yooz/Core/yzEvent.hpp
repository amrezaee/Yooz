#pragma once

#include <Core/yzDelegate.hpp>
#include <Core/yzLogger.hpp>

#include <yzSTD.hpp>

namespace yz
{
template<typename... SigArgs>
class Event
{
public:
	using signature_type = void(SigArgs...);
	using handler_type   = Delegate<signature_type>;
	using container_type = std::vector<handler_type>;
	using this_type      = Event<SigArgs...>;

	Event()  = default;
	~Event() = default;

	Event(const this_type&) {}

	this_type& operator=(const this_type& rhs)
	{
		if(this != &rhs)
			Clear();
		return *this;
	}

	Event(this_type&& other): m_handlers(std::move(other.m_handlers)) {}

	this_type& operator=(this_type&& other)
	{
		if(this != &other)
			m_handlers = std::move(other.m_handlers);
		return *this;
	}

	inline void Swap(this_type& other) { std::swap<this_type>(*this, other); }

	// Romoves all handlers.
	void Clear()
	{
		if(!m_handlers.empty())
			m_handlers.clear();
	}

	// Adds a new handler.
	template<typename... Args>
	void Add(Args&&... args)
	{
		m_handlers.emplace_back(std::forward<Args>(args)...);
	}

	// add the handler n times
	template<typename... Args>
	void AddN(std::uint32_t n, Args&&... args)
	{
		for(std::uint32_t i = 0u; i < n; ++i)
			m_handlers.emplace_back(std::forward<Args>(args)...);
	}

	// Removes a handler.
	// if there are more than one copy of a handler, use RemoveAll.
	template<typename... Args>
	void Remove(Args&&... args)
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

	// removes all copies of a handler.
	template<typename... Args>
	void RemoveAll(Args&&... args)
	{
		handler_type toremove = handler_type(std::forward<Args>(args)...);
		const auto it = std::remove(m_handlers.begin(), m_handlers.end(), toremove);

		if(it != m_handlers.end())
			m_handlers.erase(it, m_handlers.cend());
		else
			YZ_WARN("No such event handler found.");
	}

	// Raise event. calls all handlers with specified parameters.
	template<typename... Args>
	inline void Raise(Args... args)
	{
		operator()(args...);
	}

	// same as Raise
	template<typename... Args>
	void operator()(Args... args) const
	{
		if(m_handlers.empty())
		{
			YZ_WARN("Event's handler list is empty.");
			return;
		}
		for(const auto& i : m_handlers) i(args...);
	}

	inline bool operator==(const this_type& rhs) const
	{
		return m_handlers == rhs.m_handlers;
	}

	inline bool operator!=(const this_type& rhs) const { return !operator==(rhs); }

private:
	container_type m_handlers;
};
}  // namespace yz
