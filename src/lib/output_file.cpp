#include <QFile>
#include <QTextStream>
#include <QTime>

#include "collector.h"
#include "output_file.h"


OutputFile::OutputFile(Collector *collector, const Settings &settings, QObject *parent):
	Output(collector, parent),
	m_firstLine(true)
{
	if (settings.contains("path")) {
		m_file = QSharedPointer<QFile>(new QFile(settings["path"].toString()));
		if (m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
			m_output = QSharedPointer<QTextStream>(new QTextStream(m_file.data()));
		}
	}
}

OutputFile::~OutputFile()
{
}

void OutputFile::display()
{
	(*m_output) << forcepoint;
	const CollectedData &data = m_collector->collectedData();
	if (m_firstLine) {
		m_time.start();
		int col = 0;
		for (auto const &display: m_collector->displays()) {
			(*m_output) << "time";
			for (const QString &sensor: display.sensors()) {
				(*m_output) << ",\"" << display.name() << "." << sensor << "\"";
				col++;
			}
			m_firstLine = false;
		}
		(*m_output) << "\n";
	}
	int col = 0;
	(*m_output) << double(m_time.elapsed()) / 1000;
	for (auto const &display: m_collector->displays()) {
		for (const QString &sensor: display.sensors()) {
			double value = data[sensor.section('.', 0, 0)][sensor.section('.', 1, 1)] / m_collector->average() * display.scale();
			(*m_output) << "," << value;
			col++;
		}
	}
	(*m_output) << "\n";
	m_output->flush();
}

