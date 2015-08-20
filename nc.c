#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "keymap.h"

#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;

char *choices[] = { 
			"Choice 1",
			"Choice 2",
			"Choice 3",
			"Choice 4",
			"Exit",
		  };
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int fd;
struct uinput_user_dev uidev;
struct input_event ev;

#define check_ret(ret) do{\
		if (ret < 0) {\
			printf("Error at %s:%d\n", __func__, __LINE__);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)

int configure_dev()
{
	int ret, i;
	memset(&uidev, 0, sizeof(uidev));

	fd = open("/dev/uinput", O_WRONLY);
	check_ret(fd);

	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");

	uidev.id.bustype = BUS_USB;
	uidev.id.vendor  = 1;
	uidev.id.product = 1;
	uidev.id.version = 1;

	ret = write(fd, &uidev, sizeof(uidev));
	if (ret != sizeof(uidev)) {
		printf("Failed to write dev structure\n");
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd, UI_SET_EVBIT, EV_KEY);
	for(i=0;i<sizeof(keymap)/sizeof(*keymap);i++) {
		if(keymap[i]) {
			printf("conf %d\n", keymap[i]);
			ret = ioctl(fd, UI_SET_KEYBIT, keymap[i]);
			check_ret(ret);
		}
	}

	ret = ioctl(fd, UI_DEV_CREATE);
	check_ret(ret);
}

void send_event(__u16 type, __u16 code, __s32 value)
{
	int ret;
	memset(&ev, 0, sizeof(ev));

	ev.type = type;
	ev.code = code;
	ev.value = value;

	ret = write(fd, &ev, sizeof(ev));
	check_ret(ret);
}

int main()
{	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;
	int i=0;

	configure_dev();
	usleep(50000);

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(++i)
	{	c = wgetch(menu_win);
		mvprintw(27, 0, "map %d %d       %d   ", c, keymap[c], i);
		refresh();
		mvprintw(28, 0, "      ", c, keymap[c]);
		refresh();
		if (!keymap[c])
			continue;
		mvprintw(28, 0, "ok", c, keymap[c]);
		refresh();

		send_event(EV_KEY, keymap[c], 1);
		send_event( EV_SYN, SYN_REPORT, 0);
		send_event(EV_KEY, keymap[c], 0);
		send_event( EV_SYN, SYN_REPORT, 0);
		mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
		refresh();

		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
	endwin();
	return 0;
}


void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
