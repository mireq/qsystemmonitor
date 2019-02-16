#ifndef OUTPUT_FILE_H_XFVU9Y87
#define OUTPUT_FILE_H_XFVU9Y87

#include <QObject>
#include <QSharedPointer>
#include <QTime>

#include "output.h"

class QFile;
class QTextStream;


class OutputFile: public Output
{
Q_OBJECT
public:
	explicit OutputFile(Collector *collector, const Settings &settings, QObject *parent = 0);
	virtual ~OutputFile();
	virtual void display();

private:
	QSharedPointer<QFile> m_file;
	QSharedPointer<QTextStream> m_output;
	QTime m_time;
	bool m_firstLine;
}; /* -----  end of class OutputFile  ----- */


#endif /* end of include guard: OUTPUT_FILE_H_XFVU9Y87 */
