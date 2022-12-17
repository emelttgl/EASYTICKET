#ifndef PAGEACCUEIL_H
#define PAGEACCUEIL_H

#include <QWidget>
#include <FenetrePrincipale.h>
#include <easyticket.h>

namespace Ui {
class PageAccueil;
}

/**
 * @brief The PageAccueil class
 */
class PageAccueil : public QWidget
{
    Q_OBJECT

public:

    explicit PageAccueil(QWidget *parent = nullptr);

    explicit PageAccueil(QWidget *parent, FenetrePrincipale *fp, easyticket* et);

    ~PageAccueil();

private:
    void setConnect();

public slots:
    void creerCompte();

    void connexion();

private:
    Ui::PageAccueil *ui;
    FenetrePrincipale *pwindow;
    easyticket* easyTicket;
};

#endif // PAGEACCUEIL_H
