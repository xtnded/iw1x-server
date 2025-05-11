#ifndef PCH_H
#define PCH_H

// Linux
#include <unistd.h>     // access
#include <arpa/inet.h>  // sockaddr_in, inet_pton
#include <execinfo.h>   // backtrace
#include <dlfcn.h>      // dlsym
#include <sys/time.h>   // gettimeofday
#include <linux/limits.h>   // PATH_MAX
#include <signal.h>     // signal

// C++
#include <array>
#include <cmath>        // fabs, sqrt
#include <cstdarg>      // va_start, va_end
#include <cstdio>       // printf, snprintf
#include <cstring>      // strcasecmp, strlen, strcmp, strerror, strncpy...
#include <filesystem>
#include <map>          // make_tuple, get, array
#include <sstream>      // ostringstream
#include <string>
#include <vector>

#endif