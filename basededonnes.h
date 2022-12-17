#ifndef BASEDEDONNES_H
#define BASEDEDONNES_H

#include <QObject>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QSqlError>
#include <map>

#include "utilisateur.h"
#include "gestionnaireutilisateur.h"

#define DB_PATH "../projetcpoa/EasyTicketDataBase.db"

class Basededonnes : public QObject
{

    Q_OBJECT

public:
    explicit Basededonnes(const QString& path = DB_PATH);

    void createDataBase();

    void insererUtilisateur(const Utilisateur& user) const;

    void initialiserListeUtilisateur(GestionnaireUtilisateur& users);

    void insererunTicket(const Ticket& t, const Utilisateur& user);

    void initialiserTicketUtilisateur(GestionnaireTicket& t, const QString& idUser);

    bool appartientAIngenieur(const QString& user, const QString& t);

    void ajouterIntervenantAuTicket(const QString& user, const QString& t);

    QStringList initialiserIntervenant(const QString& t);

    void insererUnMessage(const Message& msg, const Ticket& t);

    void initialiserMessageTicket(Ticket& t);

    void updateHistorique(const QString& t, const QString& action);


private:
    QSqlDatabase easyTicketBase;
    bool creerDataBase;
};

#endif // BASEDEDOONES_H
