#include <iostream>
#include "INotify.hpp"

int main(int argc, char **argv) 
{
	INotify inotify;
	for (int i=1; i < argc; ++i)
		inotify.watch(string(argv[i]), IN_MODIFY);
	inotify.read_events();
}
