#include <pma/std_allocator.hpp>
#include <pma/allocate.hpp>

#include <iostream>
#include <vector>
#include <memory>
#if __cplusplus == 201703L
#include <memory_resource>
#endif

#include <EASTL/vector.h>
#include <pma/eastl_allocator.hpp>

#include <cassert>
class monotonic : public pma::allocation_strategy{
      public:
        monotonic(char* buffer,std::size_t max):buffer{buffer}, max{max} {};
      private:
       NO_DISCARD  virtual void* do_allocate(const std::size_t count, const std::size_t aligment) final {
         assert(!((head + count) < head));// "Cannot allocate!"
         auto ptr{buffer + head};
         head += count;
         return static_cast<void*>(ptr);
       }
     virtual void do_deallocate(void* const ptr,const std::size_t count) final {
       //we do nothing
     }

     char* buffer{nullptr};
     std::size_t max{0};
     std::size_t head{0};
};

struct TestStruct{
  int member{0};
};

int main() {
    char data[1024]{};

    monotonic monotonic_alloc{ data,1024 };
    std::vector<TestStruct, pma::allocator<TestStruct>> vec{ &monotonic_alloc };
    vec.push_back({1});
    vec.push_back({2});
    vec.push_back({3});
    vec.push_back({4});
    vec.push_back({5});

    unsigned char data_container[1024]{};
    pma::init_memory(data_container, 1024);
    int count{ 0 };
    auto object{ pma::allocate_in<TestStruct>(1,alignof(TestStruct),data_container) };
    object->member = 0;

#if __cplusplus == 201703L
    std::monotonic_buffer_resource mbr_small{1024};
    std::monotonic_buffer_resource mbr_big{2024,&mbr_small};
    std::pmr::vector<int> pmr_vec{&mbr_big};
    pmr_vec.push_back({1});
    pmr_vec.push_back({2});
    pmr_vec.push_back({3});
    pmr_vec.push_back({4});
    pmr_vec.push_back({5});
#endif
  
  eastl::vector<TestStruct, pma::eastl_allocator> testStructs{};
}
