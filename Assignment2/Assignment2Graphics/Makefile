CC = g++
#CFLAGS = -Wall
PROG = cse251_sampleCode

SRCS = latest.cpp  imageloader.cpp Robot.cpp

LIBS = -lglut -lGL -lGLU -lm

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
