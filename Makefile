CPPFLAGS=-std=c++17
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

comp: $(OBJS)
	$(CXX) -o comp $(OBJS) $(LDFLAGS)

$(OBJS) : regex.h

test: comp
	./test.sh

clean:
	rm -f comp *.o *~ tmp*

run: comp
	./comp

.PHONY: test clean run
