#ifndef GESTIONNAIREUTILISATEURS_H
#define GESTIONNAIREUTILISATEURS_H
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <QString>

#include "utilisateur.h"

class Utilisateur;

///
/// \brief The GestionnaireUtilisateur class C'est un classe qui permet de gérer la collection d'utilisateur
///
class GestionnaireUtilisateur
{

public:
    explicit GestionnaireUtilisateur();

    void ajouterUtilisateur(Utilisateur& user);


    bool identifierUtilisateur(const QString& id, const QString& mdp) const;

    Utilisateur getUtilisateur(const QString& id) const;

    bool findUtilisateur(const QString& id) const;

    int getNombreUtilisateur() const;

    std::map<QString, Utilisateur>::iterator begin();

    std::map<QString, Utilisateur>::iterator end();

    void clear();

private:
    std::map<QString, Utilisateur> utilisateurs;
};

#endif // GESTIONNAIREUTILISATEURS_H
