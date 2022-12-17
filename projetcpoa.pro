QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    FenetrePrincipale.cpp \
    basededonnes.cpp \
    easyticket.cpp \
    gestionnairemessage.cpp \
    gestionnaireticket.cpp \
    gestionnaireutilisateur.cpp \
    listeticket.cpp \
    main.cpp \
    message.cpp \
    pageaccueil.cpp \
    pagecreationcompte.cpp \
    pagecreationticket.cpp \
    pagegestionmessage.cpp \
    pageprincipale.cpp \
    ticket.cpp \
    utilisateur.cpp

HEADERS += \
    FenetrePrincipale.h \
    basededonnes.h \
    easyticket.h \
    gestionnairemessage.h \
    gestionnaireticket.h \
    gestionnaireutilisateur.h \
    listeticket.h \
    message.h \
    pageaccueil.h \
    pagecreationcompte.h \
    pagecreationticket.h \
    pagegestionmessage.h \
    pageprincipale.h \
    ticket.h \
    utilisateur.h

FORMS += \
    FenetrePrincipale.ui \
    ListeTicket.ui \
    PageAccueil.ui \
    PageCreationCompte.ui \
    PageCreationTicket.ui \
    PagePrincipale.ui \
    pagegestionmessage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
