#ifndef PMA_DEFINE_HPP_INCLUDED
#define PMA_DEFINE_HPP_INCLUDED

#include <cassert>
	#define assertm(exp, msg) assert(((void)msg, exp))

	#if __cplusplus == 201703L
	#define NO_DISCARD [[nodiscard]]
	#else
	#define NO_DISCARD 
	#endif

#endif