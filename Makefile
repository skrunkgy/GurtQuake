all:
	g++ -I include -lglbinding -lGL -lSDL3 src/* -o gamebin
