CCFLAGS=-Wall

watcher: watcher.cpp
	g++ `pkg-config --libs lua` $(CCFLAGS) -o watcher *.cpp

clean:
	rm -f ./watcher
