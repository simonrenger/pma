#include <pma/std_allocator.hpp>
#include <pma/allocate.hpp>
#include <astd/monotonic.hpp>

#include <iostream>
#include <vector>
#include <memory>
#if __cplusplus == 201703L
#include <memory_resource>
#endif

int main() {
	astd::monotonic montonic_allocator{2024};
	std::vector<int, pma::allocator<int>> vec{ montonic_allocator };
};
