#include "contact.h"
#include <iostream>

// constructors
Contact::Contact(){ }
Contact::Contact(string fn, string e){
  firstname = fn;
  email  = e;
};

Contact::Contact(string fn, string ln, string e){
  firstname = fn;
  lastname = ln;
  email  = e;
};

//member functions
string Contact::get_firstname(){
  return firstname;
};
string Contact::get_lastname(){
  return lastname;
}
string Contact::get_email(){
  return email;
};
void Contact::set_firstname(string new_name){
  firstname = new_name;
};
void Contact::set_lastname(string new_name){
  lastname = new_name;
};
void Contact::set_email(string new_email){
  email = new_email;
};
