#include "zeiger.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

#include <math.h>


static double binomi ( int i, int n )
{
	if ( i == 0 || i == n ) {
		return 1.0;
	} else {
		return binomi ( n -1, i - 1 ) + binomi ( n - 1, i );
	}
}

static double bernstein ( int i, int n, double t )
{
	return binomi ( i, n ) * pow ( t, i ) * pow ( ( 1 - t ), ( n - i ) );
}

Zeiger::Zeiger() : angle ( -115 ), time ( 0.0 ), soll_angle ( 0 ), old_angle ( 0 )
{
	setTransformationMode ( Qt::SmoothTransformation );
	setShapeMode ( QGraphicsPixmapItem::BoundingRectShape );
}


/*
QPainterPath Zeiger::shape() const
{

	int x = (this->pixmap()).width();
	int y = (this->pixmap()).height();
	//qDebug() << "wid sh: " << x;
	//qDebug() << "hig sh: " << y;
	QPainterPath path;

	path.addRect ( -(x/2), -(y/2), x, y );
	return path;
}
*/

QRectF Zeiger::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF ( -7 - penWidth / 2, -95 - penWidth / 2, 14 + penWidth, 108 + penWidth );
}

/*
QPainterPath Zeiger::shape() const
{
	QPainterPath path;

	path.addRect ( -7, 6, 14, 106 );

	return path;
}
*/

void Zeiger::paint ( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{

	painter->setBrush ( QColor::fromHsv ( 90 + int( ( -90.0 / 270.0 ) * ( angle + 115 ) ), 255, 255  ) );

	painter->setBrush ( Qt::green );

	static const QPoint zeig[3] = {
	                                QPoint ( 7, 8 ),
	                                QPoint ( -7, 8 ),
	                                QPoint ( 0, -95 )
	                              };

	painter->drawConvexPolygon ( zeig, 3 );
}


void Zeiger::advance ( int step )
{
	if ( !step )
		return;

	if ( old_angle == soll_angle ) {
		time = 0.0;
		return;
	}

	//old not-so-smooth-method...
	/*
	if ( angle > ( soll_angle + 3.0 ) ) {
		angle -= 3.0;
	} else if ( angle < ( soll_angle - 3.0 ) ) {
		angle += 3.0;
	} else {
		angle = soll_angle;
	}

	if ( angle >= 360 ) {
		angle -= 360;
	}*/

	int showan = 0;

	double t = time / 49.0;
	time += 1.0;

	showan = ( bernstein ( 0, 1, t ) * old_angle ) + ( bernstein ( 1, 1, t ) * soll_angle );


	angle = showan - 115;
	setRotation ( angle );
}


void Zeiger::setVal ( uint value )
{
	double zw = double ( value ) / 4500.0;
	//soll_angle = -115 + int ( 270 * zw );
	if ( zw >= 1.0 ) {
		soll_angle = 270;
	} else {
		soll_angle = int ( 270 * zw );
	}

	old_angle = angle + 115 ;
	time = 0.0;
	qDebug() << "zeiger_soll: " << soll_angle;
	qDebug() << "zeiger_ist: " << old_angle;
}
