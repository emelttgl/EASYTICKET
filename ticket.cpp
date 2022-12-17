#include "ticket.h"

/**
 * @brief Ticket constructeur
 * @param id nom / identifiant du Ticket
 * @param date date de création du Ticket
 * @param descr petite déscription du Ticket
 */
Ticket::Ticket(const QString& id, const QString& descr):
    identifiant(id),
    description(descr)
{
    QDateTime d;
    dateCreation = d.currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
}

Ticket::Ticket(): intervenant(new GestionnaireUtilisateur),
    message(new GestionnaireMessage) {
}

/**
 * @brief getIdentifiant retourne l'identifiant / nom du Ticket
 * @return
 */
QString Ticket::getIdentifiant() const {
    return identifiant;
}

void Ticket::setIdentifiant(const QString &id){
    identifiant = id;
}

/**
 * @brief getDescription retourne la descrption du Ticket
 * @return
 */
QString Ticket::getDescription() const {
    return description;
}

/**
 * @brief setDescription permet de donné une déscription pour le Ticket
 * @param descr
 */
void Ticket::setDescription(const QString &descr) {
    description = descr;
}

/**
 * @brief getDateCreation retourne la date de création du Ticket
 * @return
 */
QString Ticket::getDateCreation() const {
    return dateCreation;
}

/**
 * @brief ajouterUnIntervenant
 * @param user
 */
void Ticket::ajouterUnIntervenant(Utilisateur user) {
    intervenant->ajouterUtilisateur(user);
}

/**
 * @brief getIntervenant retourne les intervenants
 * @return
 */
GestionnaireUtilisateur Ticket::getIntervenant() const {
    return *intervenant;
}


/**
 * @brief getMessage retourne le gestionnaire de Ticket
 * @return
 */
GestionnaireMessage& Ticket::getMessage(){
    return *message;
}

/**
 * @brief setDate permet de fixer la date de création Ticket
 * @param date
 */
void Ticket::setDate(const QString& date) {
    dateCreation = date;
}

/**
 * @brief ajouterUnMessage permet d'ajouter un message
 * @param dep
 */
void Ticket::ajouterUnMessage(Message& msg){
    message->ajouterUnMessage(msg);
}

/**
 * @brief nbMessage retourne le nombre de message;
 * @return
 */
int Ticket::nbMessage() const {
    return message->nbMessage();
}

/**
 * @brief MessageToString retourne la liste des messages en string
 * @return
 */
QStringList Ticket::MessageToString() {
    QStringList qsl;

    for (int i = 0; i < nbMessage(); i++) {
        Message msg = message->getMessage(i);
        qsl << msg.getNom()+" :  repondu par "+msg.getCreateur()+"\n créé \nle "+msg.getdate();
    }

    return qsl;
}


/**
 * @brief clearDepenses supprime toutes les dépenses de la collection
 */
void Ticket::clearMessage() {
    message->clearMessage();
}


/**
 * @brief getrep retourne
 * @return
 */
std::map<QString, double> Ticket::getRep(){
    return reponse;
}


/**
 * @brief setDettes On calcule les dettes de tous les participants du groupe, en fonction de leur dépense
 */
void Ticket::setRep(){
    for(std::map<QString, Utilisateur>::iterator it = intervenant->begin(); it != intervenant->end(); ++it){ //on initialise toutes les dettes à 0 €
        reponse[it->second.getIdentifiant()] = 0;
    }
    for(int i = 0; i<nbMessage(); i++){ //Pour chaque dépense on vérifie qui l'a créé pour ajuster les calculs (répartir les dépenses sur l'ensemble des membres du groupes)
        for(std::map<QString, Utilisateur>::iterator it = intervenant->begin(); it != intervenant->end(); ++it){
            qDebug() << it->second.getIdentifiant();
        }
    }
}

/**
 * @brief Destructeur
 */
Ticket::~Ticket() {
    //delete intervenant;
}
