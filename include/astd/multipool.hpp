#ifndef PMA_AS_MPOOL_HPP_INCLUDED
#define PMA_AS_MPOOL_HPP_INCLUDED
#include <pma/defines.hpp>
#include <pma/std_allocator.hpp>
#include <pma/allocation_strategy.hpp>
#include <astd/utils/stack_linked_list.hpp>
#include <astd/monotonic.hpp>
#include <astd/pool.hpp>

#include <vector>

namespace astd {
    class multiplool : public pma::allocation_strategy {
        astd::monotonic buffer{ 0 };
        std::vector<astd::pool*> pools{};
    protected:
        NO_DISCARD  virtual void* do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t aligment) final;
        virtual void do_deallocate(void* const ptr, MAYBE_UNUSED const std::size_t count) final;
        NO_DISCARD virtual bool do_is_equal(const allocation_strategy& that) const noexcept final;
    public:
        multiplool(const std::vector<pma::alloc_option>& pool_options);
        void release();
    };	
}
#endif