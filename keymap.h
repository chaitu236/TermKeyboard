#include <linux/input.h>

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
