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
		
		void clearMap(QMap<uint, uint>* map);

	private slots:
		void doNext();
		void doPrev();
		void enablestartButton();
		void getSensorData();
		void startRequest ( QUrl );
		void httpFinished ( QObject* );
		void httpReadyRead ( QObject* );
		void sensorErr ( QObject* );
		void startDisp();
		void showCurrentVal_alt();
		void showAvg();
		void plotData ( Plotter* );
		void plotData_new ( Plotter* );
		QVector<QPointD> plotData_helper ( QMap<uint, uint>*, int, uint&, uint& );
		void getAllSensors();
		void buttonToggled_gatekeeper ( bool );

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
		//QNetworkReply* reply;
		QNetworkReply* reply1;
		QNetworkReply* reply2;
		QNetworkReply* reply3;
		//QFile* file;

		//uint curtimestamp;
		uint valinterval;
		uint fetchinterval;
		uint dlcounter;
		int currentsensors;

		//QMap<uint, uint>* map;
		QMap<uint, uint>* map1;
		QMap<uint, uint>* map2;
		QMap<uint, uint>* map3;
		QList<QMap<uint, uint>* >* maps;

		QTimer* tfetch;
		QTimer* tshow;

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
