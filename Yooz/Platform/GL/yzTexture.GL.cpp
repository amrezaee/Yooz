#include <Graphics/yzTexture.hpp>

#include <yzpch.hpp>

namespace yz
{
void Texture::Create(Vec2u size, TextureFilter filter, TextureWrapMode wrap_mode,
                     const uint8_t* data, Color border_color)
{
	m_size         = size;
	m_filter       = filter;
	m_wrap_mode    = wrap_mode;
	m_border_color = border_color;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
	SetTextureWrapMode();
	SetTextureFilter();

	glTextureStorage2D(m_handle, 1, GL_RGBA8, m_size.x, m_size.y);
	glTextureSubImage2D(m_handle, 0, 0, 0, m_size.x, m_size.y, GL_RGBA,
	                    GL_UNSIGNED_BYTE, data);
}

void Texture::Destroy()
{
	glDeleteTextures(1, &m_handle);
}

void Texture::Bind(uint32_t unit) const
{
	glBindTextureUnit(unit, m_handle);
}

Texture::handle_type Texture::GetHandle() const
{
	return m_handle;
}
Vec2u Texture::GetSize() const
{
	return m_size;
}
TextureFilter Texture::GetFilterType() const
{
	return m_filter;
}
TextureWrapMode Texture::GetWrapMode() const
{
	return m_wrap_mode;
}
Color Texture::GetBorderColor() const
{
	return m_border_color;
}


bool Texture::operator==(const Texture& rhs) const
{
	return m_handle == rhs.m_handle;
}

bool Texture::operator!=(const Texture& rhs) const
{
	return m_handle != rhs.m_handle;
}

void Texture::SetTextureFilter()
{
	switch(m_filter)
	{
	case yz::TextureFilter::Nearest:
		glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;

	case yz::TextureFilter::Linear:
		glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
}

void Texture::SetTextureWrapMode()
{
	switch(m_wrap_mode)
	{
	case yz::TextureWrapMode::Repeat:
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;

	case yz::TextureWrapMode::Mirror:
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;

	case yz::TextureWrapMode::Border:
	{
		float t[4];
		m_border_color.GetColors(t);
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTextureParameterfv(m_handle, GL_TEXTURE_BORDER_COLOR, t);
	}
	break;

	case yz::TextureWrapMode::Clamp:
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	}
}
}  // namespace yz
