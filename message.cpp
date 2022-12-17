#include "message.h"

/**
 * @brief Message constructeur par défaut
 */
Message::Message(): numMessage(0),
    aRepondu(false) {
}

/**
 * @brief Message constructeur
 * @param num numéro du message
 * @param user utilisateur qui a crée le message
 * @param aRep donne le statut du message
 */
Message::Message(const int& num, QString& user, QString& nomMess, QString& dateMess, bool aRep):
    numMessage(num), createur(user), aRepondu(aRep),
    nom(nomMess), date(dateMess)
{
}

/**
 * @brief getNumMessage retourne le numéro de Message
 * @return
 */
int Message::getNumMessage() const {
    return numMessage;
}

/**
 * @brief getCreateur retourne le créateur du Message
 * @return
 */
QString Message::getCreateur() const {
    return createur;
}



/**
 * @brief avecRep retourne vrai si le message a une reponse,
 * faux sinon
 * @return
 */
bool Message::avecRep() const {
    return aRepondu;
}


/**
 * @brief setaRep positionne le boolean arepondu sur b
 * @param b
 */
void Message::setaRep(const bool &b) {
    aRepondu = b;
}

/**
 * @brief getNom retourne le nom du message
 * @return
 */
QString Message::getNom() const {
    return nom;
}

/**
 * @brief getdate retourne la date du Message
 * @return
 */
QString Message::getdate() const {
    return date;
}
