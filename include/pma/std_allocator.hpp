#ifndef PMA_MAIN_HPP_INCLUDED
#define PMA_MAIN_HPP_INCLUDED
#include <pma/defines.hpp>
#include <pma/allocation_strategy.hpp>

#include <type_traits>
#include <stdlib.h>
#if __cplusplus == 201402
    #include <memory>
#endif
namespace pma {

template <typename T>
class allocator {
public:
    using _From_primary = allocator;

    using value_type = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal                        = std::true_type;

#if __cplusplus == 201402
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T& ;
#endif

    private:
    allocation_strategy * allocationStrategy {nullptr};
    public:

    constexpr allocator() noexcept = default;
    constexpr allocator(const allocator&) noexcept = default;
    template <class other>
    constexpr allocator(const allocator<other>&) noexcept {}


    allocator(allocation_strategy* const stratgey):allocationStrategy{stratgey} {};
    allocator(allocation_strategy& stratgey):allocationStrategy{&stratgey} {};

    void deallocate(T* const ptr, const std::size_t count) {
        if(allocationStrategy != nullptr){
            allocationStrategy->deallocate(ptr, sizeof(T) * count);
        }else{
            std::free(ptr);
        }
    }

    NO_DISCARD T* allocate(const std::size_t count) {
        if(allocationStrategy != nullptr){
            return  static_cast<T*>(allocationStrategy->allocate(sizeof(T)*count,alignof(T)));
        }else{
            return static_cast<T*>(std::malloc(sizeof(T) * count));
        }
    }

    NO_DISCARD T* allocate(const std::size_t count, const void*) {
        if(allocationStrategy != nullptr){
            return  static_cast<T*>(allocationStrategy->allocate(sizeof(T) * count,alignof(T)));
        }else{
            return static_cast<T*>(std::malloc(sizeof(T) * count));
        }
    }

    NO_DISCARD allocation_strategy* strategy() const noexcept /* strengthened */ {
        // retrieve this allocator's strategy
        return allocationStrategy;
    }

#if __cplusplus == 201402
    template <class Other>
    struct rebind {
        using other = allocator<Other>;
    };

    NO_DISCARD T* address(T& val) const noexcept {
        return std::addressof(val);
    }

    NO_DISCARD const T* address(const T& val) const noexcept {
        return std::addressof(val);
    }
    template <class O, class... U>
    void construct(O* const _Ptr, U&&... _Args) { 

    }

    template <class U>
    void destroy(U* const ptr) {
        std::free(ptr);
    }

    NO_DISCARD std::size_t max_size() const noexcept {
        return static_cast<size_t>(-1) / sizeof(T);
    }
#endif
}; // end of alloctor class

template <typename T1, typename T2>
NO_DISCARD bool operator==(const pma::allocator<T1>& left, const pma::allocator<T2>& right) noexcept {
    return *left.strategy() == *right.strategy();
}

template <typename T1, typename T2>
NO_DISCARD bool operator!=(const pma::allocator<T1>& left, const pma::allocator<T2>& right) noexcept {
    return !(left == right);
}

}  

#endif // PMA_MAIN_HPP_INCLUDED