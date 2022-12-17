#ifndef MESSAGE_H
#define MESSAGE_H


#include "utilisateur.h"

class Utilisateur;

/**
 * @brief The Message class définie un message
 *
 */
class Message
{

public:
    explicit Message();

    explicit Message(const int& num, QString& user, QString& nomMess, QString& dateMess, bool aRep = false);

    int getNumMessage() const;

    QString getCreateur() const;

    bool avecRep() const;

    void setaRep(const bool& b);

    QString getNom() const;

    QString getVb() const;

    QString getdate() const;


private:
    int numMessage;
    QString nom;
    QString date;
    QString createur;
    QString vb;
    bool aRepondu;


};

#endif // MESSAGE_H
