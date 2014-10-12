#ifndef _POP
#define _POP
#include <cc++/socket.h>
#include <string>
#include <sstream>
#include "mailbox.h"
#include <vector>
#include "mail.h"

using namespace std;
using namespace ost;
class Pop {
  public:
    Pop();
    Pop(string h, string u, string p);
    void setvalue(string key, string val);
    string get_host();
    string get_user();
    string get_pass();
    int pop(Mailbox &inbox);
  private:
    void unmime(string &mimed);
    string host;
    string user;
    string pass;
};
#endif
