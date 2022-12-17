#include "pagecreationticket.h"
#include "ui_PageCreationTicket.h"
#include <QDockWidget>
#include <iostream>
#include <QMessageBox>

/**
 * @brief PageCreationTicket
 * @param parent
 */
PageCreationTicket::PageCreationTicket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageCreationTicket)
{
    ui->setupUi(this);
}

/**
 * @brief PageCreationTicket
 * @param fp fenêtre principale de l'application
 */
PageCreationTicket::PageCreationTicket(QWidget *parent, FenetrePrincipale *fp, easyticket* et) :
    QWidget(parent),
    ui(new Ui::PageCreationTicket),
    pwindow(fp),
    easyTicket(et)
{
    ui->setupUi(this);

    //setConnexion();
}


/**
 * @brief getCreerTicketButton retourne le bouton creerTicket
 * @return
 */
QPushButton *PageCreationTicket::getCreerTicketButton(){
    return ui->CreerTicket;
}


/**
 * @brief setConnexion
 */
void PageCreationTicket::setConnexion() {
    //connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(annuler()));
    //connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(onPushButtonCreerCompte()));
}


/**
 * @brief on_CreerTicket_clicked ajoute un Ticket à la listView des Tickets (Ticket portant le nom donné dans le lineEdit)
 */
void PageCreationTicket::on_CreerTicket_clicked()
{
    if (easyTicket->findTicket(ui->lineEdit->text())) {
        QMessageBox::critical(this, "Erreur création Ticket", "Deux Tickets ne peuvent pas avoir le même nom !");
    } else {
        Utilisateur u = easyTicket->getUtilisateurActif();
        Ticket tick(ui->lineEdit->text());
        u.ajouterAMesTicket(tick);
        easyTicket->inserTicket(tick, u);
    }
}

PageCreationTicket::~PageCreationTicket()
{
    delete ui;
}
