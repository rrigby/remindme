all: remindme.c
	cc remindme.c `pkg-config --cflags --libs libnotify` -o remindme
