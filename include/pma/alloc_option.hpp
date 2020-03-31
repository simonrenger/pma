#include <cstddef>

namespace pma {
	struct alloc_option {
		std::size_t buffer_size{};
		std::size_t chunck_size{};
	};
}