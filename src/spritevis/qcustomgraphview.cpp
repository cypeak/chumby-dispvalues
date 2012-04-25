#include "qcustomgraphview.h"
#include <QDebug>
#include <QtGui>


CustQGraphView::CustQGraphView ( QWidget* parent = 0 ) : QGraphicsView ( parent )
{}

CustQGraphView::CustQGraphView ( QGraphicsScene* scene, QWidget* parent) : QGraphicsView ( scene, parent )
{}


void CustQGraphView::drawBackground ( QPainter* painter, const QRectF& rect )
{
	qDebug() << "background rect: " << rect << endl;

	QPixmap *backgroundPixmap = new QPixmap ( ":/images/tachos.jpg" );
	QPixmap sized = backgroundPixmap->scaled ( QSize ( rect.width(), rect.height() ), Qt::KeepAspectRatioByExpanding );

	painter->drawPixmap ( rect, sized, QRect ( 0.0, 0.0, sized.width(), sized.height() ) );

}