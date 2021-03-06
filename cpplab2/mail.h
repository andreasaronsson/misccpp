#ifndef _MAIL
#define _MAIL
#include <iostream>
#include <string>
#include <stdlib.h>
#include <utility>

using namespace std;
class Mail {
 public:
  Mail();
  void setvalue(string &key, string &val);
  string get_from();
  string get_date();
  string get_subject();
  string get_to();
  string get_body();
  string get_headers();
 private:
  string from;
  string date;
  string subject;
  string to;
  string body;
  string headers;
};
#endif
