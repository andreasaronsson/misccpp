#include "mail.h"
#include "mailbox.h"
#include "mailboxes.h"
#include <iostream>
using namespace std;

int main() {
  int i;
  Mail *mail;
  Mail *mail2;  
  Mailbox *inbox;
  //Mailbox *mailbox2;
  Mailboxes *mailboxes;
  string test1;
  string test2;
  string test3;
  test1="Subject";
  test2="test";
  test3="vinst!";
  mail = new Mail();
  mail2 = new Mail();
  //mailbox = new Mailbox("inbox");
  //mailbox2 = new Mailbox("test");
  mail->setvalue(test1, test3);
  mail2->setvalue(test1, test2);
  mailboxes = new Mailboxes();
  inbox = mailboxes->get_inbox();
  inbox->import(mail);
  inbox->import(mail2);
  //mailbox->import(mail);
  //mailbox->import(mail2);
  
  for (i=0; i<inbox->get_index(); i++)
    cout << inbox->mail_list.at(i)->get_subject() << endl;
 
  inbox->mailsort("Subject");
  inbox->boxsave();
  //Flytta alla mail från en box till en annan
  /*
  while(mailbox->get_index() > 0)
    mailbox->move(mailbox->mail_list.at(0), mailbox2);
  */ 
  //mailbox->boxsave();
  //mailbox2->boxsave();
  /*
  cout << mailbox->get_index() << endl;
  cout << mailbox2->get_index() << endl;
  mailbox->move(mail, mailbox2);
  cout << mailbox->get_index() << endl;
  cout << mailbox2->get_index() << endl;
  cout << mailbox->mail_list.at(0)->get_subject() << endl;
  */
}
