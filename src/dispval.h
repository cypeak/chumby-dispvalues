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
		//QLCDNumber* avgval3;
		uint valueiter;
		uint lastval;

};
//-----------------
class URLPage : public QWidget
{
		Q_OBJECT

	public:
		URLPage ( QWidget* parent = 0 );
		QLineEdit* urlLineEdit;
		QLineEdit* sensorLineEdit1;
		QLineEdit* sensorLineEdit2;
		QLineEdit* sensorLineEdit3;

		QPushButton* sen1;
		QPushButton* sen2;
		QPushButton* sen3;

		bool sen1en;
		bool sen2en;
		bool sen3en;

		QLabel* statusLabel;
		QLabel* debugLabel;

	public slots:
		void buttonToggled ( bool );
		//QTextEdit* lastValues;

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
		void startRequest ( QUrl );
		void httpFinished ( int );
		void httpReadyRead ( int );
		void sensorErr ( int );
		void startDisp();
		//void showCurrentVal();
		void showCurrentVal_alt();
		void showAvg();
		void plotData ( Plotter* );
		void getAllSensors();

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
		QNetworkReply* reply1;
		QNetworkReply* reply2;
		QNetworkReply* reply3;
		//QFile* file;
		//bool httpRequestAborted;

		//uint curtimestamp;
		uint valinterval;
		uint fetchinterval;
		uint dlcounter;
		int currentsensor;

		QMap<uint, uint>* map;
		QMap<uint, uint>* map1;
		QMap<uint, uint>* map2;
		QMap<uint, uint>* map3;

		QTimer* tfetch;
		QTimer* tshow;
		//QTimer* tavg;

		QSignalMapper* finishedMapper;
		QSignalMapper* readyreadMapper;
		QSignalMapper* errMapper;
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
