#pragma once

#ifdef __GNUC__

// Maybe other libraries will already define them

#define PURE_FUNCTION __attribute__((pure))


#define CONST_FUNCTION  __attribute__((const))

#else

// compiler does not support pure and const attributes

#define PURE_FUNCTION


#define CONST_FUNCTION 


#endif