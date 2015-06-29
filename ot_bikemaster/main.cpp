#include <qapplication.h>
#include "mainform.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    
    //Instruct the db to look in the right places
    string username = getenv("USER"); //to be used in final app
    //string username = "ot04-5";
    // cout << endl << "DATABASE NAME:\t" << username << endl;
    if (! DbConn::Instance()->changeDb(username)) {
        cerr << endl <<  "PANIC! COULD NOT CHANGE DB!!" << endl;
        exit(1);
   }

    MainForm w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
