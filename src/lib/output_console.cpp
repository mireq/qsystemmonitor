#include <cstdio>

#include "collector.h"
#include "display.h"
#include "output_console.h"


OutputConsole::OutputConsole(Collector *collector, const Settings &settings, QObject *parent):
	Output(collector, parent),
	m_counter(0),
	m_skip(1),
	m_stdout(stdout)
{
	if (settings.contains("skip")) {
		m_skip = settings["skip"].toInt();
	}
}

OutputConsole::~OutputConsole()
{
}

void OutputConsole::display()
{
	if (m_counter % m_skip != 0) {
		m_counter++;
		return;
	}
	else {
		m_counter++;
	}
	const CollectedData &data = m_collector->collectedData();
	for (auto const &display: m_collector->displays()) {
		m_stdout << display.label() << "\n";
		for (const QString &sensor: display.sensors()) {
			double value = data[sensor.section('.', 0, 0)][sensor.section('.', 1, 1)] / m_collector->average() * display.scale();
			m_stdout << sensor << ": " << value << "\t";
		}
		m_stdout << "\n\n";
		m_stdout.flush();
	}
}
