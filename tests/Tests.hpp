#include <cxxtest/TestSuite.h>
#include <INotify.hpp>

using namespace std;

class Tests : public CxxTest::TestSuite
{
public:
	void testMySanity()
	{
		INotify notify;
		notify.watch(".");
	}
};
