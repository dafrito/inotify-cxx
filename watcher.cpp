#include <iostream>
#include <string>
#include "INotify.hpp"

using std::cout;
using std::endl;
using std::string;

class INotifyPrintListener : public INotifyListener {
public:
	void file_written(const string& source, const string& path);
	void file_created(const string& source, const string& path);
	void file_opened(const string& source, const string& path);
	void file_closed(const string& source, const string& path);
	void file_deleted(const string& source, const string& path);
};

void INotifyPrintListener::file_created(const string& source, const string& path) 
{
	cout << "Created: " << source << " " << path << endl;
}

void INotifyPrintListener::file_opened(const string& source, const string& path) 
{
	cout << "Opened: " << source << " " << path << endl;
}

void INotifyPrintListener::file_written(const string& source, const string& path) 
{
	cout << "Written: " << source << " " << path << endl;
}

void INotifyPrintListener::file_closed(const string& source, const string& path) 
{
	cout << "Closed: " << source << " " << path << endl;
}

void INotifyPrintListener::file_deleted(const string& source, const string& path) 
{
	cout << "Deleted: " << source << " " << path << endl;
}

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
