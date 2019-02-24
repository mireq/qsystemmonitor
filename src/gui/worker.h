#ifndef WORKER_H_SBXO1G3P
#define WORKER_H_SBXO1G3P


#include <QList>
#include <QObject>
#include <QPair>

#include "../lib/types.h"

class Collector;
class Output;
class QTimer;


class Worker: public QObject
{
Q_OBJECT
public:
	explicit Worker(QObject *parent = 0);
	virtual ~Worker();

	void setSamplesLimit(int samples);
	void initializeOutput(const QString &name, const Settings &settings);

	void start();
	void stop();

private slots:
	void tick();

private:
	Collector *m_collector;
	QTimer *m_timer;
	QList<QPair<QString, Output *>> m_outputs;
}; /* -----  end of class Worker  ----- */


#endif /* end of include guard: WORKER_H_SBXO1G3P */
