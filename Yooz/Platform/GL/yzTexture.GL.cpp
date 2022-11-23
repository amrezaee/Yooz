#include <Graphics/yzTexture.hpp>

#include <yzpch.hpp>

#include <Graphics/yzImage.hpp>

namespace yz
{
static GLenum PixelFormat2GLInternalFormat(PixelFormat pf)
{
	switch(pf)
	{
	case PixelFormat::R8: return GL_R8;
	case PixelFormat::RG8: return GL_RG8;
	case PixelFormat::RGB565: return GL_RGB8;
	case PixelFormat::RGB8: return GL_RGB8;
	case PixelFormat::RGBA4: return GL_RGBA8;
	case PixelFormat::RGBA8: return GL_RGBA8;

	case PixelFormat::RF: return GL_R32F;
	case PixelFormat::RGF: return GL_RG32F;
	case PixelFormat::RGBF: return GL_RGB32F;
	case PixelFormat::RGBAF: return GL_RGBA32F;

	case PixelFormat::DXT1: return 0;      // TODO: find correct number
	case PixelFormat::DXT1A: return 0;     // TODO: find correct number
	case PixelFormat::DXT1SRGB: return 0;  // TODO: find correct number
	case PixelFormat::DXT3: return 0;      // TODO: find correct number
	case PixelFormat::DXT3SRGB: return 0;  // TODO: find correct number
	case PixelFormat::DXT5: return 0;      // TODO: find correct number
	case PixelFormat::DXT5SRGB: return 0;  // TODO: find correct number

	default: return 0;
	}
}

static GLenum PixelFormat2GLTextureFormat(PixelFormat pf)
{
	switch(pf)
	{
	case PixelFormat::R8:
	case PixelFormat::RF: return GL_RED;

	case PixelFormat::RG8:
	case PixelFormat::RGF: return GL_RG;

	case PixelFormat::RGB565:
	case PixelFormat::RGBF:
	case PixelFormat::RGB8: return GL_RGB;

	case PixelFormat::RGBA4:
	case PixelFormat::RGBA8:
	case PixelFormat::RGBAF: return GL_RGBA;

	case PixelFormat::DXT1: return 0;  // TODO: find correct numbers
	case PixelFormat::DXT1A: return 0;
	case PixelFormat::DXT1SRGB: return 0;
	case PixelFormat::DXT3: return 0;
	case PixelFormat::DXT3SRGB: return 0;
	case PixelFormat::DXT5: return 0;
	case PixelFormat::DXT5SRGB: return 0;

	default: return 0;
	}
}

static GLenum PixelFormat2GLTextureType(PixelFormat pf)
{
	switch(pf)
	{
	case PixelFormat::R8:
	case PixelFormat::RG8:
	case PixelFormat::RGB8:
	case PixelFormat::RGBA8: return GL_UNSIGNED_BYTE;

	case PixelFormat::RGB565: return GL_UNSIGNED_SHORT_5_6_5;

	case PixelFormat::RGBA4: return GL_UNSIGNED_SHORT_4_4_4_4;

	case PixelFormat::RF:
	case PixelFormat::RGF:
	case PixelFormat::RGBF:
	case PixelFormat::RGBAF: return GL_FLOAT;

	case PixelFormat::DXT1: return 0;  // TODO: find correct numbers
	case PixelFormat::DXT1A: return 0;
	case PixelFormat::DXT1SRGB: return 0;
	case PixelFormat::DXT3: return 0;
	case PixelFormat::DXT3SRGB: return 0;
	case PixelFormat::DXT5: return 0;
	case PixelFormat::DXT5SRGB: return 0;

	default: return 0;
	}
}

Texture::~Texture()
{
	Destroy();
}

void Texture::Create(Vec2u size, TextureFilter filter, TextureWrapMode wrap_mode,
                     const uint8_t* data, Color border_color)
{
	if(m_handle != 0)
		return;

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

void Texture::Create(const Image& image, TextureFilter filter, TextureWrapMode wrap,
                     Color border_color)
{
	if(m_handle != 0)
		return;

	m_size         = Vec2(image.GetWidth(), image.GetHeight());
	m_filter       = filter;
	m_wrap_mode    = wrap;
	m_border_color = border_color;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
	SetTextureWrapMode();
	SetTextureFilter();

	glTextureStorage2D(m_handle, 1, PixelFormat2GLInternalFormat(image.GetFormat()),
	                   m_size.x, m_size.y);

	glTextureSubImage2D(m_handle, 0, 0, 0, m_size.x, m_size.y,
	                    PixelFormat2GLTextureFormat(image.GetFormat()),
	                    PixelFormat2GLTextureType(image.GetFormat()),
	                    image.GetData());
}

void Texture::Destroy()
{
	if(m_handle != 0)
	{
		glDeleteTextures(1, &m_handle);
		m_handle = 0;
	}
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
