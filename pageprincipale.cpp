#include "pageprincipale.h"
#include "ui_PagePrincipale.h"
#include <QtWidgets>
#include <QDockWidget>
#include "ui_PageCreationTicket.h"
#include "basededonnes.h"
#include "QListWidget"
#include "QTextEdit"

/**
 * @brief PagePrincipale
 * @param parent
 */
PagePrincipale::PagePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PagePrincipale)
{
    ui->setupUi(this);
}

/**
 * @brief PagePrincipale
 * @param fp fenêtre principale de l'application
 */
PagePrincipale::PagePrincipale(QWidget *parent, FenetrePrincipale *fp, easyticket* et) :
    QMainWindow(parent),
    ui(new Ui::PagePrincipale),
    pwindow(fp),
    easyTicket(et)
{
    ui->setupUi(this);

    Listeticket *vueTicket = new Listeticket(pwindow, pwindow, easyTicket);
    addDockWidget(Qt::LeftDockWidgetArea, vueTicket);
    lt = vueTicket;
    setConnect(lt);
    setWindowTitle("EasyTicket - " + easyTicket->getUtilisateurActif().getIdentifiant());
    //afficherTicket();
}

/**
 * @brief afficherGroupe place la page de gestion de budget au centre de la mainWindow
 */
void PagePrincipale::afficherTicket(){
    PageGestionMessage *pgdm = new PageGestionMessage(pwindow, pwindow, easyTicket);

    //qDebug() << vlg->getListView()->currentIndex().data().toString();
    pgdm->getLabelNomTicket()->setText(lt->getListView()->currentIndex().data().toString());
    setCentralWidget(pgdm);
    pgdm->miseAJourIntervenant();
    easyTicket->setTicketActif(easyTicket->getUtilisateurActif().getTicket(lt->getListView()->currentIndex().data().toString()));
    pgdm->miseAJourMessage();
    pgdm->setEquilibre();
}

PagePrincipale::~PagePrincipale()
{
    delete ui;
}


/**
 * @brief ajouterGroupe place la page de création de groupe au centre de la mainWindow
 */
void PagePrincipale::ajouterTicket()
{
    PageCreationTicket *pct = new PageCreationTicket(pwindow, pwindow, easyTicket);
    setCentralWidget(pct);
    lt->setPageCreationTicket(pct);
}

/**
 * @brief setConnect connecte les signaux et slots
 */
void PagePrincipale::setConnect(Listeticket *lt){
    QObject::connect(lt->getCreerTicketButton(), &QPushButton::clicked, this, &PagePrincipale::ajouterTicket); //lors d'un clique sur le bouton "Créer un groupe" de la vueListeGroupe on affiche la pageCréation groupe
    QObject::connect(lt->getListView(), SIGNAL(clicked(const QModelIndex)),this,SLOT(afficherTicket()));
    QObject::connect(ui->actionDeconnexion, SIGNAL(triggered(bool)), this->parent(), SLOT(deconnexion()));
}


/**
 * @brief getShareCount retourne le ShareCount
 * @return
 */
easyticket* PagePrincipale::geteasyticket() {
    return easyTicket;
}
