#include <Graphics/yzImage.hpp>

#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x) YZ_EXPAND(YZ_ASSERT(x))
#define STBI_NO_STDIO
#include <ThirdParty/stb_image.h>

namespace yz
{
static bool STBLoader(const stbi_uc* indata, void** outdata, size_t size, int* width,
                      int* height, int* channels, bool hdr)
{
	if(hdr)
		*outdata = stbi_loadf_from_memory(indata, static_cast<int>(size), width,
		                                  height, channels, 0);
	else
		*outdata = stbi_load_from_memory(indata, static_cast<int>(size), width,
		                                 height, channels, 0);

	if(!outdata)
		return false;
	return true;
}

Image::Image()
        : m_width(0), m_height(0), m_format(PixelFormat::None), m_data(nullptr),
          m_size(0)
{
}

Image::Image(uint16_t width, uint16_t height, PixelFormat format, const void* data)
        : m_width(width), m_height(height), m_format(format), m_size(CalculateSize())
{
	if(IsHDR())
		m_data = new float[m_size];
	else
		m_data = new uint8_t[m_size];

	memcpy(m_data, data, m_size);
}

Image::Image(uint16_t width, uint16_t height, PixelFormat format, Color color)
        : m_width(width), m_height(height), m_format(format), m_size(CalculateSize())
{
	if(IsHDR())
		m_data = new float[m_size];
	else
		m_data = new uint8_t[m_size];

	memset(m_data, color.GetPacked(), m_size);
}

Image::Image(const std::string& path)
{
	Load(path);
}

Image::~Image()
{
	Destroy();
}

bool Image::Load(const fs::path& path)
{
	int   w, h, c;
	void* data   = nullptr;
	char* buffer = nullptr;
	bool  is_hdr = false, is_compressed = false;

	std::ifstream f(path, std::ios::binary | std::ios::ate);

	if(f.bad())
	{
		YZ_ERROR(strerror(errno));
		return false;
	}

	std::streamsize fsize = f.tellg();
	f.seekg(0, std::ios::beg);

	buffer = new char[fsize];

	YZ_ASSERT(buffer, "Memory allocation failed.");

	if(!f.read(buffer, fsize))
	{
		YZ_ERROR(strerror(errno));
		return false;
	}

	f.close();

	if(f.bad())
	{
		YZ_ERROR(strerror(errno));
		return false;
	}

	fs::path ext = path.extension();

	is_hdr = (ext == ".hdr" || ext == ".HDR");
	is_compressed =
	        (ext == ".ktx" || ext == ".KTX" || ext == ".dds" || ext == ".DDS");

	if(!is_compressed)
	{
		if(!STBLoader(reinterpret_cast<stbi_uc*>(buffer), &data, fsize, &w, &h, &c,
		              is_hdr))
		{
			YZ_ERROR("Cannot load image file %s", path.filename().generic_string());
			return false;
		}

		m_width  = static_cast<uint16_t>(w);
		m_height = static_cast<uint16_t>(h);
		m_data   = data;
		m_format = Channels2PixelFormat(c, is_hdr);
		m_size   = CalculateSize();
	}
	else
	{
		YZ_ERROR("Compressed image loader isn't implemented yet.");
		return false;
	}

	YZ_INFO("Image file %s %ux%u loaded.", path.filename().generic_string(), m_width,
	        m_height);

	return true;
}

void Image::Destroy()
{
	if(m_data)
	{
		delete[] m_data;
		m_data   = nullptr;
		m_width  = 0;
		m_height = 0;
		m_size   = 0;
		m_format = PixelFormat::None;
	}
}

size_t Image::GetSize() const
{
	return m_size;
}

size_t Image::GetPixelCount() const
{
	return m_width * m_height;
}

uint16_t Image::GetWidth() const
{
	return m_width;
}

uint16_t Image::GetHeight() const
{
	return m_height;
}

PixelFormat Image::GetFormat() const
{
	return m_format;
}

const void* Image::GetData() const
{
	return m_data;
}

int Image::GetBPP() const
{
	switch(m_format)
	{
	case PixelFormat::None: return 0;

	case PixelFormat::R8: return 8;
	case PixelFormat::RG8: return 16;
	case PixelFormat::RGB565: return 16;
	case PixelFormat::RGB8: return 24;
	case PixelFormat::RGBA4: return 16;
	case PixelFormat::RGBA8: return 32;

	case PixelFormat::RF: return 32;
	case PixelFormat::RGF: return 64;
	case PixelFormat::RGBF: return 96;
	case PixelFormat::RGBAF: return 128;

	case PixelFormat::DXT1: return 4;
	case PixelFormat::DXT1A: return 4;
	case PixelFormat::DXT1SRGB: return 4;  // NOTE: not sure
	case PixelFormat::DXT3: return 8;
	case PixelFormat::DXT3SRGB: return 8;  // NOTE: not sure
	case PixelFormat::DXT5: return 8;
	case PixelFormat::DXT5SRGB: return 8;  // NOTE: not sure
	}
	return -1;
}

bool Image::IsEmpty() const
{
	return m_size == 0;
}

bool Image::IsHDR()
{
	switch(m_format)
	{
	case PixelFormat::RF:
	case PixelFormat::RGF:
	case PixelFormat::RGBF:
	case PixelFormat::RGBAF: return true;
	default: return false;
	}
}

bool Image::IsLDR()
{
	return !IsHDR();
}

PixelFormat Image::Channels2PixelFormat(int c, bool is_hdr)
{
	if(is_hdr)
	{
		if(c == 1)
			return PixelFormat::RF;
		else if(c == 2)
			return PixelFormat::RGF;
		else if(c == 3)
			return PixelFormat::RGBF;
		else if(c == 4)
			return PixelFormat::RGBAF;
	}
	else
	{
		if(c == 1)
			return PixelFormat::R8;
		else if(c == 2)
			return PixelFormat::RG8;
		else if(c == 3)
			return PixelFormat::RGB8;
		else if(c == 4)
			return PixelFormat::RGBA8;
	}
	return PixelFormat::None;
}

size_t Image::CalculateSize() const
{
	return static_cast<size_t>(m_width) * m_height * GetBPP() / 8;
}
}  // namespace yz
