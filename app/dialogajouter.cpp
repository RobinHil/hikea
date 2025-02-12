#include "dialogajouter.h"
#include "ui_dialogajouter.h"

DialogAjouter::DialogAjouter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjouter)
{
    ui->setupUi(this);
    setWindowTitle(tr("Ajout d'un article"));

    ui->disponibilite->setDecimals(0);

    ui->longArticle->setMinimum(0);
    ui->largArticle->setMinimum(0);
    ui->profArticle->setMinimum(0);
    ui->poidArticle->setMinimum(0);
    ui->prixArticle->setMinimum(0);
    ui->disponibilite->setMinimum(0);

    ui->longArticle->setMaximum(10000);
    ui->largArticle->setMaximum(10000);
    ui->profArticle->setMaximum(10000);
    ui->poidArticle->setMaximum(10000);
    ui->prixArticle->setMaximum(1000000);
    ui->disponibilite->setMaximum(1000000);

    categories.push_back("meuble");
    categories.push_back("decoration");
    categories.push_back("rangement");
    categories.push_back("literie");
    categories.push_back("cuisine");
    categories.push_back("eclairage");
    ui->categArt->addItems(categories);
}

DialogAjouter::~DialogAjouter()
{
    delete ui;
}

QString DialogAjouter::getNomArticleEdit() const
{
    return this->ui->nomArticle->text();
}

QString DialogAjouter::getnumArticleEdit() const
{
    return this->ui->numArticle->text();
}

QString DialogAjouter::getnomPhotoEdit() const
{
    return this->ui->imageArticle->text();
}

QString DialogAjouter::getdescArticleEdit() const
{
    return this->ui->descArticle->toPlainText();
}
QString DialogAjouter::getnomDesignerEdit() const
{
    return this->ui->designerArticle->text();
}

QString DialogAjouter::getfinitionEdit() const
{
    return this->ui->finition->text();
}

double DialogAjouter::getlongueurEdit() const
{
    return this->ui->longArticle->value();
}

double DialogAjouter::getlargeurEdit() const
{
    return this->ui->largArticle->value();
}

double DialogAjouter::getprofondeurEdit() const
{
    return this->ui->profArticle->value();
}

QPushButton* DialogAjouter::getboutonValider() const
{
    return this->ui->pushButtonValider;
}

QPushButton* DialogAjouter::getboutonAnnuler() const
{
    return this->ui->pushButtonAnnuler;
}
QString DialogAjouter::getcategorieEdit() const
{
    if (ui->categArt->currentIndex()!=-1)
        return this->ui->categArt->currentText();
    return "";
}
double DialogAjouter::getpoidsEdit() const
{
    return this->ui->poidArticle->value();
}

double DialogAjouter::getPrixEdit() const
{
    return this->ui->prixArticle->value();
}

unsigned int DialogAjouter::getdispoEdit() const
{
    return this->ui->prixArticle->value();
}
