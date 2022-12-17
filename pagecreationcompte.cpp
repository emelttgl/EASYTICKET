#include "pagecreationcompte.h"
#include "ui_PageCreationCompte.h"
#include "pageaccueil.h"
#include "QMessageBox"
#include <iostream>

/**
 * @brief PageCreationCompte
 * @param parent
 */
PageCreationCompte::PageCreationCompte(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageCreationCompte)
{
    ui->setupUi(this);
    setConnexion();
}

/**
 * @brief PageCreationCompte
 * @param fp fenêtre principale de l'application
 * @param et easyticket
 * @param parent
 */
PageCreationCompte::PageCreationCompte(QWidget *parent, FenetrePrincipale *fp, easyticket* et) :
    QWidget(parent),
    ui(new Ui::PageCreationCompte),
    pwindow(fp),
    easyTicket(et)
{
    ui->setupUi(this);
    setConnexion();

}

/**
 * @brief annuler Permet d'annuler la création de compte et de retrouner
 * sur la page d'accueil
 */
void PageCreationCompte::annuler() {
    pwindow->setPageActive(new PageAccueil(pwindow, pwindow, easyTicket));
}

/**
 * @brief setConnect
 * Permet de connecter les signaux des éléments afficher avec
 * leur slots correspondant
 */
void PageCreationCompte::setConnexion() {
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(annuler()));
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(onPushButtonCreerCompte()));
}

/**
 * @brief onPushButtonCreerCompte Envoie les informations entré par l'utilisateur
 * a easyticket pour les traiter.
 */
void PageCreationCompte::onPushButtonCreerCompte() {
    Utilisateur u;

    u.setIdentifiant(ui->lineEdit_2->text());

    if (ui->lineEdit_2->text().size() < 4) {
        QMessageBox::critical(this, "Erreur identifiant", "L'identifiant doit contenir au moins 4 caractères");
    } else if (easyTicket->findUtilisateur(u.getIdentifiant())) {
        QMessageBox::critical(this, "Erreur création du compte", "Impossible de créer le compte l'identifiant existe déjà !");
    } else if (ui->lineEdit_3->text().size() < 4) {
        QMessageBox::critical(this, "Erreur mot de passe", "Le mot de passe doit contenir au moins 4 caractères.");
    } else if (ui->lineEdit_3->text() != ui->lineEdit_4->text()) {
        QMessageBox::critical(this, "Erreur mot de passe", "Les mots de passe ne correspondent pas.");
    } else if (ui->lineEdit_5->text() != ui->lineEdit_6->text()) {
        QMessageBox::critical(this, "Erreur mail", "Les mails ne correspondent pas.");
    } else {
        u.setMotDePasse(ui->lineEdit_4->text());
        u.setMail(ui->lineEdit_6->text());
        easyTicket->creerUtilisateur(u);

        pwindow->setPageActive(new PageAccueil(pwindow, pwindow, easyTicket));
    }
}

PageCreationCompte::~PageCreationCompte()
{
    delete ui;
}
