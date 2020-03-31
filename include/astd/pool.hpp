#ifndef PMA_AS_POOL_HPP_INCLUDED
#define PMA_AS_POOL_HPP_INCLUDED
#include <pma/defines.hpp>
#include <pma/allocation_strategy.hpp>
#include <astd/utils/stack_linked_list.hpp>

namespace astd{
    namespace details {
        struct free_header {};
        using node_ptr = utils::stack_linked_list<details::free_header>::node_ptr;
    };
class pool : public pma::allocation_strategy{
    void* start_ptr{ nullptr };
    utils::stack_linked_list<details::free_header> free_list{};
protected:
    NO_DISCARD  virtual void* do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t aligment) final;
    virtual void do_deallocate(void* const ptr, MAYBE_UNUSED const std::size_t count) final;
    NO_DISCARD virtual bool do_is_equal(const allocation_strategy& that) const noexcept final;
public:
    pool(pma::alloc_option option, allocation_strategy* const upstream = nullptr);
    void release();
};
}
#endif