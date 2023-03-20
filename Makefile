default: main
all: main

CXX = g++
CXXFLAGS = -std=c++20 -Wall -O0 -g -I ./

HDRS = DataGenerator.h
OBJS = DataGenerator.o

%.o : %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

main: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SIMLIBS)

.PHONY: clean
clean:
	-rm -f *.o **/*.o main

.PHONY: profiler
profiler: main
	-rm -r profiler.er
	collect -o profiler.er ./main
	analyzer profiler.er

