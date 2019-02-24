#ifndef OUTPUT_GUI_H_AHM0NQRP
#define OUTPUT_GUI_H_AHM0NQRP

#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QTime>

#include "output.h"
#include "types.h"


class QGridLayout;
class QMainWindow;
class QTimer;
class ChartOutputData;


class OutputGui: public Output
{
Q_OBJECT
public:
	explicit OutputGui(Collector *collector, const Settings &settings, QObject *parent = 0);
	virtual ~OutputGui();
	virtual void display();

private slots:
	void update();

private:
	qint64 m_counter;
	qint64 m_samplesDisplay;
	qint64 m_skip;
	bool m_firstSample;
	bool m_seriesChanged;
	QTime m_time;
	QTimer *m_timer;
	QMainWindow *m_mainWindow;
	QGridLayout *m_layout;
	QList<QSharedPointer<ChartOutputData>> m_charts;
}; /* -----  end of class OutputGui  ----- */


#endif /* end of include guard: OUTPUT_GUI_H_AHM0NQRP */
