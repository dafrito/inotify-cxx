#ifndef HPP_INOTIFY_PRIMARY
#define HPP_INOTIFY_PRIMARY

#include <sys/inotify.h>
#include <string>
#include <vector>
#include <map>
#include <functional>

using std::string;

typedef std::map<const int, string> WatchMap;
typedef std::function<void(const string& source, const string& path, const inotify_event&)> NotifyListener;

class INotify
{
public:
	INotify(const NotifyListener& receiver=noopReceiver);
	~INotify();

	void watch(const string& path, const int& bitmask);
	void watch(const string& path);
	bool hasWatch(const string& path);
	void readEvents();
	void removeWatch(const string& path);

	void setReceiver(const NotifyListener& listener);
protected:

	void dispatchEvent(const inotify_event& event);
	int getWatchFD(const string& path);
private:
	static const int EVENT_SIZE = sizeof(inotify_event);
	static const int BUF_LEN = 1024*(EVENT_SIZE+16);

	static void noopReceiver(const string&, const string&, const inotify_event&)
	{
		// No-op
	}

	const int fd;
	NotifyListener receiver;
	WatchMap watches;

	char buffer[BUF_LEN];
};

#endif
