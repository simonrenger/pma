#include <pma/defines.hpp>
#include <pma/allocation_strategy.hpp>
#include <EASTL/allocator.h>

#include <cstdlib>

#undef EASTL_NAME_ENABLED

namespace pma{
    class eastl_allocator
{
    allocation_strategy* allocationStrategy{nullptr};
public:
    eastl_allocator(const char* pName = EASTL_NAME_VAL("custom eastl::allocator"))
    {
        #if EASTL_NAME_ENABLED
            mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
        #endif

        // Possibly do something here.
    }

    eastl_allocator(const eastl::allocator& x, const char* pName = EASTL_NAME_VAL("custom eastl::allocator"))
    {
        #if EASTL_NAME_ENABLED
            mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
        #endif

        // Possibly copy from x here.
    }

    eastl_allocator(allocation_strategy* allocationStrategy): allocationStrategy{allocationStrategy} {};

    ~eastl_allocator() = default;

    eastl_allocator& operator=(const eastl_allocator& x)
    {
        // Possibly copy from x here.
        return *this;
    }

    void* allocate(size_t n, int flags = 0)
    {
        if(allocationStrategy != nullptr){
            return  allocationStrategy->allocate(n,4);
        }else{
            return std::malloc(n);
        }
    }

    void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0)
    {
        if(allocationStrategy != nullptr){
            return allocationStrategy->allocate(n,alignment);
        }else{
            #if __cplusplus == 201703L
            return std::aligned_alloc(alignment,n);
            #else
            return std::malloc(n);
            #endif
        }
    }

    void deallocate(void* ptr, size_t n)
    {
        if(allocationStrategy != nullptr){
            allocationStrategy->deallocate(ptr,n);
        }else{
            std::free(ptr);
        }
    }

    const char* get_name() const
    {
        #if EASTL_NAME_ENABLED
            return mpName;
        #else
            return "custom eastl::allocator";
        #endif
    }

    void set_name(const char* pName)
    {
        #if EASTL_NAME_ENABLED
            mpName = pName;
        #endif
    }

protected:
    // Possibly place instance data here.

    #if EASTL_NAME_ENABLED
        const char* mpName; // Debug name, used to track memory.
    #endif
};


inline bool operator==(const eastl::allocator& a, const eastl::allocator& b)
{
    // Provide a comparison here.
}

inline bool operator!=(const eastl::allocator& a, const eastl::allocator& b)
{
    // Provide a negative comparison here.
}
}