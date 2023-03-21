default: main
all: main

CXX = g++
CXXFLAGS = -Wall -O3 -g -std=c++11

HDRS = DataGenerator.h MySqrt.h
OBJS = DataGenerator.o MySqrt.o

%.o : %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

main: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	-rm -f *.o **/*.o main

export PATH := /home/jf1519/Downloads/tmp/OracleDeveloperStudio12.5-linux-x86-bin/developerstudio12.5/bin:$(PATH)
export MANPATH := /home/jf1519/Downloads/tmp/OracleDeveloperStudio12.5-linux-x86-bin/developerstudio12.5/man:$(MANPATH)

.PHONY: profiler
profiler: main
	echo $$PATH
	-rm -r profiler.er
	collect -o profiler.er ./main
	analyzer profiler.er


