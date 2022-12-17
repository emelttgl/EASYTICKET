#ifndef PAGEGESTIONMESSAGE_H
#define PAGEGESTIONMESSAGE_H

#include "FenetrePrincipale.h"
#include "easyticket.h"
#include <QWidget>
#include <QLabel>
#include "message.h"
#include <QInputDialog>
#include <QStringListModel>
#include <QDialogButtonBox>
#include <QDebug>
#include <QRegExp>
#include <string>

namespace Ui {
class PageGestionMessage;
}

class PageGestionMessage : public QWidget
{
    Q_OBJECT

public:
    explicit PageGestionMessage(QWidget *parent = nullptr);
    explicit PageGestionMessage(QWidget *parent, FenetrePrincipale *fp, easyticket* et);
    QLabel *getLabelNomTicket();
    void miseAJourIntervenant();
    void miseAJourMessage();
     void setEquilibre();
    ~PageGestionMessage();

private slots:
    void on_ajouterMessageButton_clicked();
    void on_ajouterIntervenantButton_clicked();

    void on_reglerMessage_clicked();

private:
    Ui::PageGestionMessage *ui;
    FenetrePrincipale* pwindow;
    easyticket* easyTicket;
    QLabel nomTicket;
    QStringList message;
};

#endif // PAGEGESTIONMESSAGE_H
