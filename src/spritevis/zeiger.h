#ifndef __ZEIGER_H__
#define __ZEIGER_H__

#include <QGraphicsItem>

class Zeiger : public QGraphicsPixmapItem
{
	public:
		Zeiger();

		QRectF boundingRect() const;
		//QPainterPath shape() const;
		void paint ( QPainter*, const QStyleOptionGraphicsItem*, QWidget* );
		void setVal ( uint );

	protected:
		void advance ( int );


	private:
		double angle;
		double speed;
		bool vor;
		int soll_angle;
};

#endif // __ZEIGER_H__
