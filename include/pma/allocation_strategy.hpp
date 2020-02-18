#ifndef PMA_AS_HPP_INCLUDED
#define PMA_AS_HPP_INCLUDED
#include <pma/defines.hpp>

#include <cstddef>
namespace pma{
    class allocation_strategy{
        public:
        allocation_strategy(){}
        void deallocate(void* const ptr, const std::size_t size) {
            this->do_deallocate(ptr,size);
        }

        NO_DISCARD void* allocate(const std::size_t size, std::size_t aligment) {
            return this->do_allocate(size,aligment);
        }
        NO_DISCARD  virtual void* do_allocate(const std::size_t size, const std::size_t aligment) = 0;
        virtual void do_deallocate(void* const ptr,const std::size_t size) = 0;
    };
}
#endif