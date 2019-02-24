#ifndef DISPLAY_H_MMNPTFYR
#define DISPLAY_H_MMNPTFYR


#include <QStringList>

#include "types.h"


class DisplaySettings
{
public:
	DisplaySettings();
	explicit DisplaySettings(const QString &name, const Settings &settings);
	~DisplaySettings();

	const Settings &settings() const;
	const QStringList &sensors() const;
	const QString &label() const;
	const QString &name() const;
	double scale() const;

private:
	Settings m_settings;
	QStringList m_sensors;
	QString m_label;
	QString m_name;
	double m_scale;
}; /* -----  end of class DisplaySettings  ----- */


#endif /* end of include guard: DISPLAY_H_MMNPTFYR */
