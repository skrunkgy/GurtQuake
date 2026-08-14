RESOURCE_PATH = "/home/andrew/Projects/GurtQuake/resources/"
SRCS := $(shell find src -wholename "src/*.cpp")
OBJS := $(SRCS:.cpp=.o)

gquake:
	g++ -lglbinding -lGL -lSDL3 ${SRCS} -o gquake

gqtest: 
	g++ -lglbinding -lGL -lSDL3 test/main.cpp -o gqtest
