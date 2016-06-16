#include <map>
#include <iostream>
#include <stdexcept>
#include "INotify.hpp"

using namespace std;

INotify::INotify(const NotifyListener& receiver, void* data) :
	fd(inotify_init()),
	receiver(receiver),
	user_data(data)
{
	if (this->fd == 0)
		throw runtime_error("Failed to initialize inotify");
}

void INotify::watch(const string& path, const int& bitmask)
{
	const int wd=inotify_add_watch(this->fd, path.c_str(), bitmask);
	if(wd < 0)
		throw runtime_error(string("Failed to add watch: ") + path.c_str());
	if (!this->hasWatch(path))
		this->watches.insert(WatchMap::value_type(wd, path));
}

void INotify::watch(const string& path)
{
	this->watch(path, IN_ALL_EVENTS);
}

void INotify::removeWatch(const string& path)
{
	int wd=this->getWatchFD(path);
	if (wd > 0) {
		inotify_rm_watch(this->fd, wd);
		this->watches.erase(wd);
	}
}

bool INotify::hasWatch(const string& path)
{
	return this->getWatchFD(path) != 0;
}

int INotify::getWatchFD(const string& path)
{
	for (WatchMap::iterator i=this->watches.begin(); i != this->watches.end(); i++) {
		if (path == i->second)
			return i->first;
	}
	return 0;
}

void INotify::readEvents() {
	int i=0;
	int length=0;
	do {
		length = read(this->fd, this->buffer, BUF_LEN);  
		if (length < 0)
			throw runtime_error("Failed to read next inotify event");
		const inotify_event& event = (const inotify_event&)buffer[i];
		this->dispatchEvent(event);
		i += EVENT_SIZE + event.len;
	} while (i < length);
}

void INotify::dispatchEvent(const inotify_event& event) {
	const string& source = this->watches[event.wd];
	string path;
	if (event.len)
		path=string(event.name);
	if (event.mask & IN_Q_OVERFLOW)
		throw runtime_error("inotify's internal queue has overflowed");
	this->receiver(source, path, event, user_data);
}

INotify::~INotify()
{
	close(this->fd);
}
