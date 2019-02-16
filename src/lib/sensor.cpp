#include <QFile>

#include "sensor.h"

#include <QDebug>


Sensor::Sensor(const Settings &settings, QObject *parent):
	QObject(parent),
	m_settings(settings)
{
}

Sensor::~Sensor()
{
}

Sensor *Sensor::initialize(const Settings &settings, QObject *parent)
{
	if (!settings.contains("type")) {
		return nullptr;
	}
	QString type = settings["type"].toString();
	if (type == "file") {
		return new SensorFile(settings, parent);
	}
	return nullptr;
}

/* -----  end of class Sensor  ----- */

SensorFile::SensorFile(const Settings &settings, QObject *parent):
	Sensor(settings, parent),
	m_file(nullptr)
{
	if (settings.contains("path")) {
		m_file = new QFile(settings["path"].toString(), this);
		if (!m_file->open(QIODevice::ReadOnly | QIODevice::Text)) {
			qWarning("File %s not readable", qUtf8Printable(settings["path"].toString()));
		}
	}
	else {
		qWarning("Parameter 'path' not defined");
	}
}

SensorFile::~SensorFile()
{
}

MeasurementResult SensorFile::measure()
{
	MeasurementResult result = MeasurementResult();
	if (m_file && m_file->isOpen()) { QByteArray line(m_file->readLine().trimmed()); m_file->seek(0);
		bool ok;
		int value = line.toInt(&ok);
		if (ok) {
			result["value"] = (qint64)value;
		}
	}
	return result;
}
