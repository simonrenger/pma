#ifndef PMA_AS_LL_HPP_INCLUDED
#define PMA_AS_LL_HPP_INCLUDED
#include <astd/utils/stack_linked_list.hpp>
namespace astd {
	namespace utils {
		template<typename T>
		class linked_list {
			details::node<T>* head{ nullptr };
		public:
            linked_list() = default;
            linked_list(linked_list&) = delete;
		public:
			using node_ptr = details::node<T>*;
		public:
            void insert(node_ptr previousNode, node_ptr newNode);
            void remove(node_ptr previousNode, node_ptr deleteNode);
            void reset();
            node_ptr begin();
		};
	}
}


// implementations:
template<typename T>
void astd::utils::linked_list<T>::reset() {
    head = nullptr;
}

template<typename T>
astd::utils::details::node<T>* astd::utils::linked_list<T>::begin() {
    return head;
}

template<typename T>
void astd::utils::linked_list<T>::insert(node_ptr previous_node,node_ptr new_node) {
    if (previous_node == nullptr) {
        if (head != nullptr) {
            new_node->next = head;
        }
        else {
            new_node->next = nullptr;
        }
        head = new_node;
    }
    else {
        if (previous_node->next == nullptr) {
            previous_node->next = new_node;
            new_node->next = nullptr;
        }
        else {
            new_node->next = previous_node->next;
            previous_node->next = new_node;
        }
    }
}

template<typename T>
void astd::utils::linked_list<T>::remove(node_ptr previous_node, node_ptr to_remove_node) {
    if (previous_node == nullptr) {
        if (to_remove_node->next == nullptr) {
            head = nullptr;
        }
        else {
            head = to_remove_node->next;
        }
    }
    else {
        previous_node->next = to_remove_node->next;
    }
}
#endif