#include <iostream>
#include "list.hpp"

std::ostream &operator<<(std::ostream &os, Node &node) {
  auto next = node.get_next();
  os << '(' << *(node.get_data());
  if (next) {
    return os << " . " << *next << ')';
  } else {
    return os << ')';
  }
}

std::ostream &operator<<(std::ostream &os, List &list) {
  return os << *(list.get_head());
}

void List::cons(std::shared_ptr<Node> head, std::shared_ptr<Node> tail) {
  head->next = tail;
}

std::shared_ptr<List> List::cons(std::shared_ptr<Node> head,
                                 std::shared_ptr<List> tail) {
  head->next = tail->head;
  tail->head = head;
  return tail;
}

/**
 *  Reverses a series of Nodes
 *
 *  @param ptr The head of the Node chain
 *
 *  @return The pointer to the new head
 */
std::shared_ptr<Node> List::reverse(std::shared_ptr<Node> ptr) {
  std::shared_ptr<Node> temp = nullptr;
  std::shared_ptr<Node> previous = nullptr;
  while (ptr != nullptr) {
    temp = ptr->next;
    ptr->next = previous;
    previous = ptr;
    ptr = temp;
  }
  return previous;
}

int main(int argc, char *argv[], char *env[]) {
  auto s = std::make_shared<variant>(std::string("123"));
  auto s2 = std::make_shared<variant>(std::string("456"));
  auto n = std::make_shared<Node>(s);
  auto n2 = std::make_shared<Node>(s2, n);
  std::cout << *n2 << std::endl;
  List l(n2);
  std::cout << l << std::endl;
  l.reverse();
  std::cout << l << std::endl;
  return 0;
}
