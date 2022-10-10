#pragma once

#include <Graphics/yzColor.hpp>
#include <Graphics/yzGraphicsStates.hpp>
#include <Math/yzVector2.hpp>

#include <yzSTD.hpp>

namespace yz
{
class Texture
{
public:
	// TODO: change this to something generic
	using handle_type = std::uint32_t;

	void Create(Vec2u size, TextureFilter filter, TextureWrapMode wrap_mode,
	            const std::uint8_t* data, Color border_color = Color::BLACK);

	void Destroy();

	void Bind(std::uint32_t unit) const;

	handle_type     GetHandle() const;
	Vec2u           GetSize() const;
	TextureFilter   GetFilterType() const;
	TextureWrapMode GetWrapMode() const;
	Color           GetBorderColor() const;

	bool operator==(const Texture& rhs) const;
	bool operator!=(const Texture& rhs) const;

private:
	void SetTextureFilter();
	void SetTextureWrapMode();

private:
	handle_type     m_handle {0};
	Vec2u           m_size;
	TextureFilter   m_filter {TextureFilter::Nearest};
	TextureWrapMode m_wrap_mode {TextureWrapMode::Repeat};
	Color           m_border_color;  // for BORDER wrap mode.
};
}  // namespace yz
