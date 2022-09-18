#pragma once

#include <Core/yzBase.hpp>
#include <Graphics/yzGraphicsStates.hpp>

#include <yzStds.hpp>

namespace yz
{
class GraphicsParams
{
public:
	GraphicsParams() { Reset(); }

	void Reset()
	{
		m_window_handle = nullptr;
		m_fs_mode       = FullscreenMode::WINDOWED;
		m_msaa_level    = 0;
		m_vsync         = true;
	}

	std::uint32_t GetDefaultFPS() const { return m_default_fps; }

	Handle GetWindowHandle() const { return m_window_handle; }
	void   SetWindowHandle(Handle handle) { m_window_handle = handle; }

	FullscreenMode GetFullscreenMode() const { return m_fs_mode; }
	void SetFullscreenMode(FullscreenMode fsmode) { m_fs_mode = fsmode; }

	std::uint8_t GetMSAALevel() const { return m_msaa_level; }
	void         SetMSAALevel(std::uint8_t level) { m_msaa_level = level; }

	bool GetVsyncState() const { return m_vsync; }

private:
	const std::uint32_t m_default_fps = 60;
	Handle              m_window_handle;
	FullscreenMode      m_fs_mode;
	std::uint8_t        m_msaa_level;
	std::uint32_t       m_buffer_width;
	std::uint32_t       m_buffer_height;
	float               m_buffer_aspect_ratio;
	bool                m_vsync;
};
}  // namespace yz
