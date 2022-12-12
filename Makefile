.PHONY: all clean

CC=cc 
CPPFLAGS=-O2 -std=c++11 -framework Carbon -framework IOKit
RM=rm


all:
	$(CC) $(CPPFLAGS) -o jiggle jiggle.cpp


clean:
	$(RM) -vf jiggle
