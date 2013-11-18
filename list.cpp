#include <iostream>
#include "list.hpp"



std::ostream &operator<<(std::ostream &os, Node &node) {
  auto next = node.get_next();
  os << '(' << node.get_data());
  if (next) {
    return os << " . " << *next << ')';
  } else {
    return os << ')';
  }
}

// Node* Node::reverse(Node *list) {
// 	Node* ret = NULL;
// 	Node* current = list;

// 	while (current != NULL) {
// 		ret = &Node::cons( current->get_data(), ret);
// 		ret->set_type( current->get_type() );
// 		ret->set_flag( current->get_flag() );
// 		current = current->get_next();
// 	}

// 	return ret;
// }

// void Node::free(Node& list) {}

// void Node::free_all(Node& list) {}

// void Node::free_shallow(Node& list) {}

void List::cons(std::shared_ptr<Node> head, std::shared_ptr<Node> tail) {
  head->next = tail;
}

std::shared_ptr<List> List::cons(std::shared_ptr<Node> head, std::shared_ptr<List>tail){
  head->next = tail->head;
  tail->head = head;
  return tail;
}

std::shared_ptr<Node> List::reverse(std::shared_ptr<Node> ptr){
  std::shared_ptr<Node> temp;
  std::shared_ptr<Node> previous = nullptr;
  while(ptr != nullptr) {
    temp = ptr->next;
    ptr->next = previous;
    previous = ptr;
    ptr = temp;
  }
  return previous;
}

std::shared_ptr<List> List::reverse(std::shared_ptr<List> list) {
  list->head = List::reverse(list->head);  
  return list;
}

int main(int argc, char *argv[], char *env[]) {
  Node n( std::make_shared<variant>(std::string("123")) );
  Node n2( std::make_shared<variant>(std::string("456")), &n);
  std::cout << n2;
  return 0;
}



