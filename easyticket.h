#ifndef EASYTICKET_H
#define EASYTICKET_H

#include <QObject>
#include <QWidget>
#include "basededonnes.h"
#include "gestionnaireutilisateur.h"
#include "gestionnaireticket.h"

/**
 * @brief The easyticket class
 * Classe principale du model qui est aussi un QObjet pour pouvoir utiliser les
 * sigaux et les slots
 */
class easyticket: public QObject
{

    Q_OBJECT

public:

    explicit easyticket(QObject *parent = nullptr);

    bool identifierUtilisateur(const QString &identifiant, const QString &motDePasse) const;

    void setUtilisateurActif(Utilisateur& user);

    Utilisateur getUtilisateur(const QString& id) const;

    bool findUtilisateur(const QString& id) const;

    void creerUtilisateur(Utilisateur& user);

    Utilisateur& getUtilisateurActif();

    void inserTicket(const Ticket& t, const Utilisateur& user);

    bool findTicket(const QString& t) const;

    bool appartientAuTicket(const QString& user, const QString& t);

    void ajouterIntervenantAuTicket(const QString& user, const QString& t);

    QStringList initialiserIntervenant(const QString& t);

    void ajouterUnMessage(Message& msg);

    Ticket& getTicketActif();

    void setTicketActif(Ticket& t);

    void initialiserListeUtilisateur();

    int getNombreUtilisateurs() const;

    ~easyticket();


private:
    GestionnaireUtilisateur utilisateurs;
    Utilisateur utilisateurActif;
    GestionnaireTicket tickets;
    Basededonnes easyticketBDD;
    Ticket TicketActif;
};

#endif // EASYTICKET_H
