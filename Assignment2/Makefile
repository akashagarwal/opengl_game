CC = g++
CFLAGS = -Wall
PROG = game


SRCS = world.cpp md2model.cpp vec3f.cpp imageloader.cpp
LIBS = -lglut -lGL -lGLU -lm

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
