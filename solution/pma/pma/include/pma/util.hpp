#include <cstdint>
namespace pma {
    /// IMPORTANT: The alignment must be a power of 2!

    inline std::size_t alignForwardAdjustment(void* address, std::size_t alignment)
    {
        const size_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address)& static_cast<uintptr_t>(alignment - 1));

        if (adjustment == alignment) return 0;

        return adjustment;
    }

    inline void* add(void* p, size_t x)
    {
        return (void*)(reinterpret_cast<uintptr_t>(p) + x);
    }

    inline const void* add(const void* p, size_t x)
    {
        return (const void*)(reinterpret_cast<uintptr_t>(p) + x);
    }

    template<typename T>
    inline uintptr_t alignForwardAdjustmentWithHeader(const void* address, uintptr_t alignment)
    {
        if (__alignof(T) > alignment)
            alignment = __alignof(T);

        return sizeof(T) + alignForwardAdjustment(add(address, sizeof(T)), alignment);
    }

    inline std::uint8_t alignForwardAdjustmentWithHeader(void* address, std::uint8_t alignment, std::uint8_t headerSize)
    {
        std::uint8_t adjustment = alignForwardAdjustment(address, alignment);
        std::uint8_t neededSpace = headerSize;

        if (adjustment < neededSpace)
        {
            neededSpace -= adjustment;

            //Increase adjustment to fit header 
            adjustment += alignment * (neededSpace / alignment);

            if (neededSpace % alignment > 0) adjustment += alignment;
        }

        return adjustment;
    }
}