SDL_LIBS := -lSDL3 -lm -lkernel32 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -ladvapi32 -lsetupapi -lshell32 -ldinput8
GLEW_LIBS := -lglew32 -lopengl32

app: src/*
	g++ -static-libstdc++ -std=c++17 -DGLEW_STATIC src/main.cc src/app.cc -Iinclude -Isrc -Llib $(SDL_LIBS) $(GLEW_LIBS) -o app

gengsb:
	cd tools && g++ gengsb.c -o gengsb