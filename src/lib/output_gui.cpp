#include <QGridLayout>
#include <QMainWindow>
#include <QPointF>
#include <QTimer>
#include <QVector>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include "collector.h"
#include "output_gui.h"


QT_CHARTS_USE_NAMESPACE


class ChartOutputData {
public:
	ChartOutputData():
		chart(nullptr),
		view(nullptr)
	{
	}

	DisplaySettings display;
	QChart *chart;
	QChartView *view;
	QAbstractAxis *xAxis;
	QAbstractAxis *yAxis;
	QVector<QXYSeries *> series;
	QVector<QVector<QPointF>> buffers;
};


OutputGui::OutputGui(Collector *collector, const Settings &settings, QObject *parent):
	Output(collector, parent),
	m_counter(0),
	m_samplesDisplay(1000),
	m_skip(1),
	m_firstSample(true),
	m_seriesChanged(false),
	m_timer(new QTimer(this)),
	m_mainWindow(new QMainWindow()),
	m_layout(new QGridLayout())
{
	if (settings.contains("skip")) {
		m_skip = settings["skip"].toInt();
	}

	connect(m_timer, &QTimer::timeout, this, &OutputGui::update);
	m_timer->setInterval(100);
	m_timer->start();

	m_layout->setSpacing(0);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_mainWindow->layout()->setSpacing(0);
	QWidget *widget = new QWidget();
	widget->setLayout(m_layout);
	m_mainWindow->resize(800, 600);
	m_mainWindow->setCentralWidget(widget);
	m_mainWindow->show();

	int row = 0;
	for (auto const &display: m_collector->displays()) {
		QSharedPointer<ChartOutputData> output = QSharedPointer<ChartOutputData>(new ChartOutputData());
		output->display = display;
		output->chart = new QChart();
		output->view = new QChartView(output->chart);
		output->chart->legend()->hide();
		output->xAxis = new QValueAxis;
		output->chart->addAxis(output->xAxis, Qt::AlignBottom);
		output->yAxis = new QValueAxis;
		output->chart->addAxis(output->yAxis, Qt::AlignLeft);
		output->series.reserve(display.sensors().count());
		output->buffers.resize(display.sensors().count());
		for (const QString &sensor: display.sensors()) {
			QXYSeries *series = new QLineSeries;
			series->setUseOpenGL(true);
			output->chart->addSeries(series);
			series->attachAxis(output->xAxis);
			series->attachAxis(output->yAxis);
			series->setName(sensor);
			series->setPen(QPen(QBrush(QColor("red")), 1.0));
			output->series.append(series);
		}
		for (int i = 0; i < display.sensors().count(); ++i) {
			output->buffers[i].reserve(m_samplesDisplay);
		}
		output->xAxis->setRange(-double(m_samplesDisplay) * m_collector->timePerSample() / 1000, 0);
		output->yAxis->setRange(0, 100);
		m_layout->addWidget(output->view, row, 0);
		m_layout->setRowStretch(row, 1);
		m_charts.append(output);
		row++;
	}
}

OutputGui::~OutputGui()
{
	m_mainWindow->deleteLater();
}

void OutputGui::display()
{
	const CollectedData &data = m_collector->collectedData();
	if (m_firstSample) {
		m_time.start();
		m_firstSample = false;
	}
	double time = double(m_time.elapsed()) / 1000;
	for (auto &output: m_charts) {
		int series = 0;
		for (const QString &sensor: output->display.sensors()) {
			double value = data[sensor.section('.', 0, 0)][sensor.section('.', 1, 1)] / m_collector->average() * output->display.scale();
			if (output->buffers[series].count() >= m_samplesDisplay) {
				output->buffers[series].removeFirst();
			}
			output->buffers[series] << QPointF(time, value);
			series++;
		}
	}
	m_seriesChanged = true;
}

void OutputGui::update()
{
	double time = 0;
	for (auto &output: m_charts) {
		for (int series = 0; series < output->display.sensors().count(); ++series) {
			time = qMax(time, output->buffers[series].last().x());
			output->series[series]->replace(output->buffers[series]);
		}
		output->xAxis->setRange(time-double(m_samplesDisplay) * m_collector->timePerSample() / 1000, time);
	}
}

