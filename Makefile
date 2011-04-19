CCFLAGS=-Wall -Werror

run-watch: *.cpp *.hpp
	g++ `pkg-config --libs lua` $(CCFLAGS) -g -o $@ $^

clean:
	rm -f ./run-watch
