#pragma once

#include <yzpch.hpp>

namespace yz
{
enum class Key : std::uint16_t
{
	None = 0,

	A = 4,
	B = 5,
	C = 6,
	D = 7,
	E = 8,
	F = 9,
	G = 10,
	H = 11,
	I = 12,
	J = 13,
	K = 14,
	L = 15,
	M = 16,
	N = 17,
	O = 18,
	P = 19,
	Q = 20,
	R = 21,
	S = 22,
	T = 23,
	U = 24,
	V = 25,
	W = 26,
	X = 27,
	Y = 28,
	Z = 29,

	N1 = 30,
	N2 = 31,
	N3 = 32,
	N4 = 33,
	N5 = 34,
	N6 = 35,
	N7 = 36,
	N8 = 37,
	N9 = 38,
	N0 = 39,

	Enter = 40,
	Esc   = 41,
	Back  = 42,
	Tab   = 43,
	Space = 44,

	Minus     = 45,
	Equal     = 46,
	LBracket  = 47,
	RBracket  = 48,
	BackSlash = 49,

	NonUsHash  = 50,
	SemiColon  = 51,
	Apostrophe = 52,
	Grave      = 53,
	Comma      = 54,
	Period     = 55,
	Slash      = 56,
	CapsLock   = 57,

	F1  = 58,
	F2  = 59,
	F3  = 60,
	F4  = 61,
	F5  = 62,
	F6  = 63,
	F7  = 64,
	F8  = 65,
	F9  = 66,
	F10 = 67,
	F11 = 68,
	F12 = 69,

	PrintScreen = 70,
	ScrollLock  = 71,
	Pause       = 72,
	Insert      = 73,
	Home        = 74,
	PageUp      = 75,
	Delete      = 76,
	End         = 77,
	PageDown    = 78,

	Right = 79,
	Left  = 80,
	Down  = 81,
	Up    = 82,

	NumLock     = 83,
	NP_DIVIDE   = 84,
	NP_MULTIPLY = 85,
	NP_MINUS    = 86,
	NP_PLUS     = 87,
	NP_ENTER    = 88,
	NP_1        = 89,
	NP_2        = 90,
	NP_3        = 91,
	NP_4        = 92,
	NP_5        = 93,
	NP_6        = 94,
	NP_7        = 95,
	NP_8        = 96,
	NP_9        = 97,
	NP_0        = 98,
	NP_PERIOD   = 99,

	NonUsBackSlash = 100,
	Application    = 101,
	Power          = 102,
	NP_Equal       = 103,

	F13 = 104,
	F14 = 105,
	F15 = 106,
	F16 = 107,
	F17 = 108,
	F18 = 109,
	F19 = 110,
	F20 = 111,
	F21 = 112,
	F22 = 113,
	F23 = 114,
	F24 = 115,

	Execute    = 116,
	Help       = 117,
	Menu       = 118,
	Select     = 119,
	Stop       = 120,
	Again      = 121,
	Undo       = 122,
	Cut        = 123,
	Copy       = 124,
	Paste      = 125,
	Find       = 126,
	Mute       = 127,
	VolumeUp   = 128,
	VolumeDown = 129,

	LCtrl  = 224,
	LShift = 225,
	LAlt   = 226,
	LGui   = 227,
	RCtrl  = 228,
	RShift = 229,
	RAlt   = 230,
	RGui   = 231, /* Windows, command (apple), meta, super */

	Count = 512
};

enum class MouseButton : std::uint8_t
{
	None,
	Left,
	Middle,
	Right,
	Back,
	Forward,
	Count
};

// Controller button
enum class CButton : std::int8_t
{
	None = -1,
	A,
	B,
	X,
	Y,
	Back,
	Guide,
	Start,
	LStick,
	RStick,
	LShoulder,
	RShoulder,
	DUp,
	DDown,
	DLeft,
	DRight,
	Misc1,
	Paddle1,
	Paddle2,
	Paddle3,
	Paddle4,
	TouchPad,
	Count = 22
};

// Controller axis
enum class CAxis : std::uint8_t
{
	None,
	LeftX,
	LeftY,
	RightX,
	RightY,
	TriggerLeft,
	TriggerRight,
	Count
};
}  // namespace yz
