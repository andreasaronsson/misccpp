#include "mailboxes.h"

using namespace std;

//Constructor
Mailboxes::Mailboxes()
{
  system("ls -1 *.box >boxes");

  string raw, bit, k="^[[0m";
  Mailbox* mailbox;
  //Adds the inbox and the sentbox
  this->inbox = new Mailbox("inbox");
  this->sentbox = new Mailbox("sent_mail");
  ifstream inFile("boxes", ios::in);

  while( getline(inFile, raw) ) {
    
    //cout << raw << endl;
    size_t current = 0;// , prev = 0;
    current = raw.rfind(".box");

    if (current != string::npos) {

	string box = string(raw, 0, current);
	mailbox = new Mailbox(box);
	if (box != "inbox" && box != "sent_mail")
	  this->box_list.push_back(mailbox);
    }

  
  
  }

  inFile.close();

}

//Destructor
Mailboxes::~Mailboxes()
{
  while (this->get_index()>0) {
    this->box_list.at(this->get_index()-1)->boxsave();
    delete this->box_list.back();
    this->box_list.pop_back();
  }
  this->inbox->boxsave();
  delete this->inbox;
  this->sentbox->boxsave();
  delete this->sentbox;
}


//Add mailbox to the list. Returns false if the box name is being used already.
bool Mailboxes::import(Mailbox* mailbox)
{
 
  vector<Mailbox*>::iterator it = this->box_list.begin();
  //inbox and sent_mail are reserved
  if (mailbox->get_name() == "inbox" || mailbox->get_name() == "sent_mail")
    return false;

  //If empty list
  if (get_index() == 0) {
    this->box_list.push_back(mailbox);
    return true;
  }

  while ((*it)->get_name() != mailbox->get_name() && *it != this->box_list.back())
    it++;
  if ((*it)->get_name() != mailbox->get_name() && mailbox->get_name() != "inbox" && mailbox->get_name() != "sent-mail") {  
    this->box_list.push_back(mailbox);
   return true;
  }
  else
    return false;
}

//Return a vector with mail objects
vector <Mailbox*> Mailboxes::get_list()
{
  return this->box_list;
}

//Removes a mailbox and it's file
void Mailboxes::remove(Mailbox* mailbox)
{
  string filename;
  vector<Mailbox*>::iterator it = this->box_list.begin();
  while (*it != mailbox)
    it++;
  if (*it == mailbox) {  
    filename = "rm -f " + mailbox->get_name() + ".box";
    this->box_list.erase(it);
    system (filename.c_str());
  }
}


int Mailboxes::get_index()
{
  return this->box_list.size();
}

Mailbox* Mailboxes::get_inbox()
{
  return this->inbox;
}

Mailbox* Mailboxes::get_sentbox()
{
  return this->sentbox;
}

list <string> Mailboxes::get_name_list()
{
  int i;
  list <string> name_list;
  for (i=0; i<this->get_index();i++) {
    name_list.push_back(this->box_list.at(i)->get_name());
  }  
  return name_list;

}
