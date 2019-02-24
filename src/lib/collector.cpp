#include <QSettings>

#include "collector.h"
#include "sensor.h"


Collector::Collector(QObject *parent):
	QObject(parent),
	m_average(1),
	m_counter(0),
	m_samplesLimit(0),
	m_timePerSample(1000)
{
	QSettings configuration;
	m_average = configuration.value("collector/average", 1).toULongLong();
	int interval = configuration.value("collector/interval", 1000).toInt();
	m_timePerSample = interval * m_average;
	const QString sensorPrefix = "sensor-";
	for (const QString &group: configuration.childGroups()) {
		if (group.startsWith(sensorPrefix)) {
			Settings settings;
			configuration.beginGroup(group);
			for (const QString &key: configuration.childKeys()) {
				settings[key] = configuration.value(key);
			}
			configuration.endGroup();
			initializeSensor(group.mid(sensorPrefix.length()), settings);
		}
	}

	const QString displayPrefix = "display-";
	for (const QString &group: configuration.childGroups()) {
		if (group.startsWith(displayPrefix)) {
			Settings settings;
			configuration.beginGroup(group);
			for (const QString &key: configuration.childKeys()) {
				settings[key] = configuration.value(key);
			}
			configuration.endGroup();
			initializeDisplay(group.mid(displayPrefix.length()), settings);
		}
	}
}

Collector::~Collector()
{
}

quint64 Collector::samplesLimit() const
{
	return m_samplesLimit;
}

quint64 Collector::timePerSample() const
{
	return m_timePerSample;
}

void Collector::setSamplesLimit(quint64 limit)
{
	m_samplesLimit = limit;
}

void Collector::tick()
{
	if (m_counter % m_average == 0) {
		m_collected = CollectedData();
	}
	for (QPair<QString, Sensor *> &sensor: m_sensors) {
		auto const data = sensor.second->measure();
		for (auto i = data.constBegin(); i != data.constEnd(); ++i) {
			m_collected[sensor.first][i.key()] += i.value();
		}
	}
	m_counter++;
}

quint64 Collector::sampleNumber() const
{
	return m_counter / m_average;
}

bool Collector::sampleFinished() const
{
	return (m_counter % m_average) == 0;
}

bool Collector::finished() const
{
	if (m_samplesLimit == 0) {
		return false;
	}
	return sampleNumber() >= m_samplesLimit;
}

quint64 Collector::average() const
{
	return m_average;
}

const QList<DisplaySettings> &Collector::displays() const
{
	return m_displays;
}

const CollectedData &Collector::collectedData() const
{
	return m_collected;
}

void Collector::initializeSensor(const QString &name, const Settings &settings)
{
	Sensor *sensor = Sensor::initialize(settings, this);
	if (!sensor) {
		qWarning("Sensor %s not initialized", qUtf8Printable(name));
	}
	m_sensors.append({name, sensor});
}

void Collector::initializeDisplay(const QString &name, const Settings &settings)
{
	m_displays.append(DisplaySettings(name, settings));
}

