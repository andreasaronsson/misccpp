#include "abook.h"
#include "contact.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;


/* Gets contact inforamtion from an file using xml like syntax *                
 * if the supplied filename doesen't exist this function       *  
 * will return false.                                          */

bool load_abook(vector<Contact*>& abook, string file){
  
  int con = 0,name = 0 ;
  string  fstr, tmp, ab ="<addressbook>", c="<contact>", n="<name>", e="<email>"; 
  string  f ="<first>", eab="</addressbook>", ec="</contact>", en="</name>";

  ifstream fin(file.c_str(), ios::in);
  
  Contact *contact;
  
  if(!fin){
    return false; 
  }
  else { 
    while( getline(fin, fstr) ){
      if(fstr.find(eab) != string::npos){
	break;
      }
      if(fstr.find(c) != string::npos){
	con++;
	getline(fin, fstr);
      }
      contact = new Contact;
      while(con == 1){
	if(fstr.find(n) != string::npos){
	  name++;
	}
	while(name == 1){
	  size_t start = 0, stop = 0;
	  if(fstr.find(f) != string::npos){
	    start = fstr.find(f,stop)+f.length();
	    stop = fstr.find('<',start);
	    contact->set_firstname(string(fstr,start,stop-start));
	  }
	  else { 
	    start = fstr.find('>',stop);
	    stop = fstr.find('<',start);
	    contact->set_lastname(string(fstr, start+1, stop-start-1));
	  }
	  getline(fin,fstr);
	  
	  if(fstr.find(en) != string::npos){
	    name--;
	  }
	}
	if(fstr.find(e) != string::npos){
	  size_t start = 0, stop = 0;
	  start = fstr.find('>',stop);
	  stop = fstr.find('<',start);
	  contact->set_email(string(fstr, start+1, stop-start-1));
	}
	getline(fin,fstr);
	if(fstr.find(ec) != string::npos){
	  abook.push_back(contact);
	  con--;
	}
      } 
    }
    fin.close();
    return true;
  }
}

/* saves contact inforamtion into an file using xml like syntax 
 * if file exists it will be overwritten, if it doesn't exist it
 * will created. 
 */
bool save_abook(vector<Contact*>& contact, string file) {

  ofstream fout(file.c_str(), ios::out); 
  vector<Contact*>::iterator it;
  it = contact.begin();

  fout << "<addressbook>" << endl; 
  while(it != contact.end()){
    fout << "    <contact>" << endl 
	 << "        <name>"<< endl
	 << "            <first>" << (*it)->get_firstname() << "</first>" << endl
	 << "            <last>" << (*it)->get_lastname() << "</last>" << endl
	 << "        </name>" << endl
	 << "        <email>" << (*it)->get_email() << "</email>" << endl
 	 << "    </contact>" << endl;
    it++;
  }
  fout << "</addressbook>" << endl;
  fout.close();
  
  return true;
}

/* Adds acontact to the supplied contact vector.
 */
void add_contact(vector<Contact*>& abook, string firstname, 
		 string lastname, string email ) {
  
  Contact *con = new Contact(firstname,lastname,email);
  abook.push_back(con);
}

/* removes a contact from the vector and destructs the contact object.
 */
void delete_contact(vector<Contact*>& abook, size_t pos){
  vector<Contact*>::iterator it;
  it = abook.begin() + pos;
  Contact *con = abook.at(pos);
  abook.erase(it);
  delete con;
}

bool CmpFirst::operator() (Contact *con1, Contact *con2) const {
  return con1->get_firstname()+con1->get_lastname() < 
    con2->get_firstname()+con2->get_lastname();
}

bool CmpLast::operator() (Contact *con1, Contact *con2) const {
  return con1->get_lastname()+con1->get_firstname() < 
    con2->get_lastname()+con2->get_firstname();
}

/* sorts  the addressbooks vector on firstname first
 */
void sort_first(vector<Contact*>& abook ){
  CmpFirst cmpfirst;
  sort(abook.begin(),abook.end(),cmpfirst);
  
}

/* sorts the addressbooks vector on lastname first
 */
void sort_last(vector<Contact*>& abook ){
  CmpLast cmplast;
  sort(abook.begin(),abook.end(),cmplast);
}
  
