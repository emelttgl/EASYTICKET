#ifndef PAGECREATIONTICKET_H
#define PAGECREATIONTICKET_H

#include <QWidget>
#include "FenetrePrincipale.h"
#include "easyticket.h"
#include <QDockWidget>
#include <QPushButton>
#include <QString>

namespace Ui {
class PageCreationTicket;
}

class PageCreationTicket : public QWidget
{
    Q_OBJECT

public:
    explicit PageCreationTicket(QWidget *parent = nullptr);
    explicit PageCreationTicket(QWidget *parent, FenetrePrincipale *fp, easyticket* et);
    QPushButton *getCreerTicketButton();
    QString getNomTicket();
    ~PageCreationTicket();

private:
    void setConnexion();

private slots:
    void on_CreerTicket_clicked();

private:
    Ui::PageCreationTicket *ui;
    FenetrePrincipale* pwindow;
    easyticket* easyTicket;
};

#endif // PAGECREATIONTICKET_H
