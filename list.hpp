/*
 * esh, the Unix shell with Lisp-like syntax.
 * Copyright (C) 2013 Katherine Whitlock
 * This source code is under the BSD (3 clause) license.
 */

/*
 * A simple linked-list implementation.
 *
 * Pitfalls:
 *
 *  + You cannot delete elements from the list.
 *  + Please don't use the internals of the "list" structure.
 */

#ifndef LIST_HPP
#define LIST_HPP
#include <string>
#include <memory>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/any.hpp>

#define TYPE_STRING 0
#define TYPE_LIST 1
#define TYPE_HASH 2
#define TYPE_BOOL 3
#define TYPE_FD 4
#define TYPE_PROC 5
#define TYPE_VOID 6

#define FLAG_NONE 0

class Cell;
typedef boost::variant<std::string, bool, int, boost::recursive_wrapper<Cell> >
    variant;

class Cell {
  friend class List;
  std::shared_ptr<variant> car;
  std::shared_ptr<variant> cdr;
  char type;
  char flag;

 public:
  // Various constructors
  // Cell(shared_ptr<void> car, char type, char flag)
  //     : car(car), cdr(NULL), type(type), flag(flag) {};
  // Cell(void *car, char type)
  //     : car(car), cdr(NULL), type(type), flag(FLAG_NONE) {};
  Cell(variant car)
      : car(std::make_shared<variant>(car)),
        cdr(nullptr),
        type(TYPE_STRING),
        flag(FLAG_NONE) {}
  Cell(variant car, variant cdr)
      : car(std::make_shared<variant>(car)),
        cdr(std::make_shared<variant>(cdr)),
        type(TYPE_STRING),
        flag(FLAG_NONE) {}
  Cell(std::shared_ptr<variant> car)
      : car(car), cdr(nullptr), type(TYPE_STRING), flag(FLAG_NONE) {}
  Cell(std::shared_ptr<variant> car, std::shared_ptr<variant> cdr)
      : car(car), cdr(cdr), type(TYPE_STRING), flag(FLAG_NONE) {}

  // Cell(const Cell &other);

  // Getters and setters
  inline std::shared_ptr<variant> get_car() const { return this->car; }
  inline std::shared_ptr<variant> get_cdr() const { return this->cdr; }
  inline void set_type(const char type) { this->type = type; }
  inline char get_type() const { return this->type; }
  inline void set_flag(const char flag) { this->flag = flag; }
  inline char get_flag() const { return this->flag; }
};

class List {
  std::shared_ptr<Cell> head;
//  std::shared_ptr<Cell> last;
  static std::shared_ptr<variant> reverse(std::shared_ptr<variant> head);
  static std::shared_ptr<variant> get_last(std::shared_ptr<variant> ptr);

 public:
  //  // Cons functions
  //  static void cons(std::shared_ptr<Cell> head, std::shared_ptr<variant>
  // tail);
  //  static void cons(variant data, std::shared_ptr<Cell> tail);
  //  static void cons(std::shared_ptr<variant> data, std::shared_ptr<Cell>
  // tail);
  //  static std::shared_ptr<List> cons(std::shared_ptr<Cell> head,
  //                                    std::shared_ptr<List> tail);
  //  static std::shared_ptr<List> cons(variant data, std::shared_ptr<List>
  // tail);
  //  static std::shared_ptr<List> cons(std::shared_ptr<variant> data,
  //                                    std::shared_ptr<List> tail);
  void reverse();
  inline std::shared_ptr<Cell> get_head() const { return this->head; }
 // inline std::shared_ptr<Cell> get_last() const { return this->last; }

  // Constructors
  List(std::shared_ptr<Cell> head) : head(head) { };
  List(Cell *head) : head(std::shared_ptr<Cell>(head)) {};
};

std::ostream &operator<<(std::ostream &os, const Cell &node);
// std::ostream &operator<<(std::ostream &os, const List &list);
#endif  // LIST_HPP
