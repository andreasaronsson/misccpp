#ifndef _MAILBOXES
#define _MAILBOXES
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "mail.h"
#include "mailbox.h"
using namespace std;

class Mailboxes{
 public:
  Mailboxes();
  ~Mailboxes();
  bool import(Mailbox*);
  vector <Mailbox*> get_list();  
  vector <Mailbox*> box_list;
  void remove(Mailbox*);
  int get_index();
  Mailbox* get_inbox();
  Mailbox* get_sentbox();
  list <string> get_name_list();
private:
  Mailbox* inbox;
  Mailbox* sentbox;
};
#endif
