all: remindme.c
	cc remindme.c `pkg-config --cflags --libs libnotify gtk+-3.0` -o remindme
