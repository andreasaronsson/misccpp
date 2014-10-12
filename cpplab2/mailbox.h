#ifndef _MAILBOX
#define _MAILBOX
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "mail.h"
using namespace std;

class Mailbox{
 public:
  Mailbox();
  Mailbox(string);
  void import(Mail*);
  vector <Mail*> get_list();  
  vector <Mail*> mail_list;
  void remove(Mail*);
  void move(Mail*, Mailbox*);
  void mailsort(string);  
  void boxsave();
  int get_index();
  string get_name();
private:
  string box;
  int find_index(Mail*);
};
#endif
