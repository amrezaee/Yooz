#pragma once


namespace yz
{
enum class BlendMode
{
	ONE,
	ZERO,

	SRC_COLOR,
	INVERSE_SRC_COLOR,
	SRC_ALPHA,
	INVERSE_SRC_ALPHA,

	DST_COLOR,
	INVERSE_DST_COLOR,
	DST_ALPHA,
	INVERSE_DST_ALPHA,

	BLEND_FACTOR,
	INVERSE_BLEND_FACTOR,

	SRC_ALPHA_SATURATION
};

enum class BlendFunction
{
	ADD,
	SUB,
	REVERSE_SUB,
	MIN,
	MAX
};

enum class CullMode
{
	NONE,  // don't cull
	CW,    // clock wise
	CCW    // counter clock wise
};

enum class FillMode
{
	FILL,
	WIRE_FRAME
};

enum class TextureFilter
{
	NEAREST,  // aka Point filtering
	LINEAR
};

enum class TextureWrapMode
{
	REPEAT,  // aka wrap
	MIRROR,
	BORDER,
	CLAMP
};

enum class CompareFunctions
{
	NEVER,
	ALWAYS,
	EQUAL,
	NOT_EQUAL,
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
};
}  // namespace yz
