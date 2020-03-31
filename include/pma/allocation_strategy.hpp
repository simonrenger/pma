#ifndef PMA_AS_HPP_INCLUDED
#define PMA_AS_HPP_INCLUDED
#include <pma/defines.hpp>
#include <pma/alloc_option.hpp>

#include <cstddef>
namespace pma{
    class allocation_strategy{
        public:
        allocation_strategy() = default;
        allocation_strategy(pma::alloc_option option, allocation_strategy* const upstream = nullptr) :option{ option }, upstream{ upstream } {}
        virtual ~allocation_strategy() noexcept {}

        void deallocate(void* const ptr, const std::size_t size) {
            this->do_deallocate(ptr,size);
        }

        NO_DISCARD void* allocate(const std::size_t size, std::size_t aligment) {
            return this->do_allocate(size,aligment);
        }

        NO_DISCARD bool is_equal(const allocation_strategy& that) const noexcept {
            return do_is_equal(that);
        }

#if _DEBUG
        NO_DISCARD const allocation_strategy* const  debug_upstream() const {
            return upstream;
        }

        NO_DISCARD const pma::alloc_option& debug_option() const {
            return option;
        }
#endif
    protected:
        NO_DISCARD  virtual void* do_allocate(const std::size_t size, MAYBE_UNUSED const std::size_t aligment) = 0;
        virtual void do_deallocate(MAYBE_UNUSED void* const ptr, MAYBE_UNUSED const std::size_t size) = 0;
        NO_DISCARD virtual bool do_is_equal(const allocation_strategy& that) const noexcept = 0;
        allocation_strategy* const upstream{ nullptr };
        pma::alloc_option option{};
    };

NO_DISCARD inline bool operator==(const allocation_strategy& left, const allocation_strategy& right) noexcept {
 return &left == &right || left.is_equal(right);
}

NO_DISCARD inline bool operator!=(const allocation_strategy& left, const allocation_strategy& right) noexcept {
    return !(left == right);
}


}
#endif