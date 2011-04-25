TESTS=$(check_PROGRAMS)
check_PROGRAMS=runtests
runtests_SOURCES=runtests.cpp $(testheaders)
testheaders = Tests.hpp
runtests_LDADD=../src/libinotify-cxx.la

runtests.cpp: $(testheaders)
	cxxtestgen -o $@ --error-printer $^
