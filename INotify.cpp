#include <map>
#include <stdexcept>
#include "INotify.hpp"
#include <cstdio>

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
	if (!this->has_watch(path))
		this->watches.insert(WatchMap::value_type(wd, path));
}

void INotify::watch(const string& path)
{
	this->watch(path, IN_ALL_EVENTS);
}

void INotify::remove_watch(const string& path)
{
	int wd=this->get_watch_fd(path);
	if (wd > 0) {
		inotify_rm_watch(this->fd, wd);
		this->watches.erase(wd);
	}
}

bool INotify::has_watch(const string& path)
{
	return this->get_watch_fd(path) != 0;
}

int INotify::get_watch_fd(const string& path)
{
	for (WatchMap::iterator i=this->watches.begin(); i != this->watches.end(); i++) {
		if (path == i->second)
			return i->first;
	}
	return 0;
}

void INotify::add_listener(const INotifyListener* const listener)
{
	this->listeners.push_back(listener);
}

bool INotify::remove_listener(const INotifyListener* const listener)
{
	// XXX Stubbed
	return false;
}

void INotify::read_events() {
	int i=0;
	int length=0;
	do {
		length = read(this->fd, this->buffer, BUF_LEN);  
		if (length < 0)
			throw runtime_error("Failed to read next inotify event");
		inotify_event *event = (inotify_event*) &buffer[i];
		this->dispatch_event(*event);
		i += EVENT_SIZE + event->len;
	} while (i < length);
}

void INotify::dispatch_event(const inotify_event& event) {
	if (event.mask & IN_Q_OVERFLOW)
		throw runtime_error("inotify's internal queue has overflowed");
	if ( event.len ) {
		if ( event.mask & IN_CREATE ) {
			if ( event.mask & IN_ISDIR ) {
				printf( "The directory %s was created.\n", event.name );
			}
			else {
				printf( "The file %s was created.\n", event.name );
			}
		} else if ( event.mask & IN_DELETE ) {
			if ( event.mask & IN_ISDIR ) {
				printf( "The directory %s was deleted.\n", event.name );       
			} else {
				printf( "The file %s was deleted.\n", event.name );
			}
		} else if ( event.mask & IN_MODIFY ) {
			if ( event.mask & IN_ISDIR ) {
				printf( "The directory %s was modified.\n", event.name );
			} else {
				printf( "The file %s was modified.\n", event.name );
			}
		}
	}
}

INotify::~INotify()
{
	close(this->fd);
}
