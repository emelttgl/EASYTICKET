#ifndef GESTIONNAIREMESSAGE_H
#define GESTIONNAIREMESSAGE_H

#include <vector>
#include <string>

#include "message.h"
class Message;

/**
 * @brief The GestionnaireMessage class permet de gérer une collection de dépenses:
 */
class GestionnaireMessage
{
public:
    explicit GestionnaireMessage();

    void ajouterUnMessage(Message& msg);

    Message getMessage(const int& i) const;

    Message& getMessage(const std::string& str);

    int nbMessage() const;

    std::vector<Message>::iterator begin();

    std::vector<Message>::iterator end();

    void clearMessage();

private:
    std::vector<Message> messages;

};

#endif // GESTIONNAIREMESSAGE_H
