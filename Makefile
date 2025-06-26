SDL_LIBS := -lSDL3 -lm -lkernel32 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -ladvapi32 -lsetupapi -lshell32 -ldinput8
GLEW_LIBS := -lglew32 -lopengl32
CFLAGS := -static-libstdc++ -std=c++17

SRC = src/app.cc src/mesh.cc src/shader.cc src/main.cc src/serialize.cc

app: src/*
	g++ $(CFLAGS) $(SRC) -Iinclude -Isrc -Llib $(SDL_LIBS) $(GLEW_LIBS) -o app

test: test/*
	g++ test/main.cc -Isrc -o test/test -std=c++17
	test/test.exe

debug: src/*
	g++ -g $(CFLAGS) $(SRC) -Iinclude -Isrc -Llib $(SDL_LIBS) $(GLEW_LIBS) -o dapp
	gdb dapp -ex "run" -q

gengsb:
	cd tools && g++ gengsb.c -o gengsb