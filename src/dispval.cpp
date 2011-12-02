#include "dispval.h"


DisplayPage::DisplayPage ( QWidget* parent ) : QWidget ( parent )
{
	digitalClk = new QLCDNumber ();
	digitalClk->setSegmentStyle ( QLCDNumber::Filled );
	digitalClk->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );
	digitalClk->setMaximumSize ( 220, 32 );
	digitalClk->setMinimumSize ( 190, 30 );
	digitalClk->setDigitCount ( 8 );
	digitalClk->display ( "00:00:00" );

	QLabel* clkLabel = new QLabel ( "<span style='font-size:16pt;'>Timestamp</span>" );
	clkLabel->setTextFormat ( Qt::RichText );
	clkLabel->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );

	QHBoxLayout* clkLayout = new QHBoxLayout();
	clkLayout->addWidget ( clkLabel );
	clkLayout->addWidget ( digitalClk );

	sensorval = new QLCDNumber ();
	sensorval->setSegmentStyle ( QLCDNumber::Filled );
	sensorval->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );
	sensorval->setMinimumSize ( 190, 75 );
	sensorval->setMaximumSize ( 200, 80 );

	QLabel* sensorLabel = new QLabel ( "<span style='font-size:16pt;'>Consumption</span><br><span style='font-size:12pt;'>Watt</span>" );
	sensorLabel->setTextFormat ( Qt::RichText );
	sensorLabel->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );

	QHBoxLayout* sensorLayout = new QHBoxLayout();
	sensorLayout->addWidget ( sensorLabel );
	sensorLayout->addWidget ( sensorval );

	QGridLayout* avgLayout = new QGridLayout();
	QLabel* avgLabel1 = new QLabel ( tr ( "avg.(1m)" ) );
	QLabel* avgLabel2 = new QLabel ( tr ( "avg.(15m)" ) );
	//QLabel* avgLabel3 = new QLabel ( tr ( "avg.(1h)" ) );
	avgLabel1->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );
	avgLabel2->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );
	//avgLabel3->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );
	avgLabel1->setAlignment ( Qt::AlignRight );
	avgLabel2->setAlignment ( Qt::AlignRight );
	//avgLabel3->setAlignment ( Qt::AlignRight );
	avgLabel1->setMaximumSize ( 150, 20 );
	avgLabel2->setMaximumSize ( 150, 20 );
	//avgLabel3->setMaximumSize ( 150, 20 );
	avgval1 = new QLCDNumber ();
	avgval2 = new QLCDNumber ();
	//avgval3 = new QLCDNumber ();
	avgval1->display ( "---" );
	avgval2->display ( "---" );
	//avgval3->display ( "---" );
	avgval1->setSegmentStyle ( QLCDNumber::Filled );
	avgval1->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );
	avgval2->setSegmentStyle ( QLCDNumber::Filled );
	avgval2->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );
	//avgval3->setSegmentStyle ( QLCDNumber::Filled );
	//avgval3->setFrameStyle ( QFrame::StyledPanel | QFrame::Plain );

	avgLayout->addWidget ( avgLabel1, 0, 0, 1, 1 );
	avgLayout->addWidget ( avgLabel2, 0, 1, 1, 1 );
	//avgLayout->addWidget ( avgLabel3, 0, 2, 1, 1 );
	avgLayout->addWidget ( avgval1, 1, 0, 1, 1 );
	avgLayout->addWidget ( avgval2, 1, 1, 1, 1 );
	//avgLayout->addWidget ( avgval3, 1, 2, 1, 1 );
	avgLayout->setSpacing ( 1 );

	QVBoxLayout* layout = new QVBoxLayout ( this );
	layout->addLayout ( clkLayout );
	layout->addLayout ( sensorLayout );
	layout->addLayout ( avgLayout );
	layout->setContentsMargins ( 0, 0, 0, 0 );
	layout->setSpacing ( 4 );

	valueiter = 0;
	lastval = 0;
}


URLPage::URLPage ( QWidget* parent ) : QWidget ( parent )
{
	QLabel* urlLabel = new QLabel ( tr ( "Flukso IP:Port" ) );
	//urlLineEdit = new QLineEdit ( "http://131.246.191.27:8080/sensor/032ae0de09d3133583fb52da37a5a276?unit=watt&interval=minute&version=1.0" );
	urlLineEdit = new QLineEdit ( "131.246.191.27:8080" );

	QLabel* sensorLabel = new QLabel ( tr ( "Sensor:" ) );
	sensorLineEdit = new QLineEdit ( "032ae0de09d3133583fb52da37a5a276" );

	QHBoxLayout* topLayout = new QHBoxLayout;
	topLayout->addWidget ( urlLabel );
	topLayout->addWidget ( urlLineEdit );

	QHBoxLayout* topLayout2 = new QHBoxLayout;
	topLayout2->addWidget ( sensorLabel );
	topLayout2->addWidget ( sensorLineEdit );

	statusLabel = new QLabel ( tr ( "Status: ----" ) );
	debugLabel = new QLabel ( tr ( "Mapsize: ----" ) );
	//lastValues = new QTextEdit();

	QLabel* info = new QLabel ( tr ( "Settings / Debug " ) );
	QVBoxLayout* layout = new QVBoxLayout ( this );
	layout->addWidget ( info );
	layout->addStretch();
	layout->addLayout ( topLayout );
	layout->addLayout ( topLayout2 );
	layout->addStretch();
	layout->addWidget ( statusLabel );
	layout->addWidget ( debugLabel );
	//layout->addWidget ( lastValues );
	layout->addStretch();
	layout->setContentsMargins ( 0, 0, 0, 0 );
	layout->setSpacing ( 5 );
}


PlotPage::PlotPage ( QWidget* parent ) : QWidget ( parent )
{
	QVBoxLayout* layout = new QVBoxLayout ( this );
	plotter = new Plotter ( this );
	
	TimeConverter_s* tc = new TimeConverter_s(); //create a new converter object...
	plotter->setConverter ( tc ); //override the default "do-nothing"-converter
	
	layout->addWidget ( plotter );
	layout->setContentsMargins ( 0, 0, 0, 0 );
	layout->setSpacing ( 5 );
}


Display::Display() : QDialog()
{
	startButton = new QPushButton ( tr ( "Start" ) );
	startButton->setDefault ( true );
	quitButton = new QPushButton ( tr ( "Quit" ) );
	quitButton->setAutoDefault ( false );
	previous = new QPushButton ( tr ( "Plot" ) );
	next = new QPushButton ( tr ( "Debug" ) );

	QHBoxLayout* mainbuttonBox = new QHBoxLayout();
	mainbuttonBox->addWidget ( startButton );
	mainbuttonBox->addWidget ( previous );
	mainbuttonBox->addWidget ( next );
	mainbuttonBox->addWidget ( quitButton );
	mainbuttonBox->setContentsMargins ( 0, 0, 0, 0 );
	mainbuttonBox->setSpacing ( 5 );

	pages = new QStackedWidget ( this );

	QVBoxLayout* mainlayout = new QVBoxLayout ( this );
	mainlayout->setContentsMargins ( 5, 10, 5, 8 );
	mainlayout->setSpacing ( 6 );
	mainlayout->addWidget ( pages );
	mainlayout->addLayout ( mainbuttonBox );

	connect ( next, SIGNAL ( clicked() ), this, SLOT ( doNext() ) );
	connect ( previous, SIGNAL ( clicked() ), this, SLOT ( doPrev() ) );

	pages->addWidget ( displayPg = new DisplayPage ( pages ) ); // index 0
	pages->addWidget ( plotPg = new PlotPage ( pages ) ); // index 1
	pages->addWidget ( urlPg = new URLPage ( pages ) ); // index 2

	connect ( startButton, SIGNAL ( clicked() ), this, SLOT ( startDisp() ) );
	connect ( quitButton, SIGNAL ( clicked() ), this, SLOT ( close() ) );
	connect ( urlPg->urlLineEdit, SIGNAL ( textChanged ( QString ) ), this, SLOT ( enablestartButton() ) );

	//curtimestamp  = 0;
	valinterval   = 2;
	fetchinterval = 8;
	dlcounter = 0;

	tfetch = new QTimer();
	tshow = new QTimer();

	tfetch->setInterval ( 1000 * fetchinterval );
	tshow->setInterval ( 1000 * valinterval );

	map = new QMap<uint, uint>();

	connect ( tshow, SIGNAL ( timeout() ), this, SLOT ( showCurrentVal_alt() ) );
	connect ( tfetch, SIGNAL ( timeout() ), this, SLOT ( getSensorData() ) );

	qDebug() << "created..";
}


void Display::doNext()
{
	switch ( pages->currentIndex() ) {

		case 0: //displayPg
			pages->setCurrentWidget ( urlPg );
			previous->setText ( tr ( "Numbers" ) );
			next->setText ( tr ( "Plot" ) );
			break;

		case 1: //plotPg
			pages->setCurrentWidget ( urlPg );
			previous->setText ( tr ( "Numbers" ) );
			next->setText ( tr ( "Plot" ) );
			break;

		case 2: //urlPg
			pages->setCurrentWidget ( plotPg );
			previous->setText ( tr ( "Numbers" ) );
			next->setText ( tr ( "Debug" ) );
			break;
	}
}


void Display::doPrev()
{

	switch ( pages->currentIndex() ) {

		case 0: //displayPg
			pages->setCurrentWidget ( plotPg );
			previous->setText ( tr ( "Numbers" ) );
			next->setText ( tr ( "Debug" ) );
			break;

		case 1: //plotPg
			pages->setCurrentWidget ( displayPg );
			//previous->setEnabled ( false );
			previous->setText ( tr ( "Plot" ) );
			next->setText ( tr ( "Debug" ) );
			break;

		case 2: //urlPg
			pages->setCurrentWidget ( displayPg );
			previous->setText ( tr ( "Plot" ) );
			//next->setEnabled ( true );
			next->setText ( tr ( "Debug" ) );
			break;
	}
}


void Display::enablestartButton()
{
	startButton->setEnabled ( !urlPg->urlLineEdit->text().isEmpty() );
}


void Display::startDisp()
{
	if ( tshow->isActive() || tfetch->isActive() ) {
		qDebug() << "stoping...";
		tfetch->stop();
		tshow->stop();
		//tavg->stop();
		qDebug() << "timer stoped.";
		//curtimestamp = 0;
		dlcounter = 0;
		map->clear();
		startButton->setText ( tr ( "Start" ) );
		urlPg->statusLabel->setText ( tr ( "Stopped" ) );
	} else {
		qDebug() << "starting...";
		getSensorData();
		tfetch->start();
		tshow->start();
		//tavg->start();
		qDebug() << "timer started...";
		startButton->setText ( tr ( "Stop" ) );
	}

}


void Display::getSensorData()
{
	QString sensortxt = "/sensor/" + urlPg->sensorLineEdit->text() + "?unit=watt&interval=minute&version=1.0";
	url.setUrl ( "http://" + urlPg->urlLineEdit->text() + sensortxt );
	//qDebug() << "url: " << url.toString();

	//httpRequestAborted = false;
	startRequest ( url );
}

QString Display::valConvert ( double value )
{
	QDateTime dtime = QDateTime::fromMSecsSinceEpoch ( qint64 ( value ) * 1000 );
	return dtime.toString ( "hh:mm:ss" );
}


void Display::plotData ( Plotter* plotter )
{
	int plotlen = 900;

	if ( plotlen > 240 ) {
		TimeConverter_m* tc = new TimeConverter_m();
		plotPg->plotter->setConverter ( tc );
	}

	uint minx = 0;
	uint maxx = ( map->end() - 1 ).key();
	uint miny = ( map->end() - 1 ).value();
	uint maxy = 0;

	int msize = map->size();
	minx = ( ( map->begin() ).key() ) - ( plotlen - msize );
	int goback = ( msize < plotlen ) ? msize : plotlen ;

	QVector<QPointD> plval;

	QMap<uint, uint>::const_iterator i;

	for ( i = map->constEnd() - goback ; i != map->constEnd(); ++i ) {

		uint val = i.value();

		plval.append ( QPointD ( i.key(), val ) );
		//qDebug() << "key: " << i.key() <<  " keyval: " <<  QString::number ( keyval , 'f', 1 ) << "val: " << val;

		if ( val > maxy ) {
			maxy = val;
		} else if ( val < miny ) {
			miny = val;
		}
	}

	//QVector<QPointD>::const_iterator p;
	//for ( p = plval.constBegin() ; p != plval.constEnd(); ++p ) {
	//qDebug() << "x: " << QVariant ( p->x() ).toUInt() << "y: " << p->y();
	//}

	//qDebug() << "minx: " << minx << "maxx: " <<  maxx;
	//qDebug() << "minx: " << QString::number ( minx , 'f', 0 ) << "maxx: " << QString::number ( maxx , 'f', 0 );
	//qDebug() << "minx_float: " << QString::number ( QVariant ( minx ).toFloat() , 'f', 0 ) << "maxx_float: " << QString::number ( QVariant ( maxx ).toFloat(), 'f', 0 );
	//qDebug() << "minx_double: " << QString::number ( QVariant ( minx ).toDouble() , 'f', 0 ) << "maxx_double: " << QString::number ( QVariant ( maxx ).toDouble(), 'f', 0 );
	//qDebug() << "minx_real: " << QString::number ( QVariant ( minx ).toReal() , 'f', 0 ) << "maxx_real: " << QString::number ( QVariant ( maxx ).toReal(), 'f', 0 );
	//qDebug() << "miny: " << miny << "maxy: " << maxy;
	//qDebug() << "diff: " << ( maxx - minx );
	//qDebug() << "plotval size: " << plval.size();

	miny = miny - std::floor ( miny * 0.1 );
	maxy = maxy + std::ceil ( maxy * 0.1 );
	//miny -= ( miny * 0.1 );
	//maxy += ( maxy * 0.1 );

	PlotSettings* pset = new PlotSettings (  minx, miny, maxx, maxy, 4, 5 );
	plotter->setPlotSettings ( *pset );
	//plotter->setPlotSettings ( *(new PlotSettings (  minx, miny, maxx, maxy, 4, 5 )) );
	plotter->setCurveData ( 1, plval );
}


void Display::startRequest ( QUrl url )
{
	reply = qnam.get ( QNetworkRequest ( url ) );
	urlPg->statusLabel->setText ( tr ( "Downloading sensor data..." ) );
	connect ( reply, SIGNAL ( finished() ), this, SLOT ( httpFinished() ) );
	connect ( reply, SIGNAL ( readyRead() ), this, SLOT ( httpReadyRead() ) );
	connect ( reply, SIGNAL ( error ( QNetworkReply::NetworkError ) ), this, SLOT ( sensorErr() ) );
	//connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),this, SLOT ( updateDataReadProgress ( qint64, qint64 ) ) );
}


void Display::httpFinished()
{

	QVariant redirectionTarget = reply->attribute ( QNetworkRequest::RedirectionTargetAttribute );

	if ( reply->error() ) {
		qDebug() << QString ( tr ( "Sensordata Download failed: %1." ).arg ( reply->errorString() ) );
	} else if ( !redirectionTarget.isNull() ) {
		QUrl newUrl = url.resolved ( redirectionTarget.toUrl() );
		url = newUrl;
		reply->deleteLater();
		startRequest ( url );
		return;
	} else {
		dlcounter += 1;
		urlPg->statusLabel->setText ( tr ( "Sensordata downloaded! (count: %1)" ).arg ( dlcounter ) );
	}

	reply->deleteLater();
	reply = 0;
}


// this slot is only triggered when QNetworkReply has new data available,
// not when the finished() signal is emmited - this way we use less RAM
void Display::httpReadyRead()
{
	QByteArray result;
	result = reply->readAll();

	bool ok;
	QVariantList json = QtJson::Json::parse ( QString ( result ), ok ).toList();

	if ( !ok ) {
		qFatal ( "An error occurred during parsing" );
	} else {
		if ( json.isEmpty() ) {
			qDebug() << "json data is empty!";
		}

		foreach ( QVariant data, json ) {
			if ( data.toList().value ( 1 ).toString() != "nan" ) {
				map->insert ( data.toList().value ( 0 ).toUInt(), data.toList().value ( 1 ).toUInt() );
			} else {
				map->insert ( data.toList().value ( 0 ).toUInt(), 0 );
				qDebug() << "zero value inserted! - map size was: " << map->size();
			}
			//qDebug() << data.toList().value(1).toString();
		}

		//if ( curtimestamp == 0 ) {
			//curtimestamp = map->constBegin().key() + 50;
			//qDebug() << "first stamp - now: " << curtimestamp;
			//qDebug() << "first stamp - last: " << ( map->constEnd() - 1 ).key();
		//}

		if ( map->size() > 2100 ) {
			QMap<uint, uint>::iterator i = map->begin();
			while ( i != map->end() - 1801  ) {
				i = map->erase ( i );
			}
			qDebug() << "new map size: " << map->size();
		}

		//QString lval;
		//QMap<uint, uint>::const_iterator i;
		//for ( i = map->constEnd() - 1 ; i != map->constEnd() - 6; --i ) {
			//lval.append ( "k: " + QString::number ( i.key() ) + " - v: " + QString::number ( i.value() ) + "\n" );
		//}
		//urlPg->lastValues->setPlainText ( lval );

		urlPg->debugLabel->setText ( tr ( "Map size is: %1" ).arg ( map->size() ) );

		// when there is new data available in the map (= when parsed json data)
		// the moving averages and the plot curves should be updated...
		showAvg();
		plotData ( plotPg->plotter );
	}

}


//void Display::showCurrentVal()
//{
	//QDateTime dtime = QDateTime::fromMSecsSinceEpoch ( quint64 ( curtimestamp ) * 1000 );
	//displayPg->digitalClk->display (  dtime.toString ( "hh:mm:ss" ) );

	//if ( map->contains ( curtimestamp ) ) {
		//QString val = QString::number ( map->value ( curtimestamp ) );
		//displayPg->sensorval->display ( val );
	//} else {
		//qDebug() << "no value in map!";
		//displayPg->sensorval->display ( "----" );
	//}

	//curtimestamp += valinterval;
//}

void Display::showCurrentVal_alt()
{
	//qDebug() << "lastval: " << displayPg->lastval;
	//qDebug() << "mapend:" << ( map->constEnd() - 1 ).key();

	if ( ! ( displayPg->lastval == ( map->constEnd() - 1 ).key() ) ) {
		displayPg->lastval = ( map->constEnd() - 1 ).key();
		displayPg->valueiter = 0;
		//qDebug() << "--------------";
	} else {
		displayPg->valueiter = displayPg->valueiter + valinterval;
		//qDebug() << "valiter: " << displayPg->valueiter;
	}

	uint show = ( map->constEnd() - 1 - ( int ) fetchinterval + ( int ) displayPg->valueiter ).key();

	QDateTime dtime = QDateTime::fromMSecsSinceEpoch ( quint64 ( show ) * 1000 );
	displayPg->digitalClk->display (  dtime.toString ( "hh:mm:ss" ) );
	displayPg->sensorval->display (  QString::number ( map->value ( show ) ) );
	
	//qDebug() << "show:" << show;
	//qDebug() << "mapvals: "  <<  map->value ( show ) << "\n";
}


void Display::showAvg()
{
	uint avg1 = 0;
	uint avg2 = 0;
	//uint avg3 = 0;
	//int c = 0;
	int size = map->size();
	int a1end = 0;
	int a2end = 0;
	//int a3end = 0;

	if ( map->isEmpty() ) {
		return;
	}

	QMap<uint, uint>::const_iterator i;

	( size < 60 ) ? a1end = size : a1end = 60; //1min
	( size < 900 ) ? a2end = size : a2end = 900; // 10min = 600
	//( size < 3600 ) ? a3end = size : a3end = 3600; // 1h = 3600

	for ( i = ( map->constEnd() - 1 ); i != ( map->constEnd() - 1 - a1end ); --i ) {
		avg1 += i.value(); //hier absichern falls values nicht geliefert wurden...
		//qDebug() << "k:" << i.key() << "v: " << i.value() << "sum: " << avg1;
		//c += 1;
		//qDebug() << "c: " << c;
	}
	avg1 = avg1 / a1end;
	displayPg->avgval1->display ( ( int ) avg1 );
	//qDebug() << "avg1: " << avg1;
	//c = 0;

	for ( i = ( map->constEnd() - 1 ); i != ( map->constEnd() - 1 - a2end ); --i ) {
		avg2 += i.value();
		//qDebug() << "k:" << i.key() << "v: " << i.value() << "sum: " << avg2;
		//c += 1;
		//qDebug() << "c: " << c;
	}
	avg2 = avg2 / a2end;
	displayPg->avgval2->display ( ( int ) avg2 );
	//qDebug() << "avg2: " << avg2;

	//for ( i = ( map->constEnd() - 1 ); i != ( map->constEnd() - 1 - a3end ); --i ) {
		//avg3 += i.value();
		//qDebug() << "k:" << i.key() << "v: " << i.value() << "sum: " << avg2;
		//c += 1;
		//qDebug() << "c: " << c;
	//}
	
	//avg3 = avg3 / a3end;
	//displayPg->avgval3->display ( ( int ) avg3 );
	//qDebug() << "avg3: " << avg3;
}


void Display::sensorErr()
{
	qDebug() << "seems there was a problem downloading sensor data!";
	qDebug() << "error was: " << reply->errorString();

	urlPg->statusLabel->setText ( tr ( "http-reply error! - resuming in 5s.." ) );
	QTimer::singleShot ( 500, this, SLOT ( getSensorData() ) );

	//qDebug() << "stoping by reply error!";
	//tfetch->stop();
	//tshow->stop();
	//tavg->stop();
	//qDebug() << "timer stoped.";
	//curtimestamp = 0;
	//dlcounter = 0;
	//map->clear();
	//startButton->setText ( tr ( "Start" ) );
	//statsPg->statusLabel->setText ( tr ( "Stopped by http-reply error!" ) );

}

QString TimeConverter_s::convert ( double value )
{
	QDateTime dtime = QDateTime::fromMSecsSinceEpoch ( qint64 ( value ) * 1000 );
	return dtime.toString ( "hh:mm:ss" );
}

QString TimeConverter_m::convert ( double value )
{
	QDateTime dtime = QDateTime::fromMSecsSinceEpoch ( qint64 ( value ) * 1000 );
	return dtime.toString ( "hh:mm" );
}
