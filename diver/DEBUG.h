#ifndef __Debug_h
#define __Debug_h

#define Debug_printf 0

#if Debug_printf
#define debug_printf(fmt, ...)   printf(fmt, ##__VA_ARGS__)
#else
#define debug_printf(fmt, ...)  ((void)0)
#endif

#endif
