#ifndef HPP_INOTIFY_PRIMARY
#define HPP_INOTIFY_PRIMARY

#include <sys/inotify.h>
#include <string>
#include <vector>
#include <map>
#include <functional>

using std::string;

typedef std::map<const int, string> WatchMap;
typedef std::function<void(const string& source, const string& path, const inotify_event&, void* user_data)> NotifyListener;

class INotify
{
public:
	INotify(const NotifyListener& receiver=noopReceiver, void* data=NULL);
	~INotify();

	void watch(const string& path, const int& bitmask);
	void watch(const string& path);
	bool hasWatch(const string& path);
	void readEvents();
	void removeWatch(const string& path);

	inline void setReceiver(const NotifyListener& listener) { receiver = listener; }
	inline void setData(void* data) { user_data = data; }

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
	void* user_data;

	char buffer[BUF_LEN];
};

#endif
