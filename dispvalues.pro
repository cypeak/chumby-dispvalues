TEMPLATE = app
SOURCES += src/main.cpp \
 src/dispval.cpp \
 src/json/json.cpp \
 src/plotter/plotsettings.cpp \
 src/plotter/plotter.cpp \
 src/plotter/qpointd.cpp \
 src/spritevis/tacho.cpp \
 src/spritevis/zeiger.cpp \
 src/spritevis/qcustomgraphview.cpp
HEADERS += src/dispval.h \
 src/json/json.h \
 src/plotter/plotsettings.h \
 src/plotter/plotter.h \
 src/plotter/converter.h \
 src/plotter/qpointd.h \
 src/spritevis/tacho.h \
 src/spritevis/zeiger.h \
 src/spritevis/qcustomgraphview.h
CONFIG += warn_on debug
RESOURCES += src/spritevis/mice.qrc
