.PHONY: all clean

CC=clang
CPPFLAGS=-Os -framework Carbon -framework IOKit
RM=rm

all:
	$(CC) $(CPPFLAGS) -o jiggle jiggle.c
	strip jiggle

clean:
	$(RM) -vf jiggle
