CFLAGS = $(shell pkg-config --cflags gtkmm-4.0)
LIBS = $(shell pkg-config --libs gtkmm-4.0)

test-gtk: gtk.cc
	g++ -std=c++17 gtk.cc -o editor $(shell pkg-config gtkmm-4.0 --cflags --libs)