#include "INotifyPrintListener.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

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

