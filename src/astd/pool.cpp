#include <astd/pool.hpp>
#include <pma/utils.hpp>

#include <cstdlib>
#include <cassert>
#if _DEBUG
#include <iostream>
#endif

NO_DISCARD void* astd::pool::do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t aligment) {
	#if _DEBUG
		if (size > option.chunck_size) {
			std::cout << "size is bigger then chnuck try to use upstream\n";
		}
	#endif
	if (size > option.chunck_size) return upstream->allocate(size, aligment);

	details::node_ptr free_pos = free_list.pop();
	assertm(free_pos != nullptr , "The pool allocator is full");
	return free_pos;
}
void astd::pool::do_deallocate(void* const ptr, MAYBE_UNUSED const std::size_t size) {
	if (size > option.chunck_size) return upstream->deallocate(ptr,size);
	free_list.push(reinterpret_cast<details::node_ptr>(ptr));
}

NO_DISCARD bool astd::pool::do_is_equal(const pma::allocation_strategy& that) const noexcept {
    return &that == this;
}


astd::pool::pool(pma::alloc_option option, allocation_strategy* const upstream) : allocation_strategy{ option, upstream } {
	// 8 bytes because the nodes they have pointer size.
	assertm(option.chunck_size >= 8, "Chunk size must be greater or equal to 8");
	assertm(option.buffer_size % option.chunck_size == 0, "Total Size must be a multiple of Chunk Size");
	start_ptr = std::malloc(option.buffer_size);
	release();
}

void astd::pool::release() {
	const auto chuncks{ option.buffer_size / option.chunck_size };
	for (auto i{ 0 }; i < chuncks; ++i) {
		std::size_t address = reinterpret_cast<std::size_t>(start_ptr) + i * option.chunck_size;
		free_list.push(reinterpret_cast<details::node_ptr>(address));
	}
}