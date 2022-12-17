#include "basededonnes.h"
#include <iostream>
#include <QDateTime>

/**
 * @brief The DbManager class qui permet de gérer les entrées et les sorties
 * avec la base de donnée
 */

/**
 * @brief DbManager Constrcteur par défaut
 * @param path de la base de donnée
 */
Basededonnes::Basededonnes(const QString& path) : creerDataBase(false)
{
    easyTicketBase = QSqlDatabase::addDatabase("QSQLITE");
    easyTicketBase.setDatabaseName(path);
    easyTicketBase.open();

    if (!easyTicketBase.open()) {
        qDebug() << "Erreur: connexion avec la base de donnée échouée";
    } else {
        qDebug() << "Connexion réussie" ;
    }
}

/**
 * @brief createDataBase permet de créer et d'initialiser la base de donnée
 * si le fichier ShareCountDataBase.db n'existe pas
 */
void Basededonnes::createDataBase() {

    if (creerDataBase) {
        QSqlQuery query;
        query.prepare("CREATE TABLE Utilisateurs(idUser TEXT PRIMARY KEY,"
                      " mdp TEXT NOT NULL,"
                      " mail TEXT NULL);");
        if (query.exec()) {
            qDebug() << "Création de la table Utilisateurs réussie.";
        } else {
            qDebug() << "Création de la table Utilisateurs échouée.";
        }

        query.prepare("CREATE TABLE TicketGestion(idTicket TEXT, "
                      "idUser TEXT,"
                      "description TEXT NULL,"
                      "dateCreation TEXT NOT NULL,"
                      "PRIMARY KEY(idTicket, idUser),"
                      "FOREIGN KEY (idUser) REFERENCES Utilisateurs(idUser));");
        if (query.exec()) {
            qDebug() << "Création de la table TicketGestion réussie.";
        } else {
            qDebug() << "Création de la table TicketGestion échouée.";
        }

        query.prepare("CREATE TABLE Utilisateurs(idTicket TEXT, "
                      "idUser TEXT,"
                      "PRIMARY KEY(idTicket, idUser),"
                      "FOREIGN KEY (idUser) REFERENCES Utilisateurs(idUser),"
                      "FOREIGN KEY (idGroupe) REFERENCES TicketGestion(idTicket));");
        if (query.exec()) {
            qDebug() << "Création de la table Utilisateurs réussie.";
        } else {
            qDebug() << "Création de la table Utilisateurs échouée.";
        }

        query.prepare("CREATE TABLE Historique(noHist INTEGER, "
                      "idTicket TEXT,"
                      "contenu TEXT NOT NULL,"
                      "dateHisto TEXT NOT NULL,"
                      "PRIMARY KEY(noHist, idTicket),"
                      "FOREIGN KEY (idTicket) REFERENCES TicketGestion(idTicket));");
        if (query.exec()) {
            qDebug() << "Création de la table Historique réussie.";
        } else {
            qDebug() << "Création de la table Historique échouée.";
        }

        query.prepare("CREATE TABLE Message(idUser TEXT,"
                      "idTicket TEXT,"
                      "noMsg INTEGER,"
                      "nomMsg TEXT NOT NULL,"
                      "BoolMsgRep INTEGER DEFAULT 0," // Ceci représente un booléen
                      "dateDep TEXT NOT NULL,"
                      "PRIMARY KEY (idUser, idTicket, noMsg),"
                      "FOREIGN KEY (idUser) REFERENCES Utilisateurs(idUser), "
                      "FOREIGN KEY (idTicket) REFERENCES TicketGestion(idTicket));");
        if (query.exec()) {
            qDebug() << "Création de la table Message réussie.";
        } else {
            qDebug() << "Création de la table Message échouée.";
        }

        query.prepare("CREATE TABLE Reponse(idUser TEXT,"
                      "noMsg INTEGER,"
                      "BoolRep INTEGER DEFAULT 0," // Ceci représente un booléen
                      "dateRep TEXT NOT NULL,"
                      "PRIMARY KEY (idUser, noMsg),"
                      "FOREIGN KEY (idUser) REFERENCES Utilisateurs(idUser), "
                      "FOREIGN KEY (noMsg) REFERENCES Message(noMsg));");
        if (query.exec()) {
            qDebug() << "Création de la table Reponse réussie.";
        } else {
            qDebug() << "Création de la table Reponse échouée.";
        }
    }
}

/**
 * @brief insererUtilisateur permet d'ajouter un utilisateur à la base de donnée
 * @param user
 */
void Basededonnes::insererUtilisateur(const Utilisateur& user) const {
    QSqlQuery query;
    query.prepare("INSERT INTO utilisateurs(idUser, mdp, mail)"
                   "VALUES (:idUser, :mdp, :mail);");
    query.bindValue(":idUser", QVariant(user.getIdentifiant()));
    query.bindValue(":mdp", QVariant(user.getMotDePasse()));
    query.bindValue(":mail", QVariant(user.getMail()));

    if (query.exec()) {
        qDebug() << "L'utilisateur a bien était ajouté a a table utilisateur";
    } else {
        qDebug() << "Echec de l'ajout de l'utilisateur";
    }
}

/**
 * @brief initialiserListeUtilisateur permet de récupérer tous les utilisateurs dans la base de donnée
 * au lancement de k'application
 * @param sc
 */
void Basededonnes::initialiserListeUtilisateur(GestionnaireUtilisateur& users) {
    QSqlQuery query;

    query.prepare("Select * from utilisateurs;");

    if (query.exec()) {
        qDebug() << "Selection pour initialisation de la liste des utilisateurs réussie";
    } else {
        qDebug() << "Selection pour initialisation de la liste des utilisateurs échouée";
    }

    while (query.next()) {
        QString id = query.value("idUser").toString();
        QString mdp = query.value("mdp").toString();
        QString mail = query.value("mail").toString();
        Utilisateur u;
        u.setIdentifiant(id);
        u.setMotDePasse(mdp);
        u.setMail(mail);
        users.ajouterUtilisateur(u);
    }
}

/**
 * @brief insererunGroupe permet d'inserer un groupe dans la table GroupesGestionBudget
 * et de mettre à jour la table UtilisateursParGroupesGDB
 * @param grp
 * @param user
 */
void Basededonnes::insererunTicket(const Ticket& t, const Utilisateur& user) {
    QSqlQuery query;
    query.prepare("INSERT INTO TicketGestion(idTicket, idUser, description, dateCreation )"
                   "VALUES (:idTicket, :idUser, :description, :dateCreation);");
    query.bindValue(":idTicket", QVariant(t.getIdentifiant()));
    query.bindValue(":idUser", QVariant(user.getIdentifiant()));
    query.bindValue(":description", QVariant(t.getDescription()));
    query.bindValue(":dateCreation", QVariant(t.getDateCreation()));

    if (query.exec()) {
        qDebug() << "Le Ticket a bien était ajouté a la table Ticket";
        QString action;
        action.append(user.getIdentifiant());
        action.append(" a crée le Ticket.");
        updateHistorique(t.getIdentifiant(), action );
    } else {
        qDebug() << "Echec de l'ajout du Ticket";
    }

    query.clear();
    query.prepare("INSERT INTO Utilisateurs(idTicket, idUser)"
                  "VALUES(:idTicket, :idUser);");
    query.bindValue(":idTicket", QVariant(t.getIdentifiant()));
    query.bindValue(":idUser", QVariant(user.getIdentifiant()));

    if (query.exec()) {
        qDebug() << "Utilisateurs mise a jour";
    } else {
        qDebug() << "Utilisateurs echèc mise à jour";
    }
}

/**
 * @brief initialiserGroupeUtilisateur permet d'initialiser les groupes de l'utilisateur
 * @param grp
 * @param idUser
 */
void Basededonnes::initialiserTicketUtilisateur(GestionnaireTicket& t, const QString& idUser) {
    QSqlQuery query;
    t.clear();

    query.prepare("SELECT DISTINCT GT.idTicket, GT.idUser, GT.description, GT.dateCreation "
                  "FROM TicketGestion GT, Utilisateurs U "
                  "WHERE U.idUser = :id AND U.idTicket = GT.idTicket;");
    query.bindValue(":id", QVariant(idUser));

    if (query.exec()) {
        qDebug() << "Selection du Ticket réussie";
    } else {
        qDebug() << "Selection du Ticket échoué";
    }

    while (query.next()) {
        QString idGroupe = query.value("idTicket").toString();
        QString idUser = query.value("idUser").toString();
        QString description = query.value("description").toString();
        QString date = query.value("dateCreation").toString();
        Ticket ti(idGroupe, description);
        ti.setDate(date);
        t.ajouterTicket(ti);
    }
}

/**
 * @brief appartientAuGroupe retourne vrai si user appartient a un groupe grp
 * @param user
 * @param grp
 * @return
 */
bool Basededonnes::appartientAIngenieur(const QString& user, const QString& t) {
    bool trouve = false;

    QSqlQuery query;

    query.prepare("SELECT DISTINCT idTicket FROM Utilisateurs "
                  "WHERE idUser = :idUser;");
    query.bindValue(":idUser", QVariant(user));

    if (query.exec()) {
        qDebug() << "Requête appartient réussie";
    } else {
        qDebug() << "Requête appartient échouée " << easyTicketBase.lastError().text();
    }

    while (query.next() && !trouve) {
        QString idTicket = query.value("idTicket").toString();
        if (idTicket == t) {
            trouve = true;
        }
    }

    return trouve;
}

/**
 * @brief ajouterParticipantAuGroupe ajoute le participant "user" au groupe "grp";
 * @param user
 * @param grp
 */
void Basededonnes::ajouterIntervenantAuTicket(const QString& user, const QString& t) {
    QSqlQuery query;
    query.prepare("INSERT INTO Utilisateurs(idTicket, idUser)"
                  "VALUES(:idTicket, :idUser);");
    query.bindValue(":idTicket", QVariant(t));
    query.bindValue(":idUser", QVariant(user));

    if (query.exec()) {
        qDebug() << "Utilisateurs mise a jour";
        QString action;
        action.append(user);
        action.append(" ajouté au Ticket.");
        updateHistorique(t, action );
    } else {
        qDebug() << "Utilisateurs échec mise à jour";
    }
}

/**
 * @brief initialiserParticipants permet d'initialiser les participants au groupe grp
 * pour l'afficher
 * @param grp
 */
QStringList Basededonnes::initialiserIntervenant(const QString& t) {
    QSqlQuery query;

    query.prepare("SELECT DISTINCT idUser FROM Utilisateurs "
                  "WHERE idTicket = :idTicket;");
    query.bindValue(":idTicket", QVariant(t));

    if (query.exec()) {
        qDebug() << "Requête initaliserIntervenant réussie";
    } else {
        qDebug() << "Requête initaliserIntervenant échouée";
    }

    QStringList listeUser;


    while (query.next()) {
        QString idUser = query.value("idUser").toString();
        listeUser << idUser;
    }

    return listeUser;
}

/**
 * @brief insererUneDepense permet d'insérer une dépense pour le groupe "grp"
 * dans la table Depenses
 * @param dep
 * @param grp
 */
void Basededonnes::insererUnMessage(const Message &msg, const Ticket &t) {
    QSqlQuery query;

    query.prepare("INSERT INTO Message(idUser, idTicket, noMsg, nomMsg, dateMsg)"
                  "VALUES (:idUser, :idTicket, :noMsg :nomMsg, :dateMsg);");
    query.bindValue(":idUser", QVariant(msg.getCreateur()));
    query.bindValue(":idTicket", QVariant(t.getIdentifiant()));
    query.bindValue(":noMsg", QVariant(msg.getNumMessage()));
    query.bindValue(":nomMsg", QVariant(msg.getNom()));
    query.bindValue(":dateMsg", QVariant(msg.getdate()));

    if (query.exec()) {
        qDebug() << "Requête inserUnMessage réussie";
        QString action;
        action.append(msg.getCreateur());
        action.append(" a crée un message.");
        updateHistorique(t.getIdentifiant(), action );
    } else {
        qDebug() << "Requête insererUnMessage échouée" << query.lastError().text();
    }
}

/**
 * @brief initialiserDepensesGroupe permet d'initialiser toutes les dépenses du groupe
 * @param grp
 */
void Basededonnes::initialiserMessageTicket(Ticket& t) {
    QSqlQuery query;

    query.prepare("SELECT * FROM Message "
                  "WHERE idTicket = ? ;");
    query.addBindValue(QVariant(t.getIdentifiant()));

    if (query.exec()) {
        qDebug() << "Selection pour les message du groupe réussie";
    } else {
        qDebug() << "Selection pour les message du groupe échouée " << query.lastError().text();
    }

    t.clearMessage();

    while (query.next()) {
        QString idUser = query.value("idUser").toString();
        int noMsg = query.value("noMsg").toInt();
        bool boolRep = query.value("boolRep").toBool();
        QString dateRep = query.value("dateRep").toString();
        QString nomMsg = query.value("nomMsg").toString();

        Message msg(noMsg, idUser, nomMsg, dateRep, boolRep);
        t.ajouterUnMessage(msg);
    }
}

/**
 * @brief updateHistorique a chaque fois qu'une action est fête celle-ci
 * est enregistré dans la table historique.
 * @param grp
 * @param action
 */
void Basededonnes::updateHistorique(const QString& t, const QString& action) {
    QSqlQuery query;
    QDateTime date;

    query.prepare("INSERT INTO Historique(idTicket, contenu, dateHisto) "
                  "VALUES(:idTicket, :contenu, :dateHisto);");
    query.bindValue(":idTicket", QVariant(t));
    query.bindValue(":contenu", QVariant(action));
    query.bindValue(":dateHisto", QVariant(date.currentDateTime().toString("dd/MM/yyyy hh:mm:ss")));

    if (query.exec()) {
        qDebug() << "Historique mise à jour";
    } else {
        qDebug() << "Echec de la mise à jour de l'historique" << query.lastError().text();
    }
}
