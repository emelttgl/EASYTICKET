#ifndef LISTETICKET_H
#define LISTETICKET_H

#include <QDockWidget>
#include "FenetrePrincipale.h"
#include "easyticket.h"
#include "pagecreationticket.h"
#include <QPushButton>
#include <QStringListModel>
#include <QAbstractItemModel>
#include <QListView>
#include <QDebug>

namespace Ui {
class Listeticket;
}

class Listeticket : public QDockWidget
{
    Q_OBJECT

public:
    explicit Listeticket(QWidget *parent = nullptr);
    explicit Listeticket(QWidget *parent, FenetrePrincipale *fp, easyticket* et);
    QPushButton *getCreerTicketButton();
    void setPageCreationTicket(PageCreationTicket *pct);
    QListView *getListView();
    QModelIndex getIndexList();
    ~Listeticket();

private slots:
    void creerTicketButtonClicked();
    void ajouterTicket();
    void itemClicked(QModelIndex index);

private:
    void setConnect(PageCreationTicket *pct);
    void setConnect1();
private:
    Ui::Listeticket*ui;
    FenetrePrincipale *pwindow;
    easyticket* easyTicket;
    PageCreationTicket* pageCreationTicket;
    QStringList tickets;
    QModelIndex indexList;
};

#endif // LISTETICKETS_H
