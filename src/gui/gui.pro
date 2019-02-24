QT += gui charts widgets
TEMPLATE = app
DEFINES += "OUTPUT_GUI=1"
TARGET = ../qsystemmonitor-gui
SOURCES = main.cpp\
	worker.cpp \
	../lib/collector.cpp \
	../lib/display.cpp \
	../lib/output.cpp \
	../lib/output_console.cpp \
	../lib/output_file.cpp \
	../lib/output_gui.cpp \
	../lib/sensor.cpp
HEADERS = worker.h \
	../lib/collector.h \
	../lib/display.h \
	../lib/output.h \
	../lib/output_console.h \
	../lib/output_file.h \
	../lib/output_gui.h \
	../lib/sensor.h
