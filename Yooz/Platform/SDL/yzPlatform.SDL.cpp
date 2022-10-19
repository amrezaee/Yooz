#include <platform/yzPlatform.hpp>

#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>

namespace yz
{
void Platform::Init()
{
	if(m_inited)
		return;

	YZ_SINFO("Platform initialization.");

	int code = SDL_Init(SDL_INIT_EVERYTHING);
	YZ_ASSERT(code == 0, SDL_GetError());

	SDL_SetHint(SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4, "1");

	m_name = SDL_GetPlatform();

	m_sse3    = SDL_HasSSE3();
	m_sse41   = SDL_HasSSE41();
	m_sse42   = SDL_HasSSE42();
	m_avx1    = SDL_HasAVX();
	m_avx2    = SDL_HasAVX2();
	m_avx512f = SDL_HasAVX512F();

	m_cpu_count       = static_cast<std::uint32_t>(SDL_GetCPUCount());
	m_cache_line_size = static_cast<std::uint32_t>(SDL_GetCPUCacheLineSize());
	m_ram_size        = static_cast<std::uint32_t>(SDL_GetSystemRAM());

	YZ_INFO("Platform: %s", m_name);
	YZ_INFO("#CPUs:    %u", m_cpu_count);
	YZ_INFO("L1 line:  %d bytes", m_cache_line_size);
	YZ_INFO("Ram size: %u Mib", m_ram_size);
	YZ_INFO("SSE3:     %s", m_sse3 ? "Supported" : "Not supported");
	YZ_INFO("SSE4.1:   %s", m_sse41 ? "Supported" : "Not supported");
	YZ_INFO("SSE4.2:   %s", m_sse42 ? "Supported" : "Not supported");
	YZ_INFO("AVX1:     %s", m_avx1 ? "Supported" : "Not supported");
	YZ_INFO("AVX2:     %s", m_avx2 ? "Supported" : "Not supported");
	YZ_INFO("AVX512F:  %s", m_avx512f ? "Supported" : "Not supported");

	m_inited = true;
}

void Platform::Shutdown()
{
	if(!m_inited)
		return;

	SDL_Quit();

	m_inited = false;
}

const char* Platform::GetPlatformName() const
{
	return m_name;
}

bool Platform::HasSSE3() const
{
	return m_sse3;
}
bool Platform::HasSSE41() const
{
	return m_sse41;
}
bool Platform::HasSSE42() const
{
	return m_sse42;
}
bool Platform::HasAVX1() const
{
	return m_avx1;
}
bool Platform::HasAVX2() const
{
	return m_avx2;
}
bool Platform::HasAVX512F() const
{
	return m_avx512f;
}

std::uint32_t Platform::GetCPUCount() const
{
	return m_cpu_count;
}
std::uint32_t Platform::GetRamSize() const
{
	return m_ram_size;
}
std::uint32_t Platform::GetCacheLineSize() const
{
	return m_cache_line_size;
}

std::uint64_t Platform::GetTime() const
{
	return SDL_GetTicks64();
}
}  // namespace yz
