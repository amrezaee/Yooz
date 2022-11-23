#pragma once


namespace yz
{
enum class GraphicsAPI
{
	GL,
	ES,
	VK
};

enum class FullscreenMode
{
	Windowed,
	Borderless,
	Exclusive
};

enum class BlendMode
{
	One,
	Zero,

	Src_Color,
	Inverse_Src_Color,
	Src_Alpha,
	Inverse_Src_Alpha,

	Dst_Color,
	Inverse_Dst_Color,
	Dst_Alpha,
	Inverse_Dst_Alpha,

	Blend_Factor,
	Inverse_Blend_Factor,

	Src_Alpha_Saturation
};

enum class BlendFunction
{
	Add,
	Sub,
	Reverse_Sub,
	Min,
	Max
};

enum class FillMode
{
	Fill,
	Line
};

enum class TextureFilter
{
	Nearest,  // aka Point filtering
	Linear
};

enum class TextureWrapMode
{
	Repeat,  // aka wrap
	Mirror,
	Border,
	Clamp
};

enum class PixelFormat
{
	None,

	R8,        // unsigned R with 8 bits per channel.
	RG8,       // unsigned RG with 8 bits per channel.
	RGB565,    // unsigned RGB with 5, 6 and 5 bits for R, G and B channels.
	RGB8,      // unsigned RGB wtih 8 bits per channel.
	RGBA4,     // unsigned RGBA with 4 bits per channel.
	RGBA8,     // unsigned RGBA with 8 bits per channel.

	RF,        // float R (HDR)
	RGF,       // float RG (HDR)
	RGBF,      // float RGB (HDR)
	RGBAF,     // float RGBA (HDR)
	
	DXT1,      // DXT1 (S3TC BC1) format. dimensions must be a multiple of 4. (compressed)
	DXT1A,     // DXT1 with 1 bit alpha channel. (compressed)
	DXT1SRGB,  // DXT1 sRGB format. (compressed)
	DXT3,      // DXT3 (BC2) format. dimensions must be a multiple of 4. (compressed)
	DXT3SRGB,  // DXT3 sRGB format. (compressed)
	DXT5,      // DXT5 (BC3) format. dimensions must be a multiple of 4. (compressed)
	DXT5SRGB,  // DXT5 sRGB format.
};

enum class CompareFunctions
{
	Never,
	Always,
	Equal,
	Not_Equal,
	Less,
	Less_Equal,
	Greater,
	Greater_Equal,
};

enum class MSAALevel
{
	None    = 0,
	Level2  = 2,
	Level4  = 4,
	Level8  = 8,
	Level16 = 16,
	Level32 = 32
};

enum class VsyncMode
{
	Immediate    = 0,
	Synchronized = 1,
	Adaptive     = -1
};
}  // namespace yz
