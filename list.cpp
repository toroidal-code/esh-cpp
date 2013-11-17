#include "list.hpp"
#include <iostream>

Node::~Node() {}

std::ostream &operator<<(std::ostream &os, Node &node) {
  auto next = node.get_next();
  os << '(' << *(node.get_data());
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

int main(int argc, char *argv[], char *env[]) {
  Node n((std::shared_ptr<variant>(new variant(std::string("123")))));
  Node n2((std::shared_ptr<variant>(new variant(std::string("456")))), &n);
  std::cout << n2;
  return 0;
}
