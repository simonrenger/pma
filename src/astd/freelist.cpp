#include <astd/freelist.hpp>
#include <pma/utils.hpp>


#include <cstdlib>

NO_DISCARD void* astd::freelist::do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t alignment) {

    const std::size_t allocation_header_size{ sizeof(details::alloc_header) };
    const std::size_t free_header_size{sizeof(details::free_header)};
    assertm(size >= sizeof(utils::details::node<details::free_header>), "Allocation size must be bigger");
    assertm(alignment >= 8, "Alignment must be 8 at least");

    // Search through the free list for a free block that has enough space to allocate our data
    std::size_t padding{ 0 };
    details::node_ptr affected_node{ nullptr };
    details::node_ptr previous_node{ nullptr };
    find(size, alignment, padding, previous_node, affected_node);
    assertm(affected_node != nullptr ,"Not enough memory");


    const std::size_t alignment_padding{ padding - allocation_header_size };
    const std::size_t required_size{ size + padding };

    const std::size_t rest{ affected_node->data.blockSize - required_size };

    if (rest > 0) {
        details::node_ptr new_free_node{ reinterpret_cast<details::node_ptr>((std::size_t) affected_node + required_size) };
        new_free_node->data.blockSize = rest;
        free_list.insert(affected_node, previous_node);
    }
    free_list.remove(previous_node, affected_node);

    // Setup data block
    const std::size_t header_address{ reinterpret_cast<std::size_t>(affected_node + alignment_padding) };
    const std::size_t data_address{ header_address + allocation_header_size };
    reinterpret_cast<details::alloc_header*>(header_address)->blockSize =required_size;
    reinterpret_cast<details::alloc_header*>(header_address)->padding = alignment_padding;
    return reinterpret_cast<void*>(data_address);
}
void astd::freelist::do_deallocate(void* const ptr, MAYBE_UNUSED const std::size_t size) {
    // Insert it in a sorted position by the address number
    const std::size_t current_address{ reinterpret_cast<std::size_t>(ptr) };
    const std::size_t header_address{ current_address - sizeof(details::alloc_header) };
    const details::alloc_header* allocation_Header{ reinterpret_cast<details::alloc_header*>(header_address) };

    details::node_ptr free_node = reinterpret_cast<details::node_ptr>(header_address);
    free_node->data.blockSize = allocation_Header->blockSize + allocation_Header->padding;
    free_node->next = nullptr;

    auto it = free_list.begin();
    decltype(it) itPrev = nullptr;
    while (it != nullptr) {
        if (ptr < it) {
            free_list.insert(itPrev, free_node);
            break;
        }
        itPrev = it;
        it = it->next;
    }
    coalescence(itPrev, free_node);
}

NO_DISCARD bool astd::freelist::do_is_equal(const pma::allocation_strategy& that) const noexcept {
	return &that == this;
}


void astd::freelist::find(const std::size_t size, const std::size_t alignment, std::size_t& padding, details::node_ptr& previousNode, details::node_ptr& foundNode) {
    auto it{ free_list.begin() };
    decltype(it) itPrev{ nullptr };

    while (it != nullptr) {
        padding = pma::alignForwardAdjustmentWithHeader((std::size_t)it, alignment, sizeof(details::alloc_header));
        const std::size_t requiredSpace{ size + padding };
        if (it->data.blockSize >= requiredSpace) {
            break;
        }
        itPrev = it;
        it = it->next;
    }
    previousNode = itPrev;
    foundNode = it;
}


void astd::freelist::coalescence(details::node_ptr prev_block, details::node_ptr free_block) {
    if (free_block->next != nullptr &&
        (std::size_t) free_block + free_block->data.blockSize == (std::size_t) free_block->next) {
        free_block->data.blockSize += free_block->next->data.blockSize;
        free_list.remove(free_block, free_block->next);
    }

    if (prev_block != nullptr &&
        (std::size_t) prev_block + prev_block->data.blockSize == (std::size_t) prev_block) {
        prev_block->data.blockSize += free_block->data.blockSize;
        free_list.remove(prev_block, free_block);
    }
}


astd::freelist::freelist(pma::alloc_option option, allocation_strategy* const upstream) : allocation_strategy{ option, upstream } {
    start_ptr = std::malloc(option.buffer_size);
    release();
}

void astd::freelist::release() {

    details::node_ptr first_node{ reinterpret_cast<details::node_ptr>(start_ptr) };
    first_node->data.blockSize = option.buffer_size;
    first_node->next = nullptr;
    free_list.reset();
    free_list.insert(nullptr, first_node);

}