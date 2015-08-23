LDFLAGS=-lncurses -ltermkey
all: kbd keymap.h
nc: nc.o keymap.h
clean:
	rm kbd
