CCFLAGS=-Wall -Werror

run-watch: *.cpp *.hpp
	g++ `pkg-config --libs lua` $(CCFLAGS) -o run-watch *.cpp

clean:
	rm -f ./run-watch
