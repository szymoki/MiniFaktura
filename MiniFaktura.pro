QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SMTP_LIBRARY_LOCATION = $$PWD/../../../build/SMTPEmail-Desktop-Release
SOURCES += \
    contractorform.cpp \
    contractorlistview.cpp \
    contractorrepository.cpp \
    databasemanager.cpp \
    emailsender.cpp \
    idatasource.cpp \
    invoiceform.cpp \
    invoicerepository.cpp \
    invoicetopdfgenerator.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsmanager.cpp \
    settingsview.cpp \
    sqlitedatasource.cpp

HEADERS += \
    contractorform.h \
    contractorlistview.h \
    contractorrepository.h \
    databasemanager.h \
    emailsender.h \
    icontractorrepository.h \
    idatasource.h \
    invoiceform.h \
    invoicerepository.h \
    invoicetopdfgenerator.h \
    mainwindow.h \
    settingsmanager.h \
    settingsview.h \
    sqlitedatasource.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/release/ -lSMTPMime2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lSMTPMime2
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSmtpMime

RESOURCES += \
    resources.qrc
INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
DEPENDPATH += $$SMTP_LIBRARY_LOCATION
