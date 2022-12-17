#include "listeticket.h"
#include "ui_ListeTicket.h"
#include "pagecreationticket.h"
#include <iostream>

/**
 * @brief Listeticket
 * @param parent
 */
Listeticket::Listeticket(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Listeticket)
{
    ui->setupUi(this);
    tickets = easyTicket->getUtilisateurActif().getMesTicketToString();
    QAbstractItemModel *model = new QStringListModel(tickets);
    ui->listView->setModel(model);
}

/**
 * @brief Listeticket
 * @param fp fenêtre principale de l'application
 * @param et easyticket
 * @param parent
 */
Listeticket::Listeticket(QWidget *parent, FenetrePrincipale *fp, easyticket* et) :
    QDockWidget(parent),
    ui(new Ui::Listeticket),
    pwindow(fp),
    easyTicket(et)
{
    ui->setupUi(this);
    setConnect1();
    tickets = easyTicket->getUtilisateurActif().getMesTicketToString();
    QAbstractItemModel *model = new QStringListModel(tickets);
    ui->listView->setModel(model);


}

Listeticket::~Listeticket()
{
    delete ui;
}


/**
 * @brief setPageCreationTicket met en place la page de création de ticket
 */
void Listeticket::setPageCreationTicket(PageCreationTicket *pct){
    pageCreationTicket = pct;
    setConnect(pageCreationTicket);
}


/**
 * @brief creerTicketButtonClicked active un signal, qui sera capté par le slot qui affichera la page de création de Ticket
 */
void Listeticket::creerTicketButtonClicked(){

}

/**
 * @brief getCreerTicketButton retourne le bouton creerTicket
 * @return
 */
QPushButton *Listeticket::getCreerTicketButton(){
    return ui->creerTicketButton;
}

/**
 * @brief getListView retourne la listView (qui affiche tous les tickets)
 * @return
 */
QListView *Listeticket::getListView(){
    return ui->listView;
}

/**
 * @brief setConnect connecte les signaux et slots
 */
void Listeticket::setConnect(PageCreationTicket *pct){
    QObject::connect(pct->getCreerTicketButton(), &QPushButton::clicked, this, &Listeticket::ajouterTicket);
}

/**
 * @brief setConnect1 connecte les signaux et slots
 */
void Listeticket::setConnect1(){
    QObject::connect(ui->listView,SIGNAL(clicked(const QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
}

/**
 * @brief ajouterTicket ajoute dans la listView le nom du ticket créé
 */
void Listeticket::ajouterTicket() {
    tickets = easyTicket->getUtilisateurActif().getMesTicketToString();
    QAbstractItemModel *model = new QStringListModel(tickets);
    ui->listView->setModel(model);
}

/**
 * @brief getIndexList retourne la liste d'index de la listView
 * @return
 */
QModelIndex Listeticket::getIndexList(){
    return indexList;
}

/**
 * @brief itemClicked affiche le rang de l'item de la listView qui a été cliqué
 */
void Listeticket::itemClicked(QModelIndex index){
    qDebug() << index.data().toString();
}
