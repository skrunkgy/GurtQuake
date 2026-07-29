all:
	g++ -I include -lGLEW -lGL -lSDL3 src/* -o gamebin
