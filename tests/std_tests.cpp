#include <pma/eastl_allocator.hpp>

#include <EASTL/vector.h>



class monotonic : public pma::allocation_strategy{
      public:
        monotonic( unsigned char* buffer,std::size_t max):buffer{buffer}, max{max} {};
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

      unsigned char* buffer{nullptr};
     std::size_t max{0};
     std::size_t head{0};
};

int main() {

  unsigned char data[1024]{};
  unsigned char fixedData[2024]{};
  monotonic monotonic_a{data,1024};
  eastl::vector<int,pma::eastl_allocator> vec{&monotonic_a};
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
}
