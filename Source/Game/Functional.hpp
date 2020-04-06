#pragma once




#ifdef __GNUC__

#define PURE __attribute__((pure))
#define CONST __attribute__((const))



#else

#define PURE 
#define CONST 
#warning "compiler does not support pure and const attributes"


#endif