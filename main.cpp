#include "easyticket.h"
#include "FenetrePrincipale.h"
#include "pageaccueil.h"
#include "pagecreationcompte.h"
#include "pageprincipale.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FenetrePrincipale fenetrePrincipale;
    easyticket* et = new easyticket();
    fenetrePrincipale.setPageActive(new PageAccueil(&fenetrePrincipale, &fenetrePrincipale, et));


    fenetrePrincipale.show();
    return a.exec();
}

