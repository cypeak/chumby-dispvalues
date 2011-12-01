#ifndef __DISPVAL_H__
#define __DISPVAL_H__

#include <QDialog>

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTimer>
#include <QMap>
#include <QLCDNumber>
//#include <QPalette>
//#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QUrl>
//#include <QFile>

#include <QDebug>
#include "json/json.h"
#include "plotter/converter.h"
#include "plotter/plotter.h"
#include "plotter/plotsettings.h"
#include <cmath>

class Plotter;
class TimeConverter_m; //plot label formater with minutes resolution
class TimeConverter_s; //plot label formater with seconds resolution

//-----------------
class DisplayPage : public QWidget
{
	public:
		DisplayPage ( QWidget* parent = 0 );
		QLCDNumber* digitalClk;
		QLCDNumber* sensorval;
		QLCDNumber* avgval1;
		QLCDNumber* avgval2;
		QLCDNumber* avgval3;

};
//-----------------
class URLPage : public QWidget
{
	public:
		URLPage ( QWidget* parent = 0 );
		QLineEdit* urlLineEdit;
		QLineEdit* sensorLineEdit;
		
		QLabel* statusLabel;
		QLabel* debugLabel;
		QTextEdit* lastValues;

};

//-----------------
class PlotPage : public QWidget
{
	public:
		PlotPage ( QWidget* parent = 0 );
		Plotter* plotter;

};

//----------------------
class Display : public QDialog
{
		Q_OBJECT

	public:
		Display();

	private slots:
		void doNext();
		void doPrev();
		void enablestartButton();
		void getSensorData();
		void startRequest ( QUrl url );
		void httpFinished();
		void httpReadyRead();
		void sensorErr();
		void startDisp();
		void showCurrentVal();
		void showAvg();
		void plotData ( Plotter* plotter );

	private:
		QPushButton* startButton;
		QPushButton* quitButton;
		QPushButton* next;
		QPushButton* previous;

		QStackedWidget* pages;
		DisplayPage* displayPg;
		URLPage* urlPg;
		PlotPage* plotPg;

		QUrl url;
		QNetworkAccessManager qnam;
		QNetworkReply* reply;
		//QFile* file;
		//bool httpRequestAborted;

		uint curtimestamp;
		uint vinterval;
		uint fetchinterval;
		uint dlcounter;
		QMap<QString, quint32>* map;

		QTimer* tfetch;
		QTimer* tshow;
		//QTimer* tavg;
		QString valConvert ( double value );
};

class TimeConverter_s : public Converter
{
	public:
		QString convert ( double );
};

class TimeConverter_m : public Converter
{
	public:
		QString convert ( double );
};

#endif // __DISPVAL_H__
