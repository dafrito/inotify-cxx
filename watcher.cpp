#include <iostream>
#include <string>

#include "inotify/INotify.hpp"
#include "inotify/INotifyPrintListener.hpp"

int main(int argc, char **argv) 
{
	INotify inotify;
	INotifyPrintListener listener;
	inotify.add_listener(&listener);
	for (int i=1; i < argc; ++i)
		inotify.watch(string(argv[i]));
	while(true)
		inotify.read_events();
}
