app: src/* src/graphics/* src/util/*
	gcc src/main.c src/graphics/shaders.c src/graphics/mesh.c src/util/filesystem.c -Iinclude -Isrc -L./ -lSDL3 -lglew32 -lopengl32 -lgdi32 -o app

test: src/test.c src/util/filesystem.c
	gcc src/test.c src/util/filesystem.c -Isrc -o test

gengsb:
	cd tools && gcc gengsb.c -o gengsb