#include <iostream>
#include "list.hpp"

std::ostream &operator<<(std::ostream &os, const Cell &node) {
  auto cdr = node.get_cdr();
  
  if (cdr == nullptr) {
    return os << *(node.get_car()) << ')';
  } else if (cdr->type() == typeid(Cell)) {
    return os << *(node.get_car()) << " " << *cdr;
  } else if (cdr->type() != typeid(Cell)) {
    return os << *(node.get_car()) << " . " << *cdr;
  } else {
    return os << "";
  }
}

std::ostream &operator<<(std::ostream &os, const List &list) {
  return os << '(' << *(list.get_head()) << ')';
}
//
// void List::cons(std::shared_ptr<Cell> head, std::shared_ptr<variant> tail) {
//  head->cdr = std::shared_ptr<variant>(tail);
//}

// void List::cons(variant data, std::shared_ptr<Cell> tail) {
//  std::shared_ptr<Cell> n = std::make_shared<Cell>(data);
//  List::cons(n, tail);
//}

// void List::cons(std::shared_ptr<variant> data, std::shared_ptr<Cell> tail) {
//  auto n = std::make_shared<Cell>(data);
//  List::cons(n, tail);
//}
//
// std::shared_ptr<List> List::cons(std::shared_ptr<Cell> head,
//                                 std::shared_ptr<List> tail) {
//  head->cdr = std::make_shared<variant>(&tail->head);
//  tail->head = head;
//  return tail;
//}
//
// std::shared_ptr<List> List::cons(variant data, std::shared_ptr<List> tail) {
//  auto n = std::make_shared<Cell>(data);
//  return List::cons(n, tail);
//}
//
// std::shared_ptr<List> List::cons(std::shared_ptr<variant> data,
//                                 std::shared_ptr<List> tail) {
//  auto n = std::make_shared<Cell>(data);
//  return List::cons(n, tail);
//}

/**
 *  Reverses a series of Cells
 *
 *  @param ptr The head of the Cell chain
 *
 *  @return The pointer to the new head
 */
std::shared_ptr<variant> List::reverse(std::shared_ptr<variant> ptr) {
  std::shared_ptr<variant> temp = nullptr;
  std::shared_ptr<variant> previous = nullptr;
  while (ptr != nullptr && ptr->type() == typeid(Cell)) {
    auto cell = boost::get<Cell>(&*(ptr));
    temp = cell->cdr;
    cell->cdr = previous;
    previous = ptr;
    ptr = temp;
  }
  return previous;
}

std::shared_ptr<variant> List::get_last(std::shared_ptr<variant> ptr) {
  std::shared_ptr<variant> temp = nullptr;
  std::shared_ptr<variant> previous = nullptr;
  while (ptr != nullptr && ptr->type() == typeid(Cell)) {
    auto cell = boost::get<Cell>(&*(ptr));
    temp = cell->cdr;
    previous = ptr;
    ptr = temp;
  }
  return previous;
}

void List::reverse() {
//  if (this->last.get() != nullptr) {
//    std::cout << "Error: REVERSE: A proper list must not end with"
//              << this->last.get() << std::endl;
//  }
  auto var_head = std::make_shared<variant>(*(this->head));
  auto new_head = List::reverse(var_head);
  auto new_last = List::get_last(new_head);
  this->head = std::shared_ptr<Cell>(&boost::get<Cell>(*new_head));
//  this->last = std::shared_ptr<Cell>(&boost::get<Cell>(*new_last));
}

int main(int argc, char *argv[], char *env[]) {
  auto s = std::make_shared<variant>(std::string("123"));
  auto s2 = std::make_shared<variant>(std::string("456"));
  auto n = std::make_shared<variant>(Cell(s, s2));
  auto n2 = std::make_shared<Cell>(s2, n);
  std::cout << *n2 << std::endl;
  //  std::cout << *n2 << std::endl;
  List l(n2);
  std::cout << l << std::endl;
  //  l.reverse();
  std::cout << *n << std::endl;
  return 0;
}
