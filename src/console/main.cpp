#include <QCommandLineParser>
#include <QCoreApplication>
#include <QSettings>
#include <cstdio>

#include "worker.h"


int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QCoreApplication::setOrganizationName("LinuxOS");
	QCoreApplication::setOrganizationDomain("linuxos.sk");
	QCoreApplication::setApplicationName("QSystemMonitor");
	QSettings::setDefaultFormat(QSettings::IniFormat);

	QCommandLineParser parser;
	parser.setApplicationDescription("QSystemMonitor");
	parser.addHelpOption();
	parser.addOption(QCommandLineOption("s", "Number of samples before quit", "samples"));
	parser.process(app);

	Worker worker;
	const QString samples = parser.value("s");
	if (!samples.isEmpty()) {
		bool ok;
		int samplesValue = samples.toInt(&ok);
		if (ok) {
			worker.setSamplesLimit(samplesValue);
		}
		else {
			fputs("Wrong value for samples", stderr);
			return -1;
		}
	}

	{
		fputs("Starting with configuration file ", stdout);
		QSettings settings;
		fputs(qPrintable(settings.fileName()), stdout);
		fputs("\n", stdout);
		fflush(stdout);
	}

	worker.start();

	return app.exec();
}
