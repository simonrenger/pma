#ifndef PMA_AS_SLL_HPP_INCLUDED
#define PMA_AS_SLL_HPP_INCLUDED
namespace astd {
	namespace utils {
		namespace details {
			template<typename T>
			struct node {
				T data{};
				node<T>* next{ nullptr };
			};
		}
		template<typename T>
		class stack_linked_list {
			details::node<T>* head{ nullptr };
		public:
			stack_linked_list() = default;
			stack_linked_list(stack_linked_list&) = delete;
		public:
			using node_ptr = details::node<T>*;
		public:
			void push(node_ptr new_node);
			node_ptr pop();
		};
	}
}


// implementations:

template<typename T>
void astd::utils::stack_linked_list<T>::push(node_ptr new_node) {
	//swap nodes:
	new_node->next = head;
	head = new_node;
}

template<typename T>
astd::utils::details::node<T>* astd::utils::stack_linked_list<T>::pop() {
	auto* top{ head };
	head = head->next;
	return top;
}
#endif