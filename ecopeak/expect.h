#ifndef ECOPEAK_EXPECT_H
#define ECOPEAK_EXPECT_H

#include "platform.h"
#if defined(ECOPEAK_COMPILER_GNU_LIKE)



#define ECOPEAK_EXPECT(_expr, _res) __builtin_expect((_expr), (_res))



#else



#define ECOPEAK_EXPECT(_expr, _res) (_expr)



#endif

#endif