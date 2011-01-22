#ifndef INOTIFY_H
#define INOTIFY_H

#include <sys/inotify.h>
#include <string>
#include <vector>
#include <map>
#include "INotifyListener.hpp"

using namespace std;

typedef map<int, string> WatchMap;

class INotify
{
public:
	INotify();
	~INotify();

	void watch(const string& path, const int& bitmask);
	bool has_watch(const string& path);
	void read_events();
	void remove_watch(const string& path);

	void add_listener(const INotifyListener* const listener);
	bool remove_listener(const INotifyListener* const listener);
protected:

	void dispatch_event(const inotify_event& event);
	int get_watch_fd(const string& path);
private:
	static const int EVENT_SIZE = sizeof(inotify_event);
	static const int BUF_LEN = 1024*(EVENT_SIZE+16);

	const int fd;
	map<int, string> watches;
	vector<const INotifyListener*> listeners;
	char buffer[BUF_LEN];
};

#endif
