app: src/main.c
	gcc src/main.c -Iinclude -Isrc -L./ -lSDL3 -lglew32 -lopengl32 -lgdi32 -o app

gengsb:
	cd tools && gcc gengsb.c -o gengsb