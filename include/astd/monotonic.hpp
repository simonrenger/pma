#ifndef PMA_AS_MONO_HPP_INCLUDED
#define PMA_AS_MONO_HPP_INCLUDED
#include <pma/defines.hpp>
#include <pma/allocation_strategy.hpp>
namespace astd{
    class monotonic : public pma::allocation_strategy{
        void* start_ptr{ nullptr };
        std::size_t head{ 0 };
    protected:
        NO_DISCARD  virtual void* do_allocate(const std::size_t count, MAYBE_UNUSED const std::size_t aligment) final;
        virtual void do_deallocate(MAYBE_UNUSED void* const ptr, MAYBE_UNUSED const std::size_t count) final;
        NO_DISCARD virtual bool do_is_equal(const allocation_strategy& that) const noexcept final;
    public:
        monotonic(std::size_t max_buffer, allocation_strategy *const upstream = nullptr);
        monotonic(pma::alloc_option option,allocation_strategy *const upstream = nullptr);
        void release();
    };
}
#endif