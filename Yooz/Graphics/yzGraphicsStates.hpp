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

enum class SurfaceFormat
{
	RGBA16,    // unsigned RGBA with 16 bits per channel.
	RGBA8,     // unsigned RGBA with 8 bits per channel.
	RGB8,      // unsigned RGB wtih 8 bits per channel.
	RG8,       // unsigned RG with 8 bits per channel.
	R8,        // unsigned R with 8 bits per channel.
	DXT1,      // DXT1 compressed format. dimensions must be a multiple of 4.
	DXT1A,     // DXT1 with 1 bit channel.
	DXT1SRGB,  // DXT1 sRGB format.
	DXT3,      // DXT3 compressed format. dimensions must be a multiple of 4.
	DXT3SRGB,  // DXT3 sRGB format.
	DXT5,      // DXT5 compressed format. dimensions must be a multiple of 4.
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
}  // namespace yz
