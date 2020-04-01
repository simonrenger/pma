#ifndef PMA_AS_FREE_HPP_INCLUDED
#define PMA_AS_FREE_HPP_INCLUDED
#include <pma/defines.hpp>
#include <pma/allocation_strategy.hpp>
#include <astd/utils/linked_list.hpp>

namespace astd{
    namespace details {
        struct free_header {
            std::size_t blockSize{};
        };
        struct alloc_header {
            std::size_t blockSize{};
            char padding{};
        };
        using node_ptr = utils::linked_list<free_header>::node_ptr;
    }
    class freelist : public pma::allocation_strategy{
        void* start_ptr{ nullptr };
        utils::linked_list<details::free_header> free_list{};
    private:
        void coalescence(details::node_ptr prevBlock, details::node_ptr freeBlock);
        void find(const std::size_t size, const std::size_t alignment, std::size_t& padding, details::node_ptr& previousNode, details::node_ptr& foundNode);
    protected:
        NO_DISCARD  virtual void* do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t aligment) final;
        virtual void do_deallocate(void* const ptr, MAYBE_UNUSED const std::size_t count) final;
        NO_DISCARD virtual bool do_is_equal(const allocation_strategy& that) const noexcept final;
    public:
        freelist(pma::alloc_option option, allocation_strategy* const upstream = nullptr);
        void release();
    };
}
#endif
