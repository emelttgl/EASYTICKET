#ifndef GESTIONNAIRETICKET_H
#define GESTIONNAIRETICKET_H

#include <QString>
#include <vector>

#include "ticket.h"

class Ticket;

/**
 * @brief The GestionnaireTicket class qui gère une collection de Ticket
 */
class GestionnaireTicket
{
public:
    explicit GestionnaireTicket();

    void ajouterTicket(Ticket &ticket);

    Ticket& getTicket(const int& i);

    int size() const;

    bool findTicket(const QString& t) const;

    Ticket& getTicket(const QString& idTicket);

    void clear();

private:
    std::vector<Ticket> tickets;
};

#endif // GESTIONNAIRETICKET_H
