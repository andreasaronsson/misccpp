#ifndef CONTACT_H
#define CONTACT_H
#include <string>
using namespace std;
class Contact{
 public:
  //constructors
  Contact();
  Contact(string, string);
  Contact(string, string, string);
  
  //member functions
  void set_firstname(string);
  void set_lastname(string);
  void set_email(string);
  string get_name();
  string get_firstname();
  string get_lastname();
  string get_email();

 private:
  // member variables
  string firstname;
  string lastname;
  string email;
};

#endif
