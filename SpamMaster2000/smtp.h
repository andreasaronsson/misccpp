#ifndef _SMTP
#define _SMTP
#include <cc++/socket.h>
#include <string>
#include <time.h>
#include "mail.h"
#include "mailbox.h"

using namespace std;
using namespace ost;
class Smtp {
  public:
    Smtp();
    Smtp(string hostname, string name, string addr);
    void setvalue(string key, string val);
    string get_host();
    string get_name();
    string get_addr();
    string send(Mail* message, Mailbox &sentbox);
  private:
    string host;
    string name;
    string addr;
};
#endif
