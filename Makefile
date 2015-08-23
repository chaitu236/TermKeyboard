LDFLAGS=-ltermkey -lncurses
all: kbd keymap.h
nc: nc.o keymap.h
clean:
	rm kbd
