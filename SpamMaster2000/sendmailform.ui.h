/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
vector <Contact*> *mainAddressBook;

using namespace std;

void sendMailForm::newMailSlot()
{
  sendMail();
  close();
}


void sendMailForm::sendMail()
{
  
  Mail *message;
  message = new Mail();
  string bapp, key;
  
  stringstream ss;	
  key = "To";
  ss << toMailLineEdit->text();
  std::getline(ss, bapp);
  message->setvalue(key,bapp);
  //std::cerr << "To:(bapp)  " << bapp << endl;
  //std::cerr << "To:(bapp)  " << toMailLineEdit->text() << endl;
  ss.clear();
  
  key = "Subject";
  ss <<  subjectMailLineEdit->text();
  std::getline(ss, bapp);
  message->setvalue(key,bapp);
  //std::cerr << "Subject: " << bapp << endl;
  ss.clear();
  
  key = "Body";
  bapp = "";
  char temp[1000];
  ss << mailTextEdit->text();
  while ( ss ) {
    ss.getline(temp,1000);
    bapp = bapp + temp + "\n";
  }
  bapp.erase( bapp.end() - 1 );
  message->setvalue(key,bapp);
  
  //cout << server->send(message, *boxen) << endl;
}

void sendMailForm::init()
{
  newAdressBook = 0;

}

void sendMailForm::newMailSlot( Mailbox & sentmail, Smtp & smtpserver, vector <Contact*> & abook, QString signature )
{
  boxen = &sentmail;
  server = &smtpserver;
  mainAddressBook = &abook;
  mailTextEdit->setText(signature);
}


void sendMailForm::replyMailSlot( Mail & oldmail, Mailbox & sentmail, Smtp & smtpserver , vector <Contact*> & abook)
{
    string rplyhead = "---------- In reply to ----------\n";
    rplyhead = rplyhead + "Date: " + oldmail.get_date() + "\n";
  rplyhead = rplyhead + "From: " +  oldmail.get_from() + "\n";
  rplyhead = rplyhead + "To: " + oldmail.get_to() + "\n\n";
  mailTextEdit->setText( rplyhead + oldmail.get_body() );
  subjectMailLineEdit->setText("RE: " + oldmail.get_subject() );
  toMailLineEdit->setText( oldmail.get_from() );
  boxen = &sentmail;
  server = &smtpserver;
  mainAddressBook = &abook;  
}


void sendMailForm::forwardMailSlot( Mail & oldmail, Mailbox & sentmail, Smtp & smtpserver, vector <Contact*> & abook)
{
  string fwdhead = "---------- Forwarded message ----------\n";
  fwdhead = fwdhead + "Date: " + oldmail.get_date() + "\n";
  fwdhead = fwdhead + "From: " +  oldmail.get_from() + "\n";
  fwdhead = fwdhead + "To: " + oldmail.get_to() + "\n\n";
  mailTextEdit->setText( fwdhead + oldmail.get_body() );
  subjectMailLineEdit->setText("FWD: " + oldmail.get_subject() );
  boxen = &sentmail;
  server = &smtpserver;
  mainAddressBook = &abook;  
}




void sendMailForm::addressSlot()
{
    newAdressBook = new aBookForm( this );
    connect( this, SIGNAL( sendAdressBook(vector<Contact*> &) ), 
	     newAdressBook, SLOT( ListContacts(vector<Contact*> &) ));
    emit sendAdressBook(*mainAddressBook);
    newAdressBook->show();
}


void sendMailForm::getAddressSlot(QString address)
{
    toMailLineEdit->setText(address);
}
