#include <qapplication.h>
#include "mainWindow.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    spamMaster2000 w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
