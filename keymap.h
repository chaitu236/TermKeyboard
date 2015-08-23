#include <linux/input.h>

struct keymap {
	int modifier;
	int kernelcode;
};

struct map {
	int usercode;
	int modifier;
	int kernelcode;
};

enum modifier {NONE, SHIFT, ALT};

int fnmap[] = {0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12};
int keysymmap[] = {0,
		   KEY_BACKSPACE, KEY_TAB, KEY_ENTER, KEY_ESC, KEY_SPACE, /*5*/
		   0, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,/*10*/
		   0, KEY_TAB, 0, KEY_DELETE};

struct map kmap[] = {
		{33, SHIFT, KEY_1},
		{34, SHIFT, KEY_APOSTROPHE},
		{35, SHIFT, KEY_3},
		{36, SHIFT, KEY_4},
		{37, SHIFT, KEY_5},
		{38, SHIFT, KEY_7},
		{39, 0, KEY_APOSTROPHE},
		{40, SHIFT, KEY_9},
		{41, SHIFT, KEY_0},
		{42, SHIFT, KEY_8},
		{43, SHIFT, KEY_EQUAL},
		{44, 0, KEY_COMMA},
		{45, 0, KEY_MINUS},
		{46, 0, KEY_DOT},
		{47, 0, KEY_SLASH},
		{48, 0, KEY_0},
		{49, 0, KEY_1},
		{50, 0, KEY_2},
		{51, 0, KEY_3},
		{52, 0, KEY_4},
		{53, 0, KEY_5},
		{54, 0, KEY_6},
		{55, 0, KEY_7},
		{56, 0, KEY_8},
		{57, 0, KEY_9},
		{58, SHIFT, KEY_SEMICOLON},
		{59, 0, KEY_SEMICOLON},
		{60, SHIFT, KEY_COMMA},
		{61, 0, KEY_EQUAL},
		{62, SHIFT, KEY_DOT},
		{63, SHIFT, KEY_SLASH},
		{64, SHIFT, KEY_2},
		{65, SHIFT, KEY_A},
		{66, SHIFT, KEY_B},
		{67, SHIFT, KEY_C},
		{68, SHIFT, KEY_D},
		{69, SHIFT, KEY_E},
		{70, SHIFT, KEY_F},
		{71, SHIFT, KEY_G},
		{72, SHIFT, KEY_H},
		{73, SHIFT, KEY_I},
		{74, SHIFT, KEY_J},
		{75, SHIFT, KEY_K},
		{76, SHIFT, KEY_L},
		{77, SHIFT, KEY_M},
		{78, SHIFT, KEY_N},
		{79, SHIFT, KEY_O},
		{80, SHIFT, KEY_P},
		{81, SHIFT, KEY_Q},
		{82, SHIFT, KEY_R},
		{83, SHIFT, KEY_S},
		{84, SHIFT, KEY_T},
		{85, SHIFT, KEY_U},
		{86, SHIFT, KEY_V},
		{87, SHIFT, KEY_W},
		{88, SHIFT, KEY_X},
		{89, SHIFT, KEY_Y},
		{90, SHIFT, KEY_Z},
		{91, 0, KEY_LEFTBRACE},
		{92, 0, KEY_BACKSLASH},
		{93, 0, KEY_RIGHTBRACE},
		{94, SHIFT, KEY_6},
		{95, SHIFT, KEY_MINUS},
		{96, 0, KEY_GRAVE},
		{97, 0, KEY_A},
		{98, 0, KEY_B},
		{99, 0, KEY_C},
		{100, 0, KEY_D},
		{101, 0, KEY_E},
		{102, 0, KEY_F},
		{103, 0, KEY_G},
		{104, 0, KEY_H},
		{105, 0, KEY_I},
		{106, 0, KEY_J},
		{107, 0, KEY_K},
		{108, 0, KEY_L},
		{109, 0, KEY_M},
		{110, 0, KEY_N},
		{111, 0, KEY_O},
		{112, 0, KEY_P},
		{113, 0, KEY_Q},
		{114, 0, KEY_R},
		{115, 0, KEY_S},
		{116, 0, KEY_T},
		{117, 0, KEY_U},
		{118, 0, KEY_V},
		{119, 0, KEY_W},
		{120, 0, KEY_X},
		{121, 0, KEY_Y},
		{122, 0, KEY_Z},
		{123, SHIFT, KEY_LEFTBRACE},
		{124, SHIFT, KEY_BACKSLASH},
		{125, SHIFT, KEY_RIGHTBRACE},
	};
#if 0
int keymap[] = {0,
		0, 0, 0, 0, 0, 0, 0, 0, KEY_TAB, KEY_ENTER,
		0, 0, 0, 0, KEY_TAB, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, KEY_SPACE, 0, 0, 0, 0, 0, 0, KEY_APOSTROPHE, 0,
		0, 0, 0, KEY_COMMA, KEY_MINUS, KEY_DOT, KEY_SLASH, KEY_0, KEY_1, KEY_2,/*50*/
		KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, 0, KEY_SEMICOLON, 0,
		KEY_EQUAL, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		KEY_LEFTBRACE, KEY_BACKSLASH, KEY_RIGHTBRACE, 0, 0, 0, KEY_A, KEY_B, KEY_C, KEY_D,/*100*/
		KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
		KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X,
		KEY_Y, KEY_Z, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/*150*/
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/*200*/
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/*250*/
		0, 0, 0, 0, 0, 0, 0, KEY_DOWN, KEY_UP, KEY_LEFT,
		KEY_RIGHT, 0, KEY_BACKSPACE, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/*300*/
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_DELETE,
		};
#endif
