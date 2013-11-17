/*
 * esh, the Unix shell with Lisp-like syntax.
 * Copyright (C) 1999  Ivan Tkatchev
 * This source code is under the GPL.
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

typedef boost::variant<std::string, bool> variant;

typedef struct Node {
  std::shared_ptr<variant> data;
  Node *next;
  char type;
  char flag;

  // Various constructors
  // Node(shared_ptr<void> data, char type, char flag)
  //     : data(data), next(NULL), type(type), flag(flag) {};
  // Node(void *data, char type)
  //     : data(data), next(NULL), type(type), flag(FLAG_NONE) {};
  Node(std::shared_ptr<variant> data, Node *tail)
      : data(data), next(tail), type(TYPE_STRING), flag(FLAG_NONE) {};
  Node(std::shared_ptr<variant> data)
      : data(data), next(NULL), type(TYPE_STRING), flag(FLAG_NONE) {};
  // Node(const Node &other);

  ~Node();



  // Getters and setters
  inline Node *get_next() {
    return this->next;
  };
  inline std::shared_ptr<variant> get_data() {
    return this->data;
  };
  inline void set_type(char type) {
    this->type = type;
  };
  inline char get_type() {
    return this->type;
  };
  inline void set_flag(char flag) {
    this->flag = flag;
  };
  inline char get_flag() {
    return this->flag;
  };
} Node;

class List {
  Node* head;
  public: 
    static Node *reverse(Node *list);

protected:
};


std::ostream &operator << (std::ostream &os, Node &node);


#endif // LIST_HPP
