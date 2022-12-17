#include "pageaccueil.h"
#include "ui_PageAccueil.h"
#include "pagecreationcompte.h"
#include "pageprincipale.h"
#include <iostream>
#include <QMessageBox>

/**
 * @brief PageAccueil
 * @param parent
 */
PageAccueil::PageAccueil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAccueil)
{
    ui->setupUi(this);
    setConnect();
}

/**
 * @brief PageAccueil
 * @param parent
 * @param fp fenêtre principale de l'application
 * @param sc sharcount (Sorte de système de l'application)
 */
PageAccueil::PageAccueil(QWidget *parent, FenetrePrincipale *fp, easyticket* et) :
    QWidget(parent),
    ui(new Ui::PageAccueil),
    pwindow(fp),
    easyTicket(et)
{
    ui->setupUi(this);
    setConnect();
}

/**
 * @brief creerCompte lorsque l'utilisateur appuie sur le bouton créer un compte
 * celui-ci créer une nouvelle PageCreationCompte
 */
void PageAccueil::creerCompte() {
    pwindow->setPageActive(new PageCreationCompte(pwindow, pwindow, easyTicket));
}

/**
 * @brief setConnect
 * Permet de connecter les signaux des éléments afficher avec
 * leur slots correspondant
 */
void PageAccueil::setConnect() {
    connect(ui->boutonCreationCompte, SIGNAL(released()), this, SLOT(creerCompte()));
    connect(ui->boutonConnexion, SIGNAL(released()), this, SLOT(connexion()));
}

/**
 * @brief connexion envoie les informations de connexion a ShareCount
 * et accepte la connexion ou pas en fonction de la réponse de ShareCount
 */
void PageAccueil::connexion() {
    if (easyTicket->identifierUtilisateur(ui->lineEdit->text(), ui->lineEdit_2->text())) {
        Utilisateur u = easyTicket->getUtilisateur(ui->lineEdit->text());
        easyTicket->setUtilisateurActif(u);
        pwindow->setVisible(false);
        pwindow->setPageActive(new PagePrincipale(pwindow, pwindow, easyTicket));

    } else {
        QMessageBox::critical(this, "Erreur connexion", "Identifiant ou mot de passe inconnu, veuillez réessayer");
    }
}

PageAccueil::~PageAccueil()
{
    delete ui;
}
