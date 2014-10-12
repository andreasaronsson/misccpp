#include "mail.h"
#include "smtp.h"
#include "pop.h"
#include "mailbox.h"
#include <vector>

int main() {
  Mail *message;
  message = new Mail();
  string host = "spiff.informatik.gu.se";
  Smtp server(host);
  string bapp;
  string key;
  Mailbox inbox;
  vector <Mail*> boxvector;
  
  key = "From";
  bapp = "SpamMaster 2k4 <bow@skip.informatik.gu.se>";
  message->setvalue(key,bapp);
  
  key = "Date";
  char datum[256];
  struct tm *tm;
  time_t time_date;
  time_date = time(NULL);
  tm = localtime(&time_date);
  strftime(datum, 255, "%a, %d %b %Y %H:%M:%S %z", tm);
  bapp = datum;
  message->setvalue(key,bapp);
  
  key = "Subject";
  bapp = "Testmail som fan";
  message->setvalue(key,bapp);
  
  key = "To";
  bapp = "SpamMaster Jaff <jaff@bow.mine.nu>";
  message->setvalue(key,bapp);
  
  key = "Body";
  bapp = "Detta är ett meddelande av klassen Mail.\nDet skickas av ett objekt av klassen Smtp.\nNästa rad är en punkt\n.";
  message->setvalue(key,bapp);

  //cout << server.send(message, inbox) << endl;
  Pop popserver("pop.algonet.se", "midas", "etd294");
  cout << popserver.pop(inbox) << " nya mail för ";
  cout << popserver.get_user() << "@" << popserver.get_host() << endl;

  boxvector = inbox.get_list();
  if ( !boxvector.empty() ) {
    Mail *new_mail;
    /*
    new_mail = boxvector.front();
  
    cout << "Till:  " << new_mail->get_to() << endl;
    cout << "Från:  " << new_mail->get_from() << endl;
    cout << "Datum: " << new_mail->get_date() << endl;
    cout << "Ämne:  " << new_mail->get_subject() << endl;
    cout << "Övriga headers:\n" << new_mail->get_headers() << endl;
    cout << "BODY:\n" << new_mail->get_body() << endl;
    */
    new_mail = boxvector.back();

    cout << "Till:  " << new_mail->get_to() << endl;
    cout << "Från:  " << new_mail->get_from() << endl;
    cout << "Datum: " << new_mail->get_date() << endl;
    cout << "Ämne:  " << new_mail->get_subject() << endl;
    cout << "Övriga headers:\n" << new_mail->get_headers() << endl;
    cout << "BODY:\n" << new_mail->get_body() << endl;
  }  
}
