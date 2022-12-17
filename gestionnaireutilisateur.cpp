#include "Gestionnaireutilisateur.h"

/**
 * @brief class GestionnaireUtilisateur constructeur
 */
GestionnaireUtilisateur::GestionnaireUtilisateur()
{
}

/**
 * @brief ajouterUtilisateur permet d'ajouter un utilisateur
 * @param user
 */
bool GestionnaireUtilisateur::identifierUtilisateur(const QString& id, const QString& mdp) const{
    std::map<QString, Utilisateur>::const_iterator it = utilisateurs.find(id);

    bool identifie = false;

    if (it == utilisateurs.end()) {
        identifie = false;
    } else {
        identifie = true;
        if (mdp == it->second.getMotDePasse()) {
            identifie = true;
        } else {
            identifie = false;
        }
    }

    return identifie;
}

/**
 * @brief identifierUtilisateur permet d'identifer un utilisateur à l'aide de son mot de
 * passe et de sont identifiant
 * @param identifiant
 * @param mdp
 * @return
 */
void GestionnaireUtilisateur::ajouterUtilisateur(Utilisateur& user){
    utilisateurs[user.getIdentifiant()] = user;
}

///
/// \brief getUtilisateur retorune l'utilisateur avec l'identifiant "id"
/// \param id
/// \return
///
Utilisateur GestionnaireUtilisateur::getUtilisateur(const QString& id) const {
    std::map<QString, Utilisateur>::const_iterator it = utilisateurs.find(id);

    return it->second;
}

/**
 * @brief findUtilisateur retourne vrai si l'utilisateur st trouvé, faux sinon
 * @param id
 * @return
 */
bool GestionnaireUtilisateur::findUtilisateur(const QString& id) const {
     std::map<QString, Utilisateur>::const_iterator it = utilisateurs.find(id);

     if (it == utilisateurs.end()) {
         return false;
     } else {
         return true;
     }
}

/**
 * @brief getNombreUtilisateur retourne le nombre d'utilisateur présent dans la map
 * @return
 */
int GestionnaireUtilisateur::getNombreUtilisateur() const {
    return utilisateurs.size();
}

/**
 * @brief begin retourne l'itérateur begin de la collection
 * @return
 */
std::map<QString, Utilisateur>::iterator  GestionnaireUtilisateur::begin() {
    return utilisateurs.begin();
}

/**
 * @brief end retourne l'itérateur end de la collection
 * @return
 */
std::map<QString, Utilisateur>::iterator  GestionnaireUtilisateur::end() {
    return utilisateurs.end();
}


/**
 * @brief clear supprime tous les utilisateurs de la collection
 */
void GestionnaireUtilisateur::clear() {
    utilisateurs.clear();
}
