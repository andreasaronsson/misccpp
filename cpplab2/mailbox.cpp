#include "mailbox.h"
#include "compare.h"

using namespace std;

//Constructor
Mailbox::Mailbox()
{
}

Mailbox::Mailbox(string box)
{
  this->box = box;
  setlocale(LC_ALL,"sv_SE");
  Mail* mail;
  vector<string> v;  
  string filename, raw, bit, d="<dict>", k="<key>", dq="</dict>", kq="</key>";
 
  filename = this->box + ".box";
  ifstream inFile(filename.c_str(), ios::in);

  mail = new Mail;
  while( getline(inFile, raw) ) {
    
    //cout << raw << endl;
    if ( string::npos != raw.find(k) ) {
      size_t current = 0 , next = 0;
      while ( current != string::npos ) {
	next = raw.find( '>', current );
	current = raw.find( '<', next );
	if ( 0 != current-next-1  && current != string::npos ) 
	  v.push_back( string( raw , next+1 , current-next-1 ) );
	current = (next == string::npos) ? string::npos : next + 1 ;
      }
      //      cout << v.front() << " " << v.back() << endl;
      mail->setvalue(v.front(), v.back());
      v.clear();
    }

    if ( string::npos != raw.find(dq) ) {
      getline(inFile, raw);
      this->import(mail);
      mail = new Mail();
    }
  

  }

  inFile.close();


}


//Add mail to mailbox
void Mailbox::import(Mail* mail)
{
  this->mail_list.push_back(mail);
}

//Return a vector with mail objects
vector <Mail*> Mailbox::get_list()
{
  return this->mail_list;
}

//Removes a specific mail
void Mailbox::remove(Mail* mail)
{
  vector<Mail*>::iterator it = this->mail_list.begin();
  while (*it != mail)
    it++;
  this->mail_list.erase(it);
}

//Export a mail from this mailbox to another
void Mailbox::move(Mail* mail, Mailbox* mailbox)
{
  mailbox->import(mail);
  remove(mail);
}

//Sorts the mailbox
void Mailbox::mailsort(string sortorder)
{
  CmpSubject subjectcmp;
  CmpDate datecmp;
  CmpFrom fromcmp;
  if (sortorder == "Subject")
    sort(this->mail_list.begin(), this->mail_list.end(), subjectcmp);
  else if(sortorder == "From")
    sort(this->mail_list.begin(), this->mail_list.end(), fromcmp);
  else if (sortorder == "Date")
    sort(this->mail_list.begin(), this->mail_list.end(), datecmp);
}

void Mailbox::boxsave()
{
  int i, nmail;
  setlocale(LC_ALL,"sv_SE");
  string filename, wbuffer;
 
  filename = this->box + ".box";
  ofstream outFile(filename.c_str(), ios::trunc);
  wbuffer = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
  outFile.write(wbuffer.c_str(), wbuffer.size());
  nmail = this->get_index();
  for (i = 0; i<nmail; i++) {
    wbuffer = "<dict>\n";
    wbuffer += "<key>Subject</key><string>" + this->mail_list.at(i)->get_subject() + "</string>\n";
    wbuffer += "<key>From</key><string>" + this->mail_list.at(i)->get_from() + "</string>\n";
    wbuffer += "<key>To</key><string>"+ this->mail_list.at(i)->get_to() + "</string>\n";
    wbuffer += "<key>Body</key><string>"+ this->mail_list.at(i)->get_body() + "</string>\n";
    wbuffer += "</dict>\n";
    outFile.write(wbuffer.c_str(), wbuffer.size());
  }

  outFile.close();

}


int Mailbox::get_index()
{
  return this->mail_list.size();
}

string Mailbox::get_name()
{
  return this->box;
}
