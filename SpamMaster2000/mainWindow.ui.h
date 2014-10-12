/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
using namespace std;
Mailboxes *mailboxes;
Mailbox *mailbox;
Mailbox *inbox;
Mailbox *sentbox;
Mail *mail;
bool headers;
Prefs *prefs;
Pop *popserver;
Smtp *smtpserver;

vector<Contact*> abook;


void spamMaster2000::init()
{

    load_abook(abook, "./abook.xml");
    mailboxes = new Mailboxes();
    
    newMail = 0;
    newMailbox = 0;
    newMailsave = 0;
    newAdressBook = 0;
    headers = FALSE;
    inbox = mailboxes->get_inbox();
    sentbox = mailboxes->get_sentbox();
    mailbox = inbox;
    refreshMainWindow();
    refreshComboBoxes();
    prefs = new Prefs();
    popserver = new  Pop( prefs->get_pop(),
			  prefs->get_popUser(),
			  prefs->get_popPass());
    smtpserver = new Smtp( prefs->get_smtp(),
			   prefs->get_name(),
			   prefs->get_address());
    signature = prefs->get_signature();

}

void spamMaster2000::destroy()
{
    save_abook(abook, "./abook.xml");
    delete mailboxes;	
}

void spamMaster2000::writeButtonPushed()
{
    MailForm();
}

void spamMaster2000::MailForm()
{  
  newMail = new sendMailForm( this);
  connect( this, SIGNAL( newButtonClicked( Mailbox&,Smtp&, vector <Contact*>&, QString ) ),
	   newMail, SLOT( newMailSlot( Mailbox&, Smtp&, vector <Contact*>&, QString ) ) );
  emit (newButtonClicked( *sentbox, *smtpserver,  abook, signature ));
  newMail->show();
}


void spamMaster2000::mailDoubleClickedSlot()
{
    //Do we have any  items in the list?
    if (mailListView->childCount()  == 0) return;
    
    int pos;
    QListViewItem *element = mailListView->currentItem();
    pos = element->itemPos()/element->totalHeight();  
    if ( mailListView->sortColumn() == 0)
	mailbox->mailsort("Date");
    else if( mailListView->sortColumn() == 1)
	mailbox->mailsort("From");
    else if( mailListView->sortColumn() == 2)
	mailbox->mailsort("Subject");
    if ( mailListView->sortOrder() == 1)
	mailbox->rsort();
    
    mail = mailbox->mail_list.at(pos);
    
    if ( mail )
    {
	dateLineEdit->setText(mail->get_date());
	fromLineEdit->setText(mail->get_from());
	toLineEdit->setText(mail->get_to());
	subjectLineEdit->setText(mail->get_subject());
	if (headers)
	    mailBodyTextBrowser->setText(mail->get_headers() + "\n\n\n" +mail->get_body());
	else
	    mailBodyTextBrowser->setText(mail->get_body());
    }	
}


void spamMaster2000::newMailboxDialogSlot()
{
    
    newMailbox = new newMailboxDialog( this );
    connect( newMailbox, SIGNAL( okCreateMailbox(const QString& ) ),
	     this, SLOT( createNewMailbox(const QString& )) );
    
    newMailbox->show();
    
    
}


void spamMaster2000::viewedMailboxComboboxl()
{
    

    if (viewMailboxComboBox->currentItem() == 0)
	mailbox = inbox;
    else if (viewMailboxComboBox->currentItem() == 1)
	mailbox = sentbox;
    else
	mailbox = mailboxes->box_list.at(viewMailboxComboBox->currentItem() -2 );
    refreshMainWindow();    
}

void spamMaster2000::forwardButtonPushed()
{
    if (!mail) return;
    newMail = new sendMailForm( this );
  connect ( this, SIGNAL( forwardButtonClicked( Mail&, Mailbox&, Smtp&, vector <Contact*> & ) ),
	    newMail, SLOT( forwardMailSlot( Mail&, Mailbox&, Smtp&, vector <Contact*> & ) ) );
  emit forwardButtonClicked( *mail, *sentbox, *smtpserver, abook);
  
  newMail->show();
}

void spamMaster2000::titleClicked()
{

}


void spamMaster2000::moveToMailboxSlot()
{
 
   if (mail) {
       if (moveToComboBox->currentItem() == 1)
	   mailbox->move(mail, inbox);
       else if (moveToComboBox->currentItem() == 2)
	   mailbox->move(mail, sentbox);
       else if (mailbox->get_name() != moveToComboBox->currentText()  && moveToComboBox->currentItem() != 0)
	   mailbox->move(mail, mailboxes->box_list.at(moveToComboBox->currentItem() -3));
       
       refreshMainWindow();       

   }	
   moveToComboBox->setCurrentItem(0);

}


void spamMaster2000::deleteMail()
{
 
    if (mail) {
	mailbox->remove(mail);
	refreshMainWindow();  
    }
}


void spamMaster2000::refreshMainWindow()
{
    int i;
    mailListView->clear();

    for (i = 0; i<mailbox->get_index(); i++) {
	QListViewItem element = new QListViewItem( mailListView, mailbox->mail_list.at(i)->get_date(), mailbox->mail_list.at(i)->get_from(), mailbox->mail_list.at(i)->get_subject() );
    }
    mail = NULL;

    dateLineEdit->setText("");
    fromLineEdit->setText("");
    toLineEdit->setText("");
    subjectLineEdit->setText("");
    mailBodyTextBrowser->setText("");
    
}




void spamMaster2000::replyButtonPushed()
{
    if (!mail) return;
    newMail = new sendMailForm( this );
  connect ( this, SIGNAL( replyButtonClicked( Mail&, Mailbox&, Smtp&, vector <Contact*> & ) ),
	    newMail, SLOT( replyMailSlot( Mail&, Mailbox&, Smtp&, vector <Contact*> & ) ) );
  emit replyButtonClicked( *mail, *sentbox, *smtpserver, abook);
  newMail->show();
}

void spamMaster2000::fetchMailSlot()
{
    int new_mails = popserver->pop(*inbox);
    if ( new_mails > 0 ) {
      stringstream ss;
      ss << "Your mailbox has just been invaded by " << new_mails;
      ss << " new spams." << endl;
      string infotxt;
      getline(ss,infotxt);
      
      QMessageBox::information( this , "You got Spammed" , 
				infotxt ,QMessageBox::Ok);
    }
    else {
      QMessageBox::information( this , "No Spam" , 
				"No new Spam right now!" ,
				QMessageBox::Ok);
    }
    refreshMainWindow();
}


void spamMaster2000::createNewMailbox( const QString& name)
{
    string baaas = name; 
    Mailbox *halifax = new Mailbox( baaas );
    mailboxes->import(halifax);
    refreshComboBoxes();    
    
}


void spamMaster2000::saveMailDialogSlot()
{

    newMailsave = new SaveMail( this );
    connect( newMailsave, SIGNAL( sendMailName( const QString& ) ),
	     this, SLOT( saveMailSlot(const QString& ) ) );
    
    newMailsave->show();
    
}


void spamMaster2000::saveMailSlot( const QString& name )
{
    string kraas = name;
    mail->mailsave( kraas );
}


void spamMaster2000::adressBookSlot()
{
    
    newAdressBook = new aBookForm( this );
    connect( this, SIGNAL( sendAdressBook(vector<Contact*> &) ), 
	     newAdressBook, SLOT( ListContacts(vector<Contact*> &) ));
    emit sendAdressBook(abook);
    newAdressBook->show();
}


void spamMaster2000::refreshComboBoxes()
{
    int i;    
    moveToComboBox->clear();
    viewMailboxComboBox->clear();
    moveToComboBox->insertItem("Select box");
    moveToComboBox->insertItem("inbox");
    moveToComboBox->insertItem("sent_mail");
    viewMailboxComboBox->insertItem("inbox");
        viewMailboxComboBox->insertItem("sent_mail");
    
    for (i = 0; i<mailboxes->get_index();i++) 
    {
	viewMailboxComboBox->insertItem(mailboxes->box_list.at(i)->get_name());
	moveToComboBox->insertItem(mailboxes->box_list.at(i)->get_name());
    }

}


void spamMaster2000::headersSlot()
{
    if (headers) {
	headers = FALSE;
	if (mail) mailBodyTextBrowser->setText(mail->get_body());
	
	HeaderPushButton->setText("Headers On");
    }
    else {
	headers = TRUE;
	if (mail) mailBodyTextBrowser->setText(mail->get_headers() + "\n\n\n" + mail->get_body());	   
	HeaderPushButton->setText("Headers Off");
    }
}
