#ifndef SENSOR_H_L5ZKEOMC
#define SENSOR_H_L5ZKEOMC


#include <QObject>

#include "types.h"

class QFile;


class Sensor: public QObject
{
Q_OBJECT
protected:
	explicit Sensor(const Settings &settings, QObject *parent = 0);

public:
	virtual ~Sensor();
	virtual MeasurementResult measure() = 0;
	static Sensor *initialize(const Settings &settings, QObject *parent = 0);

protected:
	Settings m_settings;
}; /* -----  end of class Sensor  ----- */


class SensorFile: public Sensor
{
Q_OBJECT
public:
	explicit SensorFile(const Settings &settings, QObject *parent = 0);
	~SensorFile();
	MeasurementResult measure();

private:
	QFile *m_file;
}; /* -----  end of class SensorFile  ----- */


#endif /* end of include guard: SENSOR_H_L5ZKEOMC */
