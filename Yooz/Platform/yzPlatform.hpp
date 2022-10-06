#pragma once

#include <yzDeps.hpp>
#include <yzSTD.hpp>

namespace yz
{
class Platform
{
public:
	void Init();
	void Shutdown();

	const char* GetPlatformName() const;

	bool HasSSE3() const;
	bool HasSSE41() const;
	bool HasSSE42() const;
	bool HasAVX1() const;
	bool HasAVX2() const;
	bool HasAVX512F() const;

	std::uint32_t GetCPUCount() const;
	std::uint32_t GetRamSize() const;
	std::uint32_t GetCacheLineSize() const;

private:
	bool m_inited {false};

	const char* m_name {nullptr};
	// MMX, SSE and SSE2 is supported by default in all x86_64 CPUs
	// All ARMv8 CPUs support NEON
	bool m_sse3 {false};
	bool m_sse41 {false};
	bool m_sse42 {false};
	bool m_avx1 {false};
	bool m_avx2 {false};
	bool m_avx512f {false};

	std::uint32_t m_cpu_count {1};
	std::uint32_t m_ram_size {0};
	std::uint32_t m_cache_line_size {0};
};
}  // namespace yz
