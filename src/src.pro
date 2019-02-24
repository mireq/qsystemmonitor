TEMPLATE = subdirs
SUBDIRS = console
qtHaveModule(charts):qtHaveModule(widgets):
	SUBDIRS += gui
