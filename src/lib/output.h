#ifndef OUTPUT_H_EIKW9CLA
#define OUTPUT_H_EIKW9CLA

#include <QObject>

#include "types.h"


class Collector;


class Output: public QObject
{
Q_OBJECT
protected:
	explicit Output(Collector *collector, QObject *parent = 0);

public:
	static Output *initialize(const QString &type, Collector *collector, const Settings &settings, QObject *parent = 0);
	virtual ~Output();
	virtual void display() = 0;

protected:
	Collector *m_collector;
}; /* -----  end of class Output  ----- */

#endif /* end of include guard: OUTPUT_H_EIKW9CLA */
