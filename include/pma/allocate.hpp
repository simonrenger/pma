#include "utils.hpp"

#include <cstddef>
#include <cstring>
namespace pma{

    /*
    example:
    struct TestStruct{
        int member{0};
    };
    unsigned char data_container[1024]{};
    pma::init_memory(data_container, 1024);
    int count{ 0 };
    auto object{ pma::allocate_in<TestStruct>(5,alignof(TestStruct),data_container) };

    object[0].member = 0;
    object[1].member = 1;
    object[2].member = 2;
    object[3].member = 3;
    object[4].member = 4;
    */

    namespace detail{
        struct Header{
            std::size_t head{};
            std::size_t capacity{};
        };
    };
    void init_memory(unsigned char* memory,std::size_t size){
        detail::Header header{sizeof(detail::Header),size};
        memmove(&memory[0], &header, sizeof(detail::Header) );
    }
    template<typename T>
    T* allocate_in(std::size_t count,std::size_t aligment,unsigned char* data){
        pma::detail::Header header{};
        memcpy(&header, &data[0], sizeof(pma::detail::Header));
        std::uint8_t adjustment = pma::alignForwardAdjustment(&data[header.head], aligment);
        header.head += (sizeof(T) * count)+ adjustment;
        assertm(header.head <= header.capacity, "Cannot Allocate");
        auto offset{ (sizeof(T)*count) + adjustment + sizeof(detail::Header)};
        T* ptr = new (&data[offset]) T{};
        memcpy(&data[0], &header, sizeof(pma::detail::Header));
        return ptr;
    };

    void release_all(unsigned char* data){
        pma::detail::Header header{};
        memcpy(&header, &data[0], sizeof(pma::detail::Header));
        header.head = sizeof(pma::detail::Header);
        memcpy(&data[0], &header, sizeof(pma::detail::Header));
    };
}