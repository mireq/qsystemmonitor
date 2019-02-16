#ifndef COLLECTOR_H_KE4HGSCY
#define COLLECTOR_H_KE4HGSCY


#include <QList>
#include <QMap>
#include <QObject>
#include <QPair>

#include "../lib/display.h"
#include "types.h"


class Sensor;


class Collector: public QObject
{
Q_OBJECT
public:
	explicit Collector(QObject *parent = 0);
	virtual ~Collector();

	quint64 samplesLimit() const;
	void setSamplesLimit(quint64 limit);

	void tick();
	quint64 sampleNumber() const;
	bool sampleFinished() const;
	bool finished() const;
	quint64 average() const;
	const QList<DisplaySettings> &displays() const;
	const CollectedData &collectedData() const;

private:
	void initializeSensor(const QString &name, const Settings &settings);
	void initializeDisplay(const QString &name, const Settings &settings);

private:
	quint64 m_average;
	quint64 m_counter;
	quint64 m_samplesLimit;

	QList<QPair<QString, Sensor *>> m_sensors;
	QList<DisplaySettings> m_displays;
	CollectedData m_collected;
}; /* -----  end of class Collector  ----- */


#endif /* end of include guard: COLLECTOR_H_KE4HGSCY */
