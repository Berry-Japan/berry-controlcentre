#include <qapplication.h>
#include "berry_control_centre.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    Berry_Control_Centre w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
