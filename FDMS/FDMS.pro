QT += sql
TARGET = FDMS
TEMPLATE = app
UI_DIR = ui/

INCLUDEPATH += headers

SOURCES += sources/main.cpp \
    sources/wndMain.cpp \
    sources/managers/PluginManager.cpp \
    sources/managers/SettingManager.cpp \
    sources/wndSetup.cpp \
    sources/managers/DatabaseManager.cpp \
    sources/plugins/PluginInfo.cpp \
    sources/plugins/DependencyList.cpp
	
HEADERS += \
    headers/MDIWindow.h \
    headers/plugins/MDIWindowPlugin.h \
    headers/plugins/DatabasePlugin.h \
    headers/managers/PluginManager.h \
    headers/managers/SettingManager.h \
    headers/wndSetup.h \
    headers/managers/DatabaseManager.h \
    headers/wndMain.h \
    headers/plugins/BasePlugin.h \
    headers/plugins/PluginInfo.h \
    headers/plugins/DependencyList.h

FORMS += \
    forms/wndMain.ui

RESOURCES += \
    resources/resources.qrc