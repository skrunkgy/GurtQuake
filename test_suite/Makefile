CFLAGS = $(shell pkg-config --cflags gtk4)
LIBS = $(shell pkg-config --libs gtk4)

test-gtk: gtk.c
	gcc $(CFLAGS) gtk.c -o gtk-test $(LIBS) -mwindows