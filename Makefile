CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags) -pthread
LDFLAGS=-g $(shell root-config --ldflags) -pthread
LDLIBS=$(shell root-config --libs)

SRCS= $(wildcard ./src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: pool

pool: $(OBJS)
	$(CXX) $(LDFLAGS) -o pool $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend
