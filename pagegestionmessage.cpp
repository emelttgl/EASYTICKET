#include "pagegestionmessage.h"
#include "ui_pagegestionmessage.h"
#include <QMessageBox>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <QDoubleSpinBox>
#include <QDateEdit>

/**
 * @brief PageGestionMessagae
 * @param parent
 */
PageGestionMessage::PageGestionMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageGestionMessage)
{
    ui->setupUi(this);
}

/**
 * @brief PageGestionMessage
 * @param fp fenêtre principale de l'application
 * @param parent
 */
PageGestionMessage::PageGestionMessage(QWidget *parent, FenetrePrincipale *fp, easyticket* et):
    QWidget(parent),
    ui(new Ui::PageGestionMessage),
    pwindow(fp),
    easyTicket(et)
{
    ui->setupUi(this);
    ui->messageListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->intervenantLisetView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/**
 * @brief getLabelNomTicket
 * @return
 */
QLabel *PageGestionMessage::getLabelNomTicket(){
    return ui->label;
}


PageGestionMessage::~PageGestionMessage()
{
    delete ui;
}


/**
 * @brief on_ajouterMessageButton_clicked ajoute un message
 */
void PageGestionMessage::on_ajouterMessageButton_clicked()
{
    QString idTicket = ui->label->text();

    QDialog * d = new QDialog();
    QVBoxLayout * vbox = new QVBoxLayout();
    QLineEdit * lineEditA = new QLineEdit();
    QDoubleSpinBox * doubleSpinBoxA = new QDoubleSpinBox();
    doubleSpinBoxA->setMinimum(0);
    doubleSpinBoxA->setMaximum(10000);
    doubleSpinBoxA->setSingleStep(0.01);
    doubleSpinBoxA->setValue(0);
    doubleSpinBoxA->setDecimals(2);
    QDateEdit * dateEditA = new QDateEdit();
    QLabel * labelA = new QLabel();
    QLabel * labelB = new QLabel();
    QLabel * labelC = new QLabel();

    labelA->setText("Titre :");
    labelB->setText("Message");
    labelC->setText("Date :");

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, &QDialogButtonBox::clicked, d, &QDialog::accept);
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(labelA);
    vbox->addWidget(lineEditA);
    vbox->addWidget(labelB);
    vbox->addWidget(doubleSpinBoxA);
    vbox->addWidget(labelC);
    vbox->addWidget(dateEditA);
    vbox->addWidget(buttonBox);

    d->setAttribute(Qt::WA_QuitOnClose, false); //Empêche la fermeture de la main window
    d->setLayout(vbox);
    d->exec();

    /* On récupère les informations des éditeurs et on les vérifie */
    bool ajouterMessage = false;
    QString titre = lineEditA->text();
    double message = doubleSpinBoxA->value();
    QString messageTxt;
    QDate date = dateEditA->date();
    QString dateTxt;

    if (message != 0) {
        ajouterMessage = true;

        std::ostringstream streamObj;
        streamObj<< std::fixed;
        streamObj << std::setprecision(2);
        streamObj << message;
        messageTxt = QString::fromStdString(streamObj.str());

        if (titre.isEmpty()) {
            titre.append("Message ");
            titre.append(QString::fromStdString(std::to_string(easyTicket->getTicketActif().nbMessage() + 1)));
        }

        if (!date.isValid()) {
            ajouterMessage = false;
            QMessageBox::critical(this, "Erreur Ajout Message", "Date invalide");
        } else {
            dateTxt = date.toString("dd/MM/yyyy");
        }


    } else {
        ajouterMessage = false;
        QMessageBox::critical(this, "Erreur Ajout MESSAGE", "Montant invalide");
    }

    if (ajouterMessage) {
        QString user = easyTicket->getUtilisateurActif().getIdentifiant();
        Message msg (easyTicket->getTicketActif().nbMessage(), user,
                      titre, dateTxt);
        easyTicket->ajouterUnMessage(msg);
        miseAJourMessage();
    }
    setEquilibre();
}

/**
 * @brief on_ajouterIntervenantButton_clicked ajoute un intervnenant
 */
void PageGestionMessage::on_ajouterIntervenantButton_clicked() {
    QString user = QInputDialog::getText(this, "Ajouter Un Intervnant", "Identifiant Utilisateur: ");

    bool ajouter = false;

    if (!user.isEmpty()) {
        if (easyTicket->findUtilisateur(user)) {
            ajouter = true;
            if (easyTicket->appartientAuTicket(user, ui->label->text())) {
                ajouter = false;
                QMessageBox::critical(this, "Erreur Ajout Intervenant", "");
            }
        } else {
            ajouter = false;
            QMessageBox::critical(this, "Erreur Ajout Intervenant", "L'identifiant n'existe pas !");
        }
    } else {
        ajouter = false;
    }

    if (ajouter) {

        easyTicket->ajouterIntervenantAuTicket(user, ui->label->text());
        QAbstractItemModel *model = new QStringListModel(easyTicket->initialiserIntervenant(ui->label->text()));
        ui->intervenantLisetView->setModel(model);
    }
}

/**
 * @brief
 */
void PageGestionMessage::setEquilibre(){
    QString intervenant;
    QStringList list = easyTicket->initialiserIntervenant(ui->label->text());
    qDebug() << QString::number(list.size());
    for(int i=0; i<list.size();i++){
        intervenant = list.at(i);
        easyTicket->getTicketActif().ajouterUnIntervenant(easyTicket->getUtilisateur(intervenant));
    }
    easyTicket->getTicketActif().setRep(); //initialisation des dettes (calcul des dettes)
    std::map<QString, double> rep = easyTicket->getTicketActif().getRep();
    QStringList equilibreRep;
    QString nom;
    QString val;
    for(std::map<QString, double>::iterator it = rep.begin(); it != rep.end(); ++it){
        val = QString::number(it->second);
        nom = it->first;
        equilibreRep << nom + " : "+val+" €";
    }

    QStandardItemModel *model = new QStandardItemModel();
    QList<QStandardItem *> list1;
    ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_3->setViewMode(QListView::ListMode);

    QRegExp rx(".+-{1}.+"); //Cherche un '-', pour trouver un nombre négatif
    for(int i=0;i<equilibreRep.size();i++){
        list1 << new QStandardItem(equilibreRep.at(i));
    }
    model->appendColumn(list1);

    for(int i=0;i<equilibreRep.size();i++){

        QModelIndex vIndex = model->index(i, 0);
        QMap<int, QVariant> vMap = model->itemData(vIndex);
        if(rx.exactMatch(equilibreRep.at(i))){
            vMap.insert(Qt::BackgroundRole, QVariant(QBrush(Qt::red))); // Si l'utilisateur doit de l'argent au groupe
        }else{
            vMap.insert(Qt::BackgroundRole, QVariant(QBrush(Qt::green))); // Si l'utilisateur a avancé plus d'argent que les autres
        }
        model->setItemData(vIndex, vMap);

    }
    ui->listView_3->setModel(model);
}

/**
 * @brief miseAJourIntervennat affiche les intervennats
 */
void PageGestionMessage::miseAJourIntervenant() {
    QAbstractItemModel *model = new QStringListModel(easyTicket->initialiserIntervenant(ui->label->text()));
    ui->intervenantLisetView->setModel(model);
}

/**
 * @brief miseAJourMessage affiche les messages dans la listView des messages
 */
void PageGestionMessage::miseAJourMessage() {
    QAbstractItemModel *model = new QStringListModel(easyTicket->getTicketActif().MessageToString());
    ui->messageListView->setModel(model);
}

/**
 * @brief on_reglerMessage_clicked ajoute
 */
void PageGestionMessage::on_reglerMessage_clicked()
{
    //ui->depenseListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QModelIndex index = ui->messageListView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    std::string s = itemText.toStdString();
    std::string delimiter = " :";
    std::string token = s.substr(0, s.find(delimiter));
    std::cout << token << std::endl;


    miseAJourMessage();
}
