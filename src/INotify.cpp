#include <map>
#include <iostream>
#include <stdexcept>
#include "INotify.hpp"

using namespace std;

INotify::INotify() :
	fd(inotify_init())
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

void INotify::addListener(INotifyListener* const listener)
{
	this->listeners.push_back(listener);
}

bool INotify::removeListener(INotifyListener* const listener)
{
	// XXX Stubbed
	return false;
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

#define run_event(event_name) \
{ \
	for(unsigned int i=0; i < this->listeners.size(); i++) \
		this->listeners[i]->event_name(source, path); \
}

void INotify::dispatchEvent(const inotify_event& event) {
	const string& source = this->watches[event.wd];
	string path;
	if (event.len)
		path=string(event.name);
	/*
	 * run_event depends on source and path, so if these are renamed, the macro
	 * will have to be changed as well.
	 */
	if (event.mask & IN_Q_OVERFLOW) {
		throw runtime_error("inotify's internal queue has overflowed");
	} else if (event.mask & IN_OPEN) {
		run_event(file_opened);
	} else if (event.mask & IN_CREATE) {
		run_event(file_created);
	} else if (event.mask & IN_ACCESS) {
		run_event(file_accessed);
	} else if (event.mask & IN_MODIFY) {
		run_event(file_written);
	} else if (event.mask & IN_ATTRIB) {
		run_event(file_attr_changed);
	} else if (event.mask & IN_MOVED_FROM) {
		run_event(file_moving);
	} else if (event.mask & IN_MOVED_TO) {
		run_event(file_moved);
	} else if (event.mask & IN_CLOSE) {
		run_event(file_closed);
	} else if (event.mask & (IN_DELETE | IN_DELETE_SELF)) {
		run_event(file_deleted);
	} else if (event.mask & (IN_IGNORED | IN_UNMOUNT)) {
		for(unsigned int i=0; i < this->listeners.size(); i++)
			this->listeners[i]->watch_removed(source);
	} else {
		std::cerr << "Unhandled event mask: " << event.mask;
		throw runtime_error("Event mask was not handled");
	}
}

INotify::~INotify()
{
	close(this->fd);
}
