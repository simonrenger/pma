#ifndef PMA_AS_FREE_HPP_INCLUDED
#define PMA_AS_FREE_HPP_INCLUDED
#include <pma/defines.hpp>
#include <pma/allocation_strategy.hpp>
namespace astd{
    class freelist : public pma::allocation_strategy{
        NO_DISCARD  virtual void* do_allocate(const std::size_t size, const std::size_t aligment) final {
            // impl
            return nullptr;
        }
        virtual void do_deallocate(void* const ptr,const std::size_t count) final {
        // impl
        }
    };
}
#endif
