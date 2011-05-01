TESTS=$(check_PROGRAMS)
check_PROGRAMS=runtests
runtests_SOURCES=runtests.cpp $(testheaders)
runtests_CPPFLAGS=-I../inotify-cxx --std=c++0x
testheaders = Tests.hpp
runtests_LDADD=../inotify-cxx/libinotify-cxx.la

runtests.cpp: $(testheaders)
	cxxtestgen -o $@ --error-printer $^
