class INotifyListener
{
public:
	/**
	 * Handle when a new watch is added.
	 */
	virtual void watch_added() {};

	/**
	 * Handle IN_OPEN events.
	 *
	 * File was opened.
	 */
	virtual void file_opened() {};

	/**
	 * Handle IN_ACCESS events.
	 *
	 * File was read from. 
	 */
	virtual void file_accessed() {};

	/**
	 * Handle IN_MODIFY events.
	 *
	 * File was written to.
	 */
	virtual void file_written() {};

	/**
	 * Handle IN_ATTRIB events.
	 *
	 * File's metadata (inode or xattr) was changed.
	 */
	virtual void file_attr_changed() {};

	/**
	 * Handle IN_MOVED_FROM events.
	 *
	 * File was moved away from watch.
	 */
	virtual void file_moving() {};

	/**
	 * Handle IN_MOVED_TO events.
	 *
	 * File was moved to watch.
	 */
	virtual void file_moved() {};

	/**
	 * Handle IN_CLOSE_WRITE and IN_CLOSE_NOWRITE events.
	 *
	 * File was closed.
	 */
	virtual void file_closed() {};

	/**
	 * Handle IN_DELETE events.
	 *
	 * File was deleted.
	 */
	virtual void file_deleted() {};

	/**
	 * Handle IN_DELETE_SELF, IN_IGNORED, and IN_UNMOUNT events.
	 *
	 * The backing filesystem was unmounted.
	 * The watch was automatically removed, because the file was deleted or 
	 * its filesystem was unmounted.
	 */
	virtual void watch_removed() {};
};
