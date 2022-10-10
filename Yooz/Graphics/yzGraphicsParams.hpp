#pragma once

#include <Core/yzBase.hpp>
#include <Graphics/yzGraphicsStates.hpp>
#include <Math/yzVector2.hpp>

#include <yzSTD.hpp>

namespace yz
{
class GraphicsParams
{
public:
	GraphicsParams();

	GraphicsParams(const GraphicsParams&)            = default;
	GraphicsParams& operator=(const GraphicsParams&) = default;

	GraphicsParams(GraphicsParams&&)            = default;
	GraphicsParams& operator=(GraphicsParams&&) = default;

	void Reset();

	std::uint32_t GetDefaultFPS() const;

	std::uint32_t GetDefaultBufferWidth() const;
	std::uint32_t GetDefaultBufferHeight() const;
	float         GetDefaultAspectRatio() const;

	std::uint32_t GetBufferWidth() const;
	std::uint32_t GetBufferHeight() const;
	Vec2u         GetBufferSize() const;
	float         GetAspectRatio() const;

	void SetBufferWidth(std::uint32_t width);
	void SetBufferHeight(std::uint32_t height);
	void SetBufferSize(Vec2u size);

	Handle GetWindowHandle() const;
	void   SetWindowHandle(Handle handle);

	FullscreenMode GetFullscreenMode() const;
	void           SetFullscreenMode(FullscreenMode fsmode);

	MSAALevel GetMSAALevel() const;
	void      SetMSAALevel(MSAALevel level);

	bool GetVsync() const;
	void SetVsync(bool enable);

private:
	static const std::uint32_t m_default_fps;
	static const std::uint32_t m_default_buffer_width;
	static const std::uint32_t m_default_buffer_height;
	static const float         m_default_aspect_ratio;

	Handle         m_window_handle;
	FullscreenMode m_fs_mode;
	MSAALevel      m_msaa_level;
	bool           m_vsync;
	std::uint32_t  m_buffer_width;
	std::uint32_t  m_buffer_height;
};
}  // namespace yz
