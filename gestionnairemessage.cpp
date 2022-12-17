#include "gestionnairemessage.h"

/**
 * @brief GestionnaireMessage constructeur par défaut
 * @param parent
 */
GestionnaireMessage::GestionnaireMessage()
{

}

/**
 * @brief ajouterUnMessag permet d'ajouter un message
 * @param msg
 */
void GestionnaireMessage::ajouterUnMessage(Message& msg) {
    messages.push_back(msg);
}

/**
 * @brief getMessage permet de récupérer un message
 * @param i
 * @return
 */
Message GestionnaireMessage::getMessage(const int& i) const {
    return messages[i];
}

/**
 * @brief nbMessage retourne le nombre de messages
 * @return
 */
Message& GestionnaireMessage::getMessage(const std::string& str) {
    for(Message message : messages){
        if(message.getNom().toStdString() == str){
            return message;
        }
    }
}

/**
 * @brief begin retourne l'itérateur begin de la collection
 * @return
 */
int GestionnaireMessage::nbMessage() const {
    return messages.size();
}

/**
 * @brief begin retourne l'itérateur begin de la collection
 * @return
 */
std::vector<Message>::iterator GestionnaireMessage::begin() {
    return messages.begin();
}


/**
 * @brief end retorune l'itérateur end de la collection
 * @return
 */
std::vector<Message>::iterator GestionnaireMessage::end() {
    return messages.end();
}


/**
 * @brief clearMessage supprimme tous les messages de la collection
 */
void GestionnaireMessage::clearMessage() {
    messages.clear();
}

