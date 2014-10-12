#ifndef ABOOK_H
#define ABOOK_H

#include "contact.h"
#include <string>
#include <vector>
#include <iostream>

void add_contact(vector<Contact*>& abook, string firstname,
		 string lastname, string email);
bool load_abook(vector<Contact*>& abook, string file);
bool save_abook(vector<Contact*>& abook, string file);
void delete_contact(vector<Contact*>& abook, int pos);
void sort_first(vector<Contact*>& abook);
void sort_last(vector<Contact*>& abook);
void rsort(vector<Contact*>& abook );
class CmpFirst {
 public:
  bool operator() (Contact*, Contact*) const;

};
class CmpLast {
 public:
  bool operator() (Contact*, Contact*) const;
};

#endif

