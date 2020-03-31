#ifndef PMA_DEFINE_HPP_INCLUDED
#define PMA_DEFINE_HPP_INCLUDED

#include <cassert>
	#define assertm(exp, msg) assert(((void)msg, exp))

	#if __cplusplus == 201703L
	#define MAYBE_UNUSED [[maybe_unused]]
	#define NO_DISCARD [[nodiscard]]
	#else
	#define NO_DISCARD
	#define MAYBE_UNUSED
	#endif

#endif