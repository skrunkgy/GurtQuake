$RESOURCE_PATH = "/home/andrew/Projects/GurtQuake/resources/"

gquake:
	g++ -I include -lglbinding -lGL -lSDL3 src/* -o gquake

gqtest: test/main.cpp
	g++ -I include -lglbinding -lGL -lSDL3 test/main.cpp -o gqtest

clean:
	rm builds/*
