#ifndef HPP_INOTIFY_PRIMARY
#define HPP_INOTIFY_PRIMARY

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
	void watch(const string& path);
	bool has_watch(const string& path);
	void read_events();
	void remove_watch(const string& path);

	void add_listener(INotifyListener* const listener);
	bool remove_listener(INotifyListener* const listener);
protected:

	void dispatch_event(const inotify_event& event);
	int get_watch_fd(const string& path);
private:
	static const int EVENT_SIZE = sizeof(inotify_event);
	static const int BUF_LEN = 1024*(EVENT_SIZE+16);

	const int fd;
	map<const int, string> watches;
	vector<INotifyListener*> listeners;
	char buffer[BUF_LEN];
};

#endif
