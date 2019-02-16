#include "output.h"
#include "output_console.h"
#include "output_file.h"


Output::Output(Collector *collector, QObject *parent):
	QObject(parent),
	m_collector(collector)
{
}

Output *Output::initialize(const QString &type, Collector *collector, const Settings &settings, QObject *parent)
{
	if (type == "console") {
		return new OutputConsole(collector, settings, parent);
	}
	else if (type == "file") {
		return new OutputFile(collector, settings, parent);
	}
	return nullptr;
}

Output::~Output()
{
}

