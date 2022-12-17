#ifndef TICKET_H
#define TICKET_H

#include <QDateTime>
#include <QString>

#include "gestionnaireutilisateur.h"
#include "message.h"
#include "gestionnairemessage.h"
#include <QDebug>
#include <QStandardItemModel>

class GestionnaireUtilisateur;
class Utilisateur;
class Message;
class GestionnaireMessage;

/**
 * @brief classe abstraite de base pour GestionMessage
 */
class Ticket
{
public:
    Ticket();

    Ticket(const QString& id, const QString& descr = "");

    void setIdentifiant(const QString& id);

    QString getIdentifiant() const;

    QString getDescription() const;

    void setDescription(const QString &descr);

    QString getDateCreation() const;

    void ajouterUnIntervenant(Utilisateur user);

    GestionnaireUtilisateur getIntervenant() const;

    void setDate(const QString& date);

    void ajouterUnMessage(Message& msg);


    int nbMessage() const;

    QStringList MessageToString();

    void clearMessage();

    void setRep();

    std::map<QString, double> getRep();

    GestionnaireMessage& getMessage();

    ~Ticket();

private:
    QString identifiant;
    QString dateCreation;
    QString description;
    GestionnaireUtilisateur* intervenant;
    GestionnaireMessage* message;
    std::map<QString, double> reponse;
};

#endif // TICKET_H
