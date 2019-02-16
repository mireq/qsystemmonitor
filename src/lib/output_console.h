#ifndef OUTPUT_CONSOLE_H_IGDWFZXR
#define OUTPUT_CONSOLE_H_IGDWFZXR


#include <QObject>
#include <QTextStream>

#include "output.h"
#include "types.h"


class OutputConsole: public Output
{
Q_OBJECT
public:
	explicit OutputConsole(Collector *collector, const Settings &settings, QObject *parent = 0);
	virtual ~OutputConsole();
	virtual void display();

private:
	qint64 m_counter;
	qint64 m_skip;
	QTextStream m_stdout;
}; /* -----  end of class OutputConsole  ----- */

#endif /* end of include guard: OUTPUT_CONSOLE_H_IGDWFZXR */
