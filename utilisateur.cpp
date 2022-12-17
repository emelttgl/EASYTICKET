#include "utilisateur.h"

/**
 * @brief Utilisateur constructeur
 */
Utilisateur::Utilisateur(): mesTicket(new GestionnaireTicket){
}


/**
 * @brief setIdentifiant modifie l'identifiant
 * @param id
 */
void Utilisateur::setIdentifiant(const QString& id) {
    identifiant = id;
}

/**
 * @brief setMotDePasse modifier le mdp
 * @param mdp
 */
void Utilisateur::setMotDePasse(const QString& mdp) {
    motDePasse = mdp;
}

/**
 * @brief setMail modifier le mail
 * @param m
 */
void Utilisateur::setMail(const QString& m) {
    mail = m;
}

/**
 * @brief getIdentifiant
 * @return l'identifiant de l'utilisateur
 */
QString Utilisateur::getIdentifiant() const{
    return identifiant;
}

/**
 * @brief getMotDePasse
 * @return  le mot de passe de l'utilisateur
 */
QString Utilisateur::getMotDePasse() const {
    return motDePasse;
}

/**
 * @brief getMail
 * @return le mail de l'utilisateur
 */
QString Utilisateur::getMail() const {
    return mail;
}

/**
 * @brief ajouterAMesTicket permet d'ajouter un Ticket
 * @param t
 */
void Utilisateur::ajouterAMesTicket(Ticket& t) {
    mesTicket->ajouterTicket(t);
}

/**
 * @brief getMesTicketToString retourne la liste des Ticket sous la
 * forme d'une liste de QString
 * @return
 */
QStringList Utilisateur::getMesTicketToString() const {
    QStringList qsl;
    for (int i = 0; i < mesTicket->size(); i++) {
        qsl << mesTicket->getTicket(i).getIdentifiant();
    }

    return qsl;
}

/**
 * @brief getMesTicket retourne une référence sur mesTicket
 * @return
 */
GestionnaireTicket& Utilisateur::getMesTicket() const {
    return *mesTicket;
}

/**
 * @brief findTicket retourne vrai si t fait partie des Ticket
 * @param t
 * @return
 */
bool Utilisateur::findTicket(const QString& t) const {
    return mesTicket->findTicket(t);
}

/**
 * @brief getTicket retourne un Ticket
 * @param idTicket
 * @return
 */
Ticket& Utilisateur::getTicket(const QString& idTicket) {
    return mesTicket->getTicket(idTicket);
}

Utilisateur::~Utilisateur() {
    //delete mesTicket;
}
