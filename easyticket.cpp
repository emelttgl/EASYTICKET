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
 * @brief inserGroupe permet d'inserer un groupe dans la base de donnée
 * @param grp
 * @param user
 */
void easyticket::inserTicket(const Ticket& t, const Utilisateur& user) {
    easyticketBDD.insererunTicket(t, user);
}

/**
 * @brief findGroupe retourne vrai si grp fait partie des groupes d'utilisateurActif
 * @param grp
 * @return
 */
bool easyticket::findTicket(const QString& t) const {
    return utilisateurActif.findTicket(t);
}

/**
 * @brief appartientAuGroupe retourne vrai si user appartient à grp
 * @param user
 * @param grp
 * @return
 */
bool easyticket::appartientAuTicket(const QString& user, const QString& t) {
    return easyticketBDD.appartientAIngenieur(user, t);
}

/**
 * @brief ajouterParticipantAuGroupe ajoute le participant "user" au groupe "grp";
 * @param user
 * @param grp
 */
void easyticket::ajouterIntervenantAuTicket(const QString& user, const QString& grp) {
    easyticketBDD.ajouterIntervenantAuTicket(user, grp);
}

/**
 * @brief initialiserParticipants permet d'initialiser les participants au groupe grp
 * pour l'afficher
 * @param grp
 */
QStringList easyticket::initialiserIntervenant(const QString& t) {
    return easyticketBDD.initialiserIntervenant(t);
}

/**
 * @brief ajouterUneDepense permet d'ajouter une dépense au groupe actif
 * @param dep
 */
void easyticket::ajouterUnMessage(Message& msg) {
    TicketActif.ajouterUnMessage(msg);
    easyticketBDD.insererUnMessage(msg, TicketActif);
}

/**
 * @brief getGroupeActif retourne le groupe actif
 * @return
 */
Ticket& easyticket::getTicketActif() {
    return TicketActif;
}

/**
 * @brief setGroupeActif positionne le groupe actif
 * @param grp
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
