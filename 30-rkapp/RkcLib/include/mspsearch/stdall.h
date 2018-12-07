#ifndef STDALL_H
#define STDALL_H

#ifdef WIN32
	#include <winsock2.h>
	#include <windows.h>
	#include <assert.h>
	#pragma comment(lib,"Ws2_32.lib")
#else
#include <arpa/inet.h>
#endif

#include <deque>

#include <string>
#include <string.h>
#include "kdvtype.h"
#include "mspsearch.h"
#include "lock.h"
#include "publicfun.h"
#include "datamanager.h"

using namespace std;

#endif