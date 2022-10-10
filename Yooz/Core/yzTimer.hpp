#pragma once

#include <yzSTD.hpp>

namespace yz
{
class Timer
{
public:
	using clock_type     = std::chrono::steady_clock;
	using timepoint_type = std::chrono::time_point<clock_type>;
	using s_type         = std::chrono::duration<float>;
	using ms_type        = std::chrono::duration<float, std::milli>;
	using us_type        = std::chrono::duration<float, std::micro>;
	using ns_type        = std::chrono::duration<float, std::nano>;

	Timer() { Reset(); }

	void Reset()
	{
		m_start      = clock_type::now();
		m_is_stopped = false;
	}

	void Timer::Stop()
	{
		m_stop       = clock_type::now();
		m_is_stopped = true;
	}

	// elapsed time in second
	float Elapsed() const { return GetTime<s_type>(); }

	// elapsed time in millisecond
	float ElapsedMilli() const { return GetTime<ms_type>(); }

	// elapsed time in microsecond
	float ElapsedMicro() const { return GetTime<us_type>(); }

	// elapsed time in nanosecond
	float ElapsedNano() const { return GetTime<ns_type>(); }

private:
	template<typename T>
	inline float GetTime() const
	{
		return std::chrono::duration_cast<T>(
		               (m_is_stopped ? m_stop : clock_type::now()) - m_start)
		        .count();
	}

private:
	timepoint_type m_start;
	timepoint_type m_stop;
	bool           m_is_stopped {false};
};
}  // namespace yz
