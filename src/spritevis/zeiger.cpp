#include "zeiger.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static double normalizeAngle ( double angle )
{
	while ( angle < 0 )
		angle += TwoPi;
	while ( angle > TwoPi )
		angle -= TwoPi;
	return angle;
}


Zeiger::Zeiger()
		: angle ( -115 ), speed ( 0 ), vor ( true ), soll_angle ( 0 )
{
	//setPixmap ( QPixmap ( ":/images/windradt.png" ) );
	//setRotation(0);
	//setRotation ( qrand() % ( 360 * 16 ) );
	//int xo = QPixmap ( ":/images/windradt.png" ).width();
	//
	//int yo = QPixmap ( ":/images/windradt.png" ).height();
	//qDebug() << "wid: " << xo;
	//qDebug() << "hig: " << yo;
	//setOffset ( -( xo / 2 ) , -( yo / 2 ) );
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
	return QRectF ( -7 - penWidth / 2, -100 - penWidth / 2, 14 + penWidth, 108 + penWidth );
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
	if ( angle < -90 ) {
		painter->setBrush ( Qt::green );
	} else if ( angle < -8 ) {
		painter->setBrush ( Qt::white );
	} else if ( angle < 74 ) {
		painter->setBrush ( Qt::yellow );
	} else if ( angle < 160 ) {
		painter->setBrush ( Qt::red );
	}

	//painter->setBrush ( Qt::green );

	static const QPoint zeig[3] = {
	                                QPoint ( 7, 8 ),
	                                QPoint ( -7, 8 ),
	                                QPoint ( 0, -100 )
	                              };

	painter->drawConvexPolygon ( zeig, 3 );
}


void Zeiger::advance ( int step )
{
	if ( !step )
		return;


	if ( angle > ( soll_angle + 3.0 ) ) {
		angle -= 3.0;
	} else if ( angle < ( soll_angle - 3.0 ) ) {
		angle += 3.0;
	} else {
		angle = soll_angle;
	}


	if ( angle >= 360 ) {
		angle -= 360;
	}

	//qDebug() << "rot: " << dx << " -> ang: " << angle << " -> xrot: " << rotation();
	//setRotation ( rotation() + dx );
	//qDebug() << "ang: " << angle << " -> xrot: " << rotation();
	setRotation ( angle );
}

void Zeiger::setVal ( uint value )
{	
	double zw = double(value) / 4500.0;
	soll_angle = -115 + int ( 270 * zw );
	//qDebug() << "zeiger: " << soll_angle;
}
