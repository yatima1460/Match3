#pragma once

#ifdef __GNUC__
#define PURE_FUNCTION __attribute__((pure))
#define CONST_FUNCTION __attribute__((const))
#else
#ifdef _MSC_VER
#pragma message("Warning: MSC compiler does not support pure and const attributes")
#endif
#define PURE_FUNCTION
#define CONST_FUNCTION
#endif
