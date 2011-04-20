#ifndef HPP_INOTIFYPRINTLISTENER
#define HPP_INOTIFYPRINTLISTENER

#include <string>
#include "INotifyListener.hpp"

using std::string;

class INotifyPrintListener : public INotifyListener {
public:
	void file_written(const string& source, const string& path);
	void file_created(const string& source, const string& path);
	void file_opened(const string& source, const string& path);
	void file_closed(const string& source, const string& path);
	void file_deleted(const string& source, const string& path);
};

#endif
