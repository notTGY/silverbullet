/**
 * Read more about this header here:
 * https://www.cs.colostate.edu/~fsieker/misc/debug/DEBUG.html
 */

#ifndef __DEBUG__
#define __DEBUG__

#ifdef DEBUG
#define debug(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...) ((void)0)
#endif

#endif

