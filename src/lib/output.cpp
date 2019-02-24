#include "output.h"
#include "output_console.h"
#include "output_file.h"
#ifdef OUTPUT_GUI
	#include "output_gui.h"
#endif


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
#ifdef OUTPUT_GUI
	else if (type == "gui") {
		return new OutputGui(collector, settings, parent);
	}
#endif
	return nullptr;
}

Output::~Output()
{
}

