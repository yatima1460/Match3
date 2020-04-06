#pragma once

#ifdef __GNUC__

#define PURE __attribute__((pure))
#define CONST __attribute__((const))

#else

// compiler does not support pure and const attributes
#define PURE
#define CONST

#endif