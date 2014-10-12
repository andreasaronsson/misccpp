/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
using namespace std;

vector<Contact*>::iterator it;
vector<Contact*> *mainAddrBook;
Contact *contact;
int pp;

void aBookForm::init()
{
    newCon=0;
    
}


void aBookForm::addContactButton()
{

    newCon = new addContactForm(this);
    connect ( newCon, SIGNAL ( contactSignal(Contact &) ),
	      this, SLOT ( addContactSlot(Contact &) ) );
    newCon->show();
    
}
void aBookForm::ListContacts(vector<Contact*> & abook)
{
    contactListView->clear();
    it  = abook.begin();
    while( it != abook.end()){
	QListViewItem element = new QListViewItem(contactListView,(*it)->get_firstname(),  (*it)->get_lastname(), (*it)->get_email());
	it++;
    }
    mainAddrBook = &abook;
}


void aBookForm::addContactSlot( Contact & newContact )
{
    mainAddrBook->push_back( &newContact );
    ListContacts(*mainAddrBook);
}


void aBookForm::deleteContactSlot()
{
	cerr << "hej då" << endl << pp << endl;
    if(contact) {
	cerr << "hej" << endl;
	delete_contact(*mainAddrBook, pp);
	ListContacts(*mainAddrBook);

    }	
}


void aBookForm::contactClickedSlot()
{
    //Abort if empty list
    if (contactListView->childCount() == 0) return;
    int pos;
    QListViewItem *element = contactListView->currentItem();
    pos = element->itemPos()/element->totalHeight();
    if ( contactListView->sortColumn() == 0) 
    {
	sort_first(*mainAddrBook);
    }
    else if( contactListView->sortColumn() == 1)
	sort_last(*mainAddrBook);
    if ( contactListView->sortOrder() == 1)
	rsort(*mainAddrBook);

    
      contact = mainAddrBook->at(pos);
      pp = pos;

}


void aBookForm::putAddressSlot()
{
    connect( this, SIGNAL( sendAddress(QString) ), 
	     this->parentWidget(), SLOT( getAddressSlot(QString) ));
    emit sendAddress(contactListView->currentItem()->text(2));
    close();

}
