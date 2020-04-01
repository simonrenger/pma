#include <astd/multipool.hpp>
#include <astd/pool.hpp>
#include <pma/utils.hpp>

#include <cstdlib>
#include <cassert>
#include <vector>



astd::multiplool::multiplool(const std::vector<pma::alloc_option>& pool_options) :buffer{ pool_options.size() * sizeof(astd::pool) } {
	pools.resize(pool_options.size(),nullptr);
	for (auto i{ pool_options.size()-1 }; i > 0; --i) {
		auto* storage{ buffer.allocate(sizeof(astd::pool), alignof(astd::pool)) };
		auto* pool{ new (storage) astd::pool{pool_options[i],nullptr} };
		pools[i] =pool;
	}
}

NO_DISCARD void* astd::multiplool::do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t aligment) {
	return pools[0]->allocate(size, aligment);
}
void astd::multiplool::do_deallocate(void* const ptr, MAYBE_UNUSED const std::size_t size) {
	pools[0]->deallocate(ptr, size);
}

NO_DISCARD bool astd::multiplool::do_is_equal(const pma::allocation_strategy& that) const noexcept {
	return &that == this;
}



void astd::multiplool::release() {
	for (auto* pool : pools) {
		pool->release();
	}
}