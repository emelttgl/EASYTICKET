#include "gestionnaireticket.h"
#include <algorithm>

/**
 * @brief GestionnaireTicket constructeur
 */
GestionnaireTicket::GestionnaireTicket()
{

}

/**
 * @brief ajouterTicket permet d'ajouter un Ticket a la collection
 * @param Ticket
 */
void GestionnaireTicket::ajouterTicket(Ticket& ticket){
    tickets.push_back(ticket);
}

/**
 * @brief getTicket permet de retourner un Ticket à la position i
 * @param i
 * @return
 */
Ticket& GestionnaireTicket::getTicket(const int& i) {
    return tickets[i];
}

/**
 * @brief size retourne la taille de la collection
 * @return
 */
int GestionnaireTicket::size() const {
    return tickets.size();
}

/**
 * @brief findTicket renvoie vrai si t est présent dans la collection, faux sinon
 * @param t
 * @return
 */
bool GestionnaireTicket::findTicket(const QString& t) const {
    bool trouve = false;

    for (int i = 0; i < size() && !trouve; i++) {
        if (tickets[i].getIdentifiant() == t) {
            trouve = true;
        }
    }

    return trouve;
}

/**
 * @brief getTicket retourne un Ticket
 * @param idTicket
 * @return
 */
Ticket& GestionnaireTicket::getTicket(const QString& idTicket) {
    for (int i = 0; i < size(); i++) {
        if (tickets[i].getIdentifiant() == idTicket) {
            return tickets[i];
        }
    }
    //return std::nullptr_t;
}

/**
 * @brief clear permet de supprimer tous les Tickets
 */
void GestionnaireTicket::clear() {
    tickets.clear();
}
