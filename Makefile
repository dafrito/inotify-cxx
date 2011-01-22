CCFLAGS=-Wall -Werror

watcher: *.cpp *.hpp
	g++ `pkg-config --libs lua` $(CCFLAGS) -o watcher *.cpp

clean:
	rm -f ./watcher
