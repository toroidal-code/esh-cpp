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

#define TYPE_STRING 0
#define TYPE_LIST 1
#define TYPE_HASH 2
#define TYPE_BOOL 3
#define TYPE_FD 4
#define TYPE_PROC 5
#define TYPE_VOID 6

#define FLAG_NONE 0

class List;

typedef boost::variant<std::string, List, char *, bool> variant;

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
  Node(variant *data, Node *tail)
      : data(std::shared_ptr<variant>(data)),
        next(std::shared_ptr<Node>(tail)),
        type(TYPE_STRING),
        flag(FLAG_NONE) {}
  Node(variant *data)
      : data(std::shared_ptr<variant>(data)),
        next(nullptr),
        type(TYPE_STRING),
        flag(FLAG_NONE) {}
  Node(variant *data, std::shared_ptr<Node> tail)
      : data(std::shared_ptr<variant>(data)),
        next(tail),
        type(TYPE_STRING),
        flag(FLAG_NONE) {}
  Node(std::shared_ptr<variant> data, Node *tail)
      : data(data),
        next(std::shared_ptr<Node>(tail)),
        type(TYPE_STRING),
        flag(FLAG_NONE) {}
  Node(std::shared_ptr<variant> data)
      : data(data), next(nullptr), type(TYPE_STRING), flag(FLAG_NONE) {}
  Node(std::shared_ptr<variant> data, std::shared_ptr<Node> tail)
      : data(data), next(tail), type(TYPE_STRING), flag(FLAG_NONE) {}

  // Node(const Node &other);

  // Getters and setters
  inline std::shared_ptr<Node> get_next() const { return this->next; }
  inline std::shared_ptr<variant> get_data() const { return this->data; }
  inline void set_type(const char type) { this->type = type; }
  inline char get_type() const { return this->type; }
  inline void set_flag(const char flag) { this->flag = flag; }
  inline char get_flag() const { return this->flag; }
};

class List {
  std::shared_ptr<Node> head;
  static std::shared_ptr<Node> reverse(std::shared_ptr<Node> head);

 public:
  // Static functions
  static void cons(std::shared_ptr<Node> head, std::shared_ptr<Node> tail);
  static std::shared_ptr<List> cons(std::shared_ptr<Node> head,
                                    std::shared_ptr<List> tail);
  void reverse();

  inline std::shared_ptr<Node> get_head() { return this->head; }
  inline std::shared_ptr<Node> get_head() const { return this->head; }

  // Constructors
  List(std::shared_ptr<Node> head) : head(head) {};
  List(Node *head) : head(std::shared_ptr<Node>(head)) {};
};

std::ostream &operator<<(std::ostream &os, const Node &node);
std::ostream &operator<<(std::ostream &os, const List &list);
#endif  // LIST_HPP
