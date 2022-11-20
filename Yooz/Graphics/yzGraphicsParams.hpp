#pragma once

#include <Core/yzBase.hpp>
#include <Graphics/yzGraphicsStates.hpp>
#include <Math/yzVector2.hpp>

#include <yzpch.hpp>

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

	uint32_t GetDefaultFPS() const;

	uint16_t GetDefaultBufferWidth() const;
	uint16_t GetDefaultBufferHeight() const;
	float    GetDefaultAspectRatio() const;

	uint16_t GetBufferWidth() const;
	uint16_t GetBufferHeight() const;
	Vec2u    GetBufferSize() const;
	float    GetAspectRatio() const;

	void SetBufferWidth(uint16_t width);
	void SetBufferHeight(uint16_t height);
	void SetBufferSize(uint16_t w, uint16_t h);

	Handle GetWindowHandle() const;
	void   SetWindowHandle(Handle handle);

	FullscreenMode GetFullscreenMode() const;
	void           SetFullscreenMode(FullscreenMode fsmode);

	MSAALevel GetMSAALevel() const;
	void      SetMSAALevel(MSAALevel level);  // TODO: impl. this

	VsyncMode GetVsyncMode() const;
	void      SetVsyncMode(VsyncMode vm);

private:
	static const uint32_t m_default_fps;
	static const uint16_t m_default_buffer_width;
	static const uint16_t m_default_buffer_height;
	static const float    m_default_aspect_ratio;

	Handle         m_window_handle;
	FullscreenMode m_fs_mode;
	MSAALevel      m_msaa_level;
	VsyncMode      m_vsync;
	uint16_t       m_buffer_width;
	uint16_t       m_buffer_height;
};
}  // namespace yz
