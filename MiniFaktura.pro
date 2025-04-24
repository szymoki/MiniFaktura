QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contractorform.cpp \
    contractorlistview.cpp \
    contractorrepository.cpp \
    databasemanager.cpp \
    idatasource.cpp \
    invoiceform.cpp \
    invoicerepository.cpp \
    invoicetopdfgenerator.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsmanager.cpp \
    settingsview.cpp \
    sqlitedatasource.cpp \
    emailsender.cpp

HEADERS += \
    contractorform.h \
    contractorlistview.h \
    contractorrepository.h \
    databasemanager.h \
    icontractorrepository.h \
    idatasource.h \
    invoiceform.h \
    invoicerepository.h \
    invoicetopdfgenerator.h \
    mainwindow.h \
    settingsmanager.h \
    settingsview.h \
    sqlitedatasource.h \
    emailsender.h

FORMS += \
    contractorform.ui \
    contractorlistview.ui \
    invoiceform.ui \
    mainwindow.ui \
    settingsview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    invoice.html

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/smtpclient/src/release/ -lSmtpMime
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/smtpclient/src/debug/ -lSmtpMime
else:unix: LIBS += -L$$PWD/smtpclient/src/ -lSmtpMime

INCLUDEPATH += $$PWD/smtpclient/src
DEPENDPATH += $$PWD/smtpclient/src
