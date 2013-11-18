/*
 * esh, the Unix shell with Lisp-like syntax.
 * Copyright (C) 2013 Katherine Whitlock
 * This source code is under the BSD (3 clause) license.
 */

/*
 * A very simple linked-list implementation.
 *
 * Pitfalls:
 *
 *  + You cannot delete elements from the list.
 *  + The list functions are lisp-like, i.e. "ls_cons" returns a list.
 *  + Please don't use the internals of the "list" structure.
 *  + You can accidentaly reverse the arguments to "ls_cons"
 *    and not get a warning from the compiler!
 *  + The list does not do any memory management. Nothing is copied before
 *    insertion, and "ls_free" does not free the data in the list.
 *    "ls_free_all" is provided as a convinience -- it will free
 *    the data before deleting the list node.
 *  + "ls_copy" and "ls_free_all" make lots of assumptions about type
 *     information.
 */

#ifndef LIST_HPP
#define LIST_HPP
#include <string>
#include <memory>
#include <boost/variant.hpp>

#define TYPE_STRING 0
#define TYPE_LIST 1
#define TYPE_HASH 2
#define TYPE_BOOL 3
#define TYPE_FD 4
#define TYPE_PROC 5
#define TYPE_VOID 6

#define FLAG_NONE 0

class List;

typedef boost::variant<std::string, char *, bool> variant;

class Node {
  friend class List;
  std::shared_ptr<variant> data;
  std::shared_ptr<Node> next;
  char type;
  char flag;

 public:
  // Various constructors
  // Node(shared_ptr<void> data, char type, char flag)
  //     : data(data), next(NULL), type(type), flag(flag) {};
  // Node(void *data, char type)
  //     : data(data), next(NULL), type(type), flag(FLAG_NONE) {};
  Node(variant* data, Node *tail)
      : data(std::shared_ptr<variant>(data)), next(std::shared_ptr<Node>(tail)), type(TYPE_STRING), flag(FLAG_NONE) {}
  Node(variant * data)
      : data(std::shared_ptr<variant>(data)), next(nullptr), type(TYPE_STRING), flag(FLAG_NONE) {}
  Node(variant* data, std::shared_ptr<Node> tail)
      : data(std::shared_ptr<variant>(data)), next(tail), type(TYPE_STRING), flag(FLAG_NONE) {}
  Node(std::shared_ptr<variant> data, Node *tail)
      : data(data), next(std::shared_ptr<Node>(tail)), type(TYPE_STRING), flag(FLAG_NONE) {}
  Node(std::shared_ptr<variant> data)
      : data(data), next(nullptr), type(TYPE_STRING), flag(FLAG_NONE) {}
  Node(std::shared_ptr<variant> data, std::shared_ptr<Node> tail)
      : data(data), next(tail), type(TYPE_STRING), flag(FLAG_NONE) {}

  // Node(const Node &other);

  // Getters and setters
  inline std::shared_ptr<Node> get_next() { return this->next; }
  inline std::shared_ptr<variant> get_data() { return this->data; }
  inline void set_type(char type) { this->type = type; }
  inline char get_type() { return this->type; }
  inline void set_flag(char flag) { this->flag = flag; }
  inline char get_flag() { return this->flag; }
};

class List {
  std::shared_ptr<Node> head;
 public:
  // Static functions
  static void cons(std::shared_ptr<Node> head, std::shared_ptr<Node> tail);
  static std::shared_ptr<List> cons(std::shared_ptr<Node> head, std::shared_ptr<List> tail);
  static std::shared_ptr<Node> reverse(std::shared_ptr<Node> head);
  static std::shared_ptr<List> reverse(std::shared_ptr<List> list);

  // Constructors
  List(std::shared_ptr<Node> head)
      : head(head) {};
  List(Node *head)
      : head(std::shared_ptr<Node>(head)) {};
};

std::ostream &operator<<(std::ostream &os, Node &node);

#endif  // LIST_HPP
