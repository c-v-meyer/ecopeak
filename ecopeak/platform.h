#ifndef ECOPEAK_PLATFORM_H
#define ECOPEAK_PLATFORM_H

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)))
#define ECOPEAK_PLATFORM_UNIX_LIKE
#elif defined(_WIN32) || defined(_WIN64)
#define ECOPEAK_PLATFORM_WINDOWS
#endif

#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#define ECOPEAK_COMPILER_GNU_LIKE
#elif defined(_MSC_VER)
#define ECOPEAK_COMPILER_MS
#endif

#endif