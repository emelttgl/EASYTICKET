#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <QString>


#include "GestionnaireTicket.h"
class GestionnaireTicket;
class Ticket;

/**
 * @brief The Utilisateur class est une classe qui représente un utilisateur ou un compte.
 * défini par un identifiant, un mot de passe et une adresse mail
 */
class Utilisateur
{
public:

    Utilisateur();

    QString getIdentifiant() const;

    QString getMotDePasse() const;

    QString getMail() const;

    void setIdentifiant(const QString& id);

    void setMotDePasse(const QString& mdp);

    void setMail(const QString& m);

    void ajouterAMesTicket(Ticket& t);

    QStringList getMesTicketToString() const;

    GestionnaireTicket& getMesTicket() const;

    bool findTicket(const QString& grp) const;

    Ticket& getTicket(const QString& idTicket);

    ~Utilisateur();

private:

    /**
     * @brief identifiant de client
     */
    QString identifiant;

    /**
     * @brief motDePasse de compte
     */
    QString motDePasse;
    /**
     * @brief mail de client
     */
    QString mail;
    /**
     * @brief solde de client
     */
    GestionnaireTicket* mesTicket;
};


#endif // UTILISATEUR_H
