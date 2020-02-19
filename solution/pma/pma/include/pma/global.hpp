#ifndef PMA_AS_GLOBAL_HPP_INCLUDED
#define PMA_AS_GLOBAL_HPP_INCLUDED
namespace pma{
    class allocation_strategy;
    void init_global_allocation_strategy();
    allocation_strategy* get_global_allocation_strategy();
}
#endif