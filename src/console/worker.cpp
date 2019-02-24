#include <QCoreApplication>
#include <QSettings>
#include <QTimer>

#include "../lib/collector.h"
#include "../lib/output.h"
#include "worker.h"


Worker::Worker(QObject *parent):
	QObject(parent),
	m_collector(new Collector(this)),
	m_timer(new QTimer(this))
{
	QSettings configuration;
	int interval = configuration.value("collector/interval", 1000).toInt();

	const QString outputPrefix = "output-";
	for (const QString &group: configuration.childGroups()) {
		if (group.startsWith(outputPrefix)) {
			const QString name = group.mid(outputPrefix.length());
			if (name == "gui") {
				continue;
			}
			Settings settings;
			configuration.beginGroup(group);
			for (const QString &key: configuration.childKeys()) {
				settings[key] = configuration.value(key);
			}
			configuration.endGroup();
			initializeOutput(name, settings);
		}
	}

	m_timer->setInterval(interval);
	connect(m_timer, &QTimer::timeout, this, &Worker::tick);
}

Worker::~Worker()
{
}

void Worker::setSamplesLimit(int samples)
{
	if (samples < 0) {
		samples = 0;
	}
	m_collector->setSamplesLimit((quint64)samples);
}

void Worker::initializeOutput(const QString &name, const Settings &settings)
{
	Output *output = Output::initialize(name, m_collector, settings, this);
	if (!output) {
		qWarning("Output %s not initialized", qUtf8Printable(name));
	}
	m_outputs.append({name, output});
}

void Worker::start()
{
	m_timer->start();
}

void Worker::stop()
{
	m_timer->stop();
}

void Worker::tick()
{
	m_collector->tick();
	if (m_collector->sampleFinished()) {
		for (auto const &output: m_outputs) {
			output.second->display();
		}
	}
	if (m_collector->finished()) {
		QTimer::singleShot(0, qApp, &QCoreApplication::quit);
	}
}

