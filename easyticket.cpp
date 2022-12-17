#include "easyticket.h"
#include <iostream>

/**
 * @brief easyticket constructeur par défaut
 * @param parent
 */
easyticket::easyticket(QObject *parent): QObject(parent){
    easyticketBDD.createDataBase();

    easyticketBDD.initialiserListeUtilisateur(utilisateurs);
}

/**
 * @brief initialiserListeUtilisateur permet d'initialiser les utilisateurs
 */
void easyticket::initialiserListeUtilisateur() {
    easyticketBDD.initialiserListeUtilisateur(utilisateurs);
}

/**
 * @brief identifierUtilisateur retourne vrai si l'utilisateur existe
 * @param identifiant
 * @param motDePasse
 * @return
 */
bool easyticket::identifierUtilisateur(const QString &identifiant, const QString &motDePasse) const {
    return utilisateurs.identifierUtilisateur(identifiant, motDePasse);
}

/**
 * @brief setUtilisateurActif Permet d'affecter au système l'utilisateur actif
 * @param user
 */
void easyticket::setUtilisateurActif(Utilisateur& user) {
    utilisateurActif = user;
    easyticketBDD.initialiserTicketUtilisateur(user.getMesTicket(), user.getIdentifiant());
}

/**
 * @brief getUtilisateur retourne un utilisateur avec l'id spécifique
 * @param id
 * @return
 */
Utilisateur easyticket::getUtilisateur(const QString& id) const {
    return utilisateurs.getUtilisateur(id);
}

/**
 * @brief findUtilisateur retourne vrai si l'utilisateur existe faux sinon
 * @param id
 * @return
 */
bool easyticket::findUtilisateur(const QString& id) const {
    return utilisateurs.findUtilisateur(id);
}

/**
 * @brief creerUtilisateur permet d'ajouter un utilisateur à la base de donnée
 * @param user
 */
void easyticket::creerUtilisateur(Utilisateur& user) {
    easyticketBDD.insererUtilisateur(user);
    utilisateurs.ajouterUtilisateur(user);
}

/**
 * @brief getUtilisateurActif retourne la référence de l'utiisateur actif
 * @return
 */
Utilisateur& easyticket::getUtilisateurActif() {
    return utilisateurActif;
}

/**
 * @brief inserTicket permet d'inserer un ticket dans la base de donnée
 * @param t
 * @param user
 */
void easyticket::inserTicket(const Ticket& t, const Utilisateur& user) {
    easyticketBDD.insererunTicket(t, user);
}

/**
 * @brief findTicket retourne vrai si t fait partie des tickets d'utilisateurActif
 * @param t
 * @return
 */
bool easyticket::findTicket(const QString& t) const {
    return utilisateurActif.findTicket(t);
}

/**
 * @brief appartientAuTicket retourne vrai si user appartient à t
 * @param user
 * @param t
 * @return
 */
bool easyticket::appartientAuTicket(const QString& user, const QString& t) {
    return easyticketBDD.appartientAIngenieur(user, t);
}

/**
 * @brief
 * @param user
 * @param t
 */
void easyticket::ajouterIntervenantAuTicket(const QString& user, const QString& grp) {
    easyticketBDD.ajouterIntervenantAuTicket(user, grp);
}

/**
 * @brief initialiserIntervenant permet d'initialiser les intervenants au t
 * pour l'afficher
 * @param t
 */
QStringList easyticket::initialiserIntervenant(const QString& t) {
    return easyticketBDD.initialiserIntervenant(t);
}

/**
 * @brief ajouterUnMessage permet d'ajouter un message au ticket
 * @param dep
 */
void easyticket::ajouterUnMessage(Message& msg) {
    TicketActif.ajouterUnMessage(msg);
    easyticketBDD.insererUnMessage(msg, TicketActif);
}

/**
 * @brief getTicketActif retourne le ticket actif
 * @return
 */
Ticket& easyticket::getTicketActif() {
    return TicketActif;
}

/**
 * @brief setTicketActif positionne le ticket actif
 * @param t
 */
void easyticket::setTicketActif(Ticket& t) {
    TicketActif = t;
    easyticketBDD.initialiserMessageTicket(TicketActif);
}


/**
 * @brief getNombreUtilisateurs retourne le nombre d'utilisateur
 * @return
 */
int easyticket::getNombreUtilisateurs() const {
    return utilisateurs.getNombreUtilisateur();
}

easyticket::~easyticket() {
}
