
#ifndef BB_BRL_KEYCODES_H
#define BB_BRL_KEYCODES_H

enum{
	MOUSE_LEFT=1,
	MOUSE_RIGHT=2,
	MOUSE_MIDDLE=3
};

enum{
	MODIFIER_NONE=0,
	MODIFIER_SHIFT=1,
	MODIFIER_CONTROL=2,
	MODIFIER_OPTION=4,
	MODIFIER_SYSTEM=8,

	MODIFIER_ALT=MODIFIER_OPTION,
	MODIFIER_MENU=MODIFIER_OPTION,
	MODIFIER_APPLE=MODIFIER_SYSTEM,
	MODIFIER_WINDOWS=MODIFIER_SYSTEM
};

enum{
	KEY_BACKSPACE=8,KEY_TAB,
	KEY_ENTER=13,
	KEY_ESC=27,
	KEY_SPACE=32,
	KEY_PAGEUP=33,KEY_PAGEDOWN,KEY_END,KEY_HOME,
	KEY_LEFT=37,KEY_UP,KEY_RIGHT,KEY_DOWN,
	KEY_INSERT=45,KEY_DELETE,
	KEY_0=48,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,
	KEY_A=65,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F,KEY_G,KEY_H,KEY_I,KEY_J,
	KEY_K,KEY_L,KEY_M,KEY_N,KEY_O,KEY_P,KEY_Q,KEY_R,KEY_S,KEY_T,
	KEY_U,KEY_V,KEY_W,KEY_X,KEY_Y,KEY_Z,
	
	KEY_LSYS=91,KEY_RSYS,
	
	KEY_NUM0=96,KEY_NUM1,KEY_NUM2,KEY_NUM3,KEY_NUM4,
	KEY_NUM5,KEY_NUM6,KEY_NUM7,KEY_NUM8,KEY_NUM9,
	KEY_NUMMULTIPLY=106,KEY_NUMADD,KEY_NUMSLASH,
	KEY_NUMSUBTRACT,KEY_NUMDECIMAL,KEY_NUMDIVIDE,

	KEY_F1=112,KEY_F2,KEY_F3,KEY_F4,KEY_F5,KEY_F6,
	KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_F11,KEY_F12,

	KEY_LSHIFT=160,KEY_RSHIFT,
	KEY_LCONTROL=162,KEY_RCONTROL,
	KEY_LALT=164,KEY_RALT,

	KEY_TILDE=192,KEY_MINUS=189,KEY_EQUALS=187,
	KEY_OPENBRACKET=219,KEY_CLOSEBRACKET=221,KEY_BACKSLASH=226,
	KEY_SEMICOLON=186,KEY_QUOTES=222,
	KEY_COMMA=188,KEY_PERIOD=190,KEY_SLASH=191
};

#endif

