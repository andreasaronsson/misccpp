#ifndef _PREFS
#define _PREFS
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <utility>

using namespace std;
class Prefs {
 public:
  Prefs();
  string get_name();
  string get_address();
  string get_pop();
  string get_popUser();
  string get_popPass();
  string get_smtp();
  string get_smtpUser();
  string get_smtpPass();
  string get_signature();
private:
  string name;
  string address;
  string pop;
  string popUser;
  string popPass;
  string smtp;
  string smtpUser;
  string smtpPass;
  string signature;
};
#endif
