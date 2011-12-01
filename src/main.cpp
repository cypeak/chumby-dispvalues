#include <QApplication>

#include "dispval.h"

int main ( int argc, char **argv )
{
	QApplication app ( argc, argv );
	Display dlg;
	dlg.showFullScreen();
	dlg.show();
	app.setOverrideCursor( QCursor( Qt::BlankCursor ) );

	return app.exec();
}
