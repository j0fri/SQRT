default: main
all: main

CXX = g++
CXXFLAGS = -Wall -O0 -g

HDRS = DataGenerator.h
OBJS = DataGenerator.o

%.o : %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

main: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	-rm -f *.o **/*.o main

.PHONY: profiler
profiler: main
	-rm -r profiler.er
	collect -o profiler.er ./main
	analyzer profiler.er

