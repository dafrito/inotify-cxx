#ifndef INOTIFYLISTENER_H
#define INOTIFYLISTENER_H

#include <string>

using std::string;

class INotifyListener
{
public:
	/**
	 * Handle when a new watch is added.
	 */
	virtual void watch_added(const string& watch) {};

	/**
	 * Event that is fired when a file is created.
	 */
	virtual void file_created(const string& source, const string& path) {};

	/**
	 * Handle IN_OPEN events.
	 *
	 * File was opened.
	 */
	virtual void file_opened(const string& source, const string& path) {};

	/**
	 * Handle IN_ACCESS events.
	 *
	 * File was read from. 
	 */
	virtual void file_accessed(const string& source, const string& path) {};

	/**
	 * Handle IN_MODIFY events.
	 *
	 * File was written to.
	 */
	virtual void file_written(const string& source, const string& path) {};

	/**
	 * Handle IN_ATTRIB events.
	 *
	 * File's metadata (inode or xattr) was changed.
	 */
	virtual void file_attr_changed(const string& source, const string& path) {};

	/**
	 * Handle IN_MOVED_FROM events.
	 *
	 * File was moved away from watch.
	 */
	virtual void file_moving(const string& source, const string& path) {};

	/**
	 * Handle IN_MOVED_TO events.
	 *
	 * File was moved to watch.
	 */
	virtual void file_moved(const string& source, const string& path) {};

	/**
	 * Handle IN_CLOSE_WRITE and IN_CLOSE_NOWRITE events.
	 *
	 * File was closed.
	 */
	virtual void file_closed(const string& source, const string& path) {};

	/**
	 * Handle IN_DELETE and IN_DELETE_SELF events.
	 *
	 * File was deleted.
	 */
	virtual void file_deleted(const string& source, const string& path) {};

	/**
	 * Handle IN_IGNORED, and IN_UNMOUNT events.
	 *
	 * The backing filesystem was unmounted.
	 * The watch was automatically removed, because the file was deleted or 
	 * its filesystem was unmounted.
	 */
	virtual void watch_removed(const string& source) {}
};

#endif
