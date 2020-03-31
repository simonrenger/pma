#include <astd/monotonic.hpp>
#include <pma/utils.hpp>

#include <cstdlib>

astd::monotonic::monotonic(std::size_t max_size, pma::allocation_strategy* const upstream) :allocation_strategy{ {max_size},upstream }{
    start_ptr = std::malloc(max_size);
}
astd::monotonic::monotonic(pma::alloc_option option,pma::allocation_strategy * const upstream) :allocation_strategy{ option,upstream }{
    start_ptr = std::malloc(option.buffer_size);
}

NO_DISCARD void* astd::monotonic::do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t alignment) {

    std::size_t padding {0};
    const std::size_t currentAddress = (std::size_t)start_ptr + head;
    if (alignment != 0 && head % alignment != 0) {
        padding = pma::alignForwardAdjustment(currentAddress, alignment);
    }
    if (head + padding + size > option().buffer_size) {
        return nullptr;
    }
    head += padding;
    const std::size_t nextAddress = currentAddress + padding;
    head += size;
    return (void*)nextAddress;
}
void astd::monotonic::do_deallocate(MAYBE_UNUSED void* const ptr, MAYBE_UNUSED const std::size_t count)  {
    // do nothing
}

NO_DISCARD bool astd::monotonic::do_is_equal(const pma::allocation_strategy& that) const noexcept {
    return &that == this;
}

void astd::monotonic::release() {
    head = 0;
}