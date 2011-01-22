CCFLAGS=-Wall -Werror

run-watch: *.cpp
	g++ `pkg-config --libs lua` $(CCFLAGS) -g -o run-watch inotify/*.cpp *.cpp

clean:
	rm -f ./run-watch
