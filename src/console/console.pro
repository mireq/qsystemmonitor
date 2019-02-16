QT += core
QT -= gui
TEMPLATE = app
TARGET = ../qsystemmonitor-console
SOURCES = main.cpp \
	worker.cpp \
	../lib/collector.cpp \
	../lib/display.cpp \
	../lib/output.cpp \
	../lib/output_console.cpp \
	../lib/output_file.cpp \
	../lib/sensor.cpp
HEADERS = worker.h \
	../lib/collector.h \
	../lib/display.h \
	../lib/output.h \
	../lib/output_console.h \
	../lib/output_file.h \
	../lib/sensor.h
