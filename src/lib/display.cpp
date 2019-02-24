#include "display.h"


DisplaySettings::DisplaySettings(const QString &name, const Settings &settings):
	m_settings(settings),
	m_name(name),
	m_scale(1)
{
	if (settings.contains("label")) {
		m_label = settings["label"].toString();
	}
	else {
		m_label = name;
	}
	if (settings.contains("sensors")) {
		m_sensors = settings["sensors"].toStringList();
	}
	if (settings.contains("scale")) {
		bool ok;
		m_scale = settings["scale"].toDouble(&ok);
		if (!ok) {
			m_scale = 1;
		}
	}
}

DisplaySettings::~DisplaySettings()
{
}

const Settings &DisplaySettings::settings() const
{
	return m_settings;
}

const QStringList &DisplaySettings::sensors() const
{
	return m_sensors;
}

const QString &DisplaySettings::label() const
{
	return m_label;
}

const QString &DisplaySettings::name() const
{
	return m_name;
}

double DisplaySettings::scale() const
{
	return m_scale;
}

