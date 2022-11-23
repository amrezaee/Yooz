#pragma once

#include <yzpch.hpp>

#include <Graphics/yzColor.hpp>
#include <Graphics/yzGraphicsStates.hpp>

namespace yz
{
class Image
{
public:
	Image();  // create empty image
	Image(const std::string& path);
	Image(uint16_t width, uint16_t height, PixelFormat format, const void* data);
	Image(uint16_t width, uint16_t height, PixelFormat format, Color color);
	~Image();

	bool Load(const fs::path& path);

	void Destroy();

	size_t      GetSize() const;        // size in bytes
	size_t      GetPixelCount() const;  // number of pixels
	uint16_t    GetWidth() const;
	uint16_t    GetHeight() const;
	PixelFormat GetFormat() const;
	const void* GetData() const;
	int         GetBPP() const;

	bool IsEmpty() const;
	bool IsHDR();
	bool IsLDR();

private:
	static PixelFormat Channels2PixelFormat(int c, bool is_hdr);
	size_t             CalculateSize() const;

private:
	uint16_t    m_width;
	uint16_t    m_height;
	PixelFormat m_format;
	void*       m_data;
	size_t      m_size;
};
}  // namespace yz
