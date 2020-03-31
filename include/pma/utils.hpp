#ifndef PMA_AS_UTILS_HPP_INCLUDED
#define PMA_AS_UTILS_HPP_INCLUDED

#include <cstdint>
namespace pma {
    /// IMPORTANT: The alignment must be a power of 2!
    inline std::size_t alignForwardAdjustment(const std::size_t baseAddress, const std::size_t alignment)
    {
        const std::size_t multiplier{ (baseAddress / alignment) + 1 };
        const std::size_t alignedAddress {multiplier * alignment };
        const std::size_t padding { alignedAddress - baseAddress };
        return padding;
    }

    inline void* add(void* p, size_t x)
    {
        return (void*)(reinterpret_cast<uintptr_t>(p) + x);
    }

    inline const void* add(const void* p, size_t x)
    {
        return (const void*)(reinterpret_cast<uintptr_t>(p) + x);
    }


    inline std::uint8_t alignForwardAdjustmentWithHeader(const std::size_t baseAddress, const std::size_t alignment, const std::size_t headerSize)
    {
        std::size_t padding{ alignForwardAdjustment(baseAddress, alignment) };
        std::size_t neededSpace { headerSize};

        if (padding < neededSpace) {
            // Header does not fit - Calculate next aligned address that header fits
            neededSpace -= padding;

            // How many alignments I need to fit the header        
            if (neededSpace % alignment > 0) {
                padding += alignment * (1 + (neededSpace / alignment));
            }
            else {
                padding += alignment * (neededSpace / alignment);
            }
        }

        return padding;
    }
}
#endif