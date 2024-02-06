.PHONY: all clean

CC=clang
CFLAGS=-Os -framework Carbon -framework IOKit
RM=rm
SOURCES=*.c
HEADERS=*.h

all: jiggle

jiggle_x86: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o jiggle_x86 -target x86_64-apple-macos12 $(SOURCES)

jiggle_arm: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o jiggle_arm -target arm64-apple-macos12 $(SOURCES)

jiggle: jiggle_x86 jiggle_arm Makefile
	lipo -create -output jiggle jiggle_x86 jiggle_arm

clean:
	$(RM) -vf jiggle jiggle_x86 jiggle_arm
