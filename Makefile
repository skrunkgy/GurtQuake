SDL_LIBS := -lSDL3 -lm -lkernel32 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -ladvapi32 -lsetupapi -lshell32 -ldinput8
GLEW_LIBS := -lglew32 -lopengl32 -DGLEW_STATIC
CFLAGS := -static-libstdc++ -std=c++17

SRC = src/app.cpp src/mesh.cpp src/shader.cpp src/main.cpp

app: src/*
	g++ $(CFLAGS) $(SRC) -Iinclude -Isrc -Llib $(SDL_LIBS) $(GLEW_LIBS) -o app

test: test/* src/gmath/*
	g++ test/main.cpp -o test/test -std=c++17
	test/test.exe

debug: src/*
	g++ -g $(CFLAGS) $(SRC) -Iinclude -Isrc -Llib $(SDL_LIBS) $(GLEW_LIBS) -o dapp
	gdb dapp -ex "run" -q