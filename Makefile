CCFLAGS=-Wall -Werror

run-watch: *.cpp *.hpp
	g++ `pkg-config --libs lua` $(CCFLAGS) -g -o run-watch *.cpp

clean:
	rm -f ./run-watch
