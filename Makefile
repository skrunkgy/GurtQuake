RESOURCE_PATH = "/home/andrew/Projects/GurtQuake/resources/"
SRCS := $(shell find src -wholename "src/*.cpp")
OBJS := $(SRCS:.cpp=.o)
LIBS := -lglbinding -lGL -lSDL3 -lSDL3_image

gquake:
	g++ ${LIBS} ${SRCS} -o gquake

gqtest: 
	g++ ${LIBS} test/main.cpp -o gqtest
