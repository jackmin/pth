#ifndef __RDTSC_H__
#define __RDTSC_H__
#include <sys/types.h>

typedef unsigned long long u64;

#ifdef __x86_64__
#define DECLARE_ARGS(val, low, high)    unsigned low, high
#define EAX_EDX_VAL(val, low, high)     ((low) | ((u64)(high) << 32))
#define EAX_EDX_ARGS(val, low, high)    "a" (low), "d" (high)
#define EAX_EDX_RET(val, low, high)     "=a" (low), "=d" (high)
#else
#define DECLARE_ARGS(val, low, high)    unsigned long long val
#define EAX_EDX_VAL(val, low, high)     (val)
#define EAX_EDX_ARGS(val, low, high)    "A" (val)
#define EAX_EDX_RET(val, low, high)     "=A" (val)
#endif

static inline unsigned long long __rdtscll(void)
{
	DECLARE_ARGS(val, low, high);

	asm volatile("cpuid; rdtsc" : EAX_EDX_RET(val, low, high));

	return EAX_EDX_VAL(val, low, high);
}

#define rdtscll(val) do { (val) = __rdtscll(); } while (0)
#endif
