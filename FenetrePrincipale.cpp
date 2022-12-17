#include "FenetrePrincipale.h"
#include "ui_FenetrePrincipale.h"
#include "pageaccueil.h"
#include "pageprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    pageActive = nullptr;
    qDebug()<<QSqlDatabase:: drivers();
    resize(900, 1000);
}

FenetrePrincipale::FenetrePrincipale(QWidget *parent, easyticket* et):
     QWidget(parent),
     ui(new Ui::FenetrePrincipale),
     easyTicket(et)
 {
     ui->setupUi(this);
     pageActive = nullptr;
     resize(900, 1000);
 }

/**
 * @brief getThis permet de renvoyer le pointeur de la classe pour pouvoir ajouter des "enfants"
 * @return this
 */
FenetrePrincipale* FenetrePrincipale::getThis() {
    return this;
}

/**
 * @brief setPageActive permet de positionner la page active
 * détruit celle précédente si elle existe
 * @param p page que l'on souhaite afficher
 */
void FenetrePrincipale::setPageActive(QWidget *p) {
    if (pageActive != nullptr) {
        delete pageActive;
        pageActive = nullptr;
    }

    pageActive = p;
    resizeEvent(nullptr);
    pageActive->show();
}

/**
 * @brief resizeEvent permet de redimensionner automatiquement la taille de la page lorsque
 * l'utilisateur modifie la taille de la fenêtre
 * @param event
 */
void FenetrePrincipale::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    if (pageActive) {
        pageActive->resize(width(), height());
    }
}

void FenetrePrincipale::deconnexion() {
    this->setVisible(true);
    easyTicket = ((PagePrincipale*)pageActive)->geteasyticket();
    pageActive->close();
    pageActive = nullptr;
    setPageActive(new PageAccueil(this, this, easyTicket));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete pageActive;
    delete ui;
}
