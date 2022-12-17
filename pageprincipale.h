#ifndef PAGEPRINCIPALE_H
#define PAGEPRINCIPALE_H

#include <QMainWindow>
#include <FenetrePrincipale.h>
#include "listeticket.h"
#include "pagegestionmessage.h"
#include <QListView>
#include <QDebug>

namespace Ui {
class PagePrincipale;
}

class PagePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit PagePrincipale(QWidget *parent = nullptr);
    explicit PagePrincipale(QWidget *parent, FenetrePrincipale *fp, easyticket* et);
    easyticket* geteasyticket();
    ~PagePrincipale();

private:
    void setConnect(Listeticket *lt);

private slots:
    void ajouterTicket();
    void afficherTicket();  //Affichage des données du groupe dans le central widget

private:
    Ui::PagePrincipale *ui;
    FenetrePrincipale* pwindow;
    easyticket* easyTicket;
    Listeticket* lt;
};

#endif // PAGEPRINCIPALE_H
