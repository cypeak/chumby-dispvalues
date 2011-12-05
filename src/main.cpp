#include <QApplication>

#include "dispval.h"

int main ( int argc, char **argv )
{
	QApplication app ( argc, argv );
	app.setOverrideCursor( QCursor( Qt::BlankCursor ) );
	
	Display dlg;
	dlg.showFullScreen();
	dlg.show();
	
	return app.exec();
}
