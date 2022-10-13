# ppmd_sh Makefile

WARNINGS =
DEBUG    = -g
CFLAGS   = -O2 $(DEBUG) $(WARNINGS)
CXXFLAGS = $(CFLAGS) -std=c++11
INCLUDES = -I.
LIBS     =
LDFLAGS  =


CC = gcc
CXX = g++

BIN = ppmd

.PHONY: all clean

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

ppmd: pmd.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	-rm -f *.o $(BIN) core
