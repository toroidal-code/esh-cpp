#include <iostream>
#include "list.hpp"

std::ostream &operator<<(std::ostream &os, const Cell &node) {
  auto cdr = node.get_cdr();
  os << '(' << *(node.get_car());
  if (cdr) {
    return os << " . " << *cdr << ')';
  } else {
    return os << ')';
  }
}

std::ostream &operator<<(std::ostream &os, const List &list) {
  return os << *(list.get_head());
}

void List::cons(std::shared_ptr<Cell> head, std::shared_ptr<variant> tail) {
  head->cdr = std::shared_ptr<variant>(tail);
}

void List::cons(variant data, std::shared_ptr<Cell> tail) {
  std::shared_ptr<Cell> n = std::make_shared<Cell>(data);
  List::cons(n, tail);
}

void List::cons(std::shared_ptr<variant> data, std::shared_ptr<Cell> tail) {
  auto n = std::make_shared<Cell>(data);
  List::cons(n, tail);
}

std::shared_ptr<List> List::cons(std::shared_ptr<Cell> head,
                                 std::shared_ptr<List> tail) {
  head->cdr = std::make_shared<variant>(&tail->head);
  tail->head = head;
  return tail;
}

std::shared_ptr<List> List::cons(variant data, std::shared_ptr<List> tail) {
  auto n = std::make_shared<Cell>(data);
  return List::cons(n, tail);
}

std::shared_ptr<List> List::cons(std::shared_ptr<variant> data,
                                 std::shared_ptr<List> tail) {
  auto n = std::make_shared<Cell>(data);
  return List::cons(n, tail);
}

/**
 *  Reverses a series of Cells
 *
 *  @param ptr The head of the Cell chain
 *
 *  @return The pointer to the new head
 */
std::shared_ptr<Cell> List::reverse(std::shared_ptr<Cell> ptr) {
  static std::shared_ptr<variant> temp = nullptr;
  static std::shared_ptr<Cell> previous = nullptr;
  while (ptr != nullptr) {
    temp = ptr->cdr;
    if (previous != nullptr) {
      ptr->cdr = std::make_shared<variant>(*previous);
    } else {
      ptr->cdr = nullptr;
    }
    previous = ptr;
    ptr = std::shared_ptr<Cell>(boost::get<Cell>(&*(temp)));
  }
  return previous;
}

void List::reverse() { this->head = List::reverse(this->head); }

int main(int argc, char *argv[], char *env[]) {
  auto s = std::make_shared<variant>(std::string("123"));
  auto s2 = std::make_shared<variant>(std::string("456"));
  auto n = std::make_shared<variant>(Cell(s));
  auto n2 = std::make_shared<Cell>(s2, n);
  std::cout << *n2 << std::endl;
  List l(n2);
  std::cout << l << std::endl;
  l.reverse();
  std::cout << l << std::endl;
  return 0;
}

