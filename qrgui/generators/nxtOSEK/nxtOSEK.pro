######################################################################
# Automatically generated by qmake (2.01a) ?? ???? 11 16:29:32 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += nxtOSEKRobotGenerator.h \
           ../../kernel/ids.h \
           ../../../qrrepo/repoApi.h \
           ../../kernel/roles.h \
           ../../../qrrepo/private/client.h \
           ../../kernel/definitions.h \
           ../../../qrrepo/private/classes/object.h \
           ../../../qrrepo/private/qrRepoGlobal.h \
           ../../../qrrepo/private/serializer.h \
           ../../../qrrepo/repoControlInterface.h \
           ../../../qrrepo/commonRepoApi.h \
           ../../../qrrepo/graphicalRepoApi.h \
           ../../../qrrepo/logicalRepoApi.h
SOURCES += nxtOSEKRobotGenerator.cpp \
           main.cpp \
           ../../kernel/ids.cpp \
           ../../../qrrepo/private/client.cpp \
           ../../../qrrepo/private/classes/object.cpp \
           ../../../qrrepo/private/serializer.cpp

LIBS += -L../../../qrgui -lqrrepo

QMAKE_LFLAGS="-Wl,-O1,-rpath,$(PWD)/../../../qrgui"

