#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMessageBox>
#include <QVector>
#include <QPixmap>
#include <QAbstractButton>
#include <regex>
#include <QTranslator>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogajouter.h"

// constructeur de MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Hïkěà");

    ui->doubleSpinBox_dispo->setDecimals(0);

    ui->doubleSpinBox_longueur->setMinimum(0);
    ui->doubleSpinBox_largeur->setMinimum(0);
    ui->doubleSpinBox_profond->setMinimum(0);
    ui->doubleSpinBox_poids->setMinimum(0);
    ui->doubleSpinBox_prix->setMinimum(0);
    ui->doubleSpinBox_dispo->setMinimum(0);

    ui->doubleSpinBox_longueur->setMaximum(10000);
    ui->doubleSpinBox_largeur->setMaximum(10000);
    ui->doubleSpinBox_profond->setMaximum(10000);
    ui->doubleSpinBox_poids->setMaximum(10000);
    ui->doubleSpinBox_prix->setMaximum(1000000);
    ui->doubleSpinBox_dispo->setMaximum(1000000);

    ui->label_titre->setPixmap(QPixmap("../img/Hïkěà.png").scaledToHeight(107));
    ui->label_titre->show();

    this->nomFichier = "../data/data.json";

    categories.push_back("meuble");
    categories.push_back("decoration");
    categories.push_back("rangement");
    categories.push_back("literie");
    categories.push_back("cuisine");
    categories.push_back("eclairage");
    ui->comboBox_categorie->addItems(categories);
    ui->comboBox_categorie->addItem("tout");

    chargerFichier();

    aJour = true;

    connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(quitter()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));
    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(ui->liste_articles, SIGNAL(itemSelectionChanged()), this, SLOT(infoArticle()));
    connect(ui->actionCharger, SIGNAL(triggered()),this, SLOT(charger()));
    connect(ui->actionSauvegarder_Sous, SIGNAL(triggered()),this, SLOT(sauvegarderSous()));
    connect(ui->actionSauvegarder, SIGNAL(triggered()),this, SLOT(sauvegarder()));
    connect(ui->comboBox_finition, SIGNAL(currentIndexChanged(int)),this, SLOT(modifieFinition()));
    connect(ui->pushButton_recherche, SIGNAL(clicked()), this, SLOT(recherche()));
    connect(ui->lineEdit_recherche, SIGNAL(returnPressed()), this, SLOT(recherche()));
    connect(ui->comboBox_categorie, SIGNAL(currentIndexChanged(int)), this, SLOT(triCategorie()));
    connect(ui->pushButton_ajouter, SIGNAL(clicked()),this, SLOT(ajouter()));
    connect(ui->pushButton_supprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    connect(ui->pushButton_enregistrer, SIGNAL(clicked()),this, SLOT(enregistreArticle()));
    connect(ui->pushButton_annuler, SIGNAL(clicked()),this, SLOT(annuleModif()));
    connect(ui->actionNouveau, SIGNAL(triggered()),this, SLOT(nouveau()));
    connect(ui->pushButton_suppr_finition, SIGNAL(clicked()),this, SLOT(supprFinition()));
    connect(ui->actionEnglish, SIGNAL(triggered()),this, SLOT(anglais()));
    connect(ui->actionFrancais, SIGNAL(triggered()),this, SLOT(francais()));
}

// destructeur de MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::francais()
{
        qApp->removeTranslator(&translator);
        ui->retranslateUi(this);
    ui->label_titre->setPixmap(QPixmap("../img/Hïkěà.png").scaledToHeight(107));
    ui->label_titre->show();
}
void MainWindow::anglais()
{

    if (translator.load(":/i18n/hikea_en_US"))
    {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
    ui->label_titre->setPixmap(QPixmap("../img/Hïkěà.png").scaledToHeight(107));
    ui->label_titre->show();
}
// méthode qui gère la fenêtre à propos du menu supérieur
void MainWindow::aPropos()
{
    QMessageBox a_propos(this);
    a_propos.setWindowTitle(tr("A propos"));
    a_propos.setText(tr("Informations sur des articles Hïkěà.\n\nCe programme permet la consultation d'informations concernant des articles (mobilier). Les données des différents mobiliers sont conservées au format JSON.\n\npar HILAIRE Robin et MILLET Simon (c) 2023."));
    a_propos.exec();
}

void MainWindow::recherche()
{
    if (ui->lineEdit_recherche->text().size()!=0)
        foreach (const Article& a , articles){
            if (a.getNomArticle().indexOf(ui->lineEdit_recherche->text(), 0, Qt::CaseInsensitive)==-1 &&
                a.getDescArticle().indexOf(ui->lineEdit_recherche->text(), 0, Qt::CaseInsensitive)==-1 &&
                a.getNumArticle().indexOf(ui->lineEdit_recherche->text(), 0, Qt::CaseInsensitive)==-1 &&
                a.getPhoto().indexOf(ui->lineEdit_recherche->text(), 0, Qt::CaseInsensitive)==-1 &&
                a.getNomDesigner().indexOf(ui->lineEdit_recherche->text(), 0, Qt::CaseInsensitive)==-1 &&
                a.getCategorie().indexOf(ui->lineEdit_recherche->text(), 0, Qt::CaseInsensitive)==-1){
                foreach (const Attributs& at , a.getAttributs())
                    if (at.getFinition().indexOf(ui->lineEdit_recherche->text(), 0, Qt::CaseInsensitive)==-1){
                        QList<QListWidgetItem*> items = ui->liste_articles->findItems(a.getNomArticle()+" "+a.getNumArticle(), Qt::MatchExactly);
                        for (QListWidgetItem* i : items)
                            i->setHidden(true);
                    } else{
                        QList<QListWidgetItem*> items = ui->liste_articles->findItems(a.getNomArticle()+" "+a.getNumArticle(), Qt::MatchExactly);
                        for (QListWidgetItem* i : items)
                            if (ui->comboBox_categorie->currentText()=="tout" || ui->comboBox_categorie->currentIndex()==-1)
                                i->setHidden(false);
                            else
                                if (ui->comboBox_categorie->currentText()==a.getCategorie())
                                    i->setHidden(false);
                                else
                                    i->setHidden(true);
                        break;
                    }
            } else{
                QList<QListWidgetItem*> items = ui->liste_articles->findItems(a.getNomArticle()+" "+a.getNumArticle(), Qt::MatchExactly);
                for (QListWidgetItem* i : items)
                    if (ui->comboBox_categorie->currentText()=="tout" || ui->comboBox_categorie->currentIndex()==-1)
                        i->setHidden(false);
                    else
                        if (ui->comboBox_categorie->currentText()==a.getCategorie())
                                i->setHidden(false);
                        else
                                i->setHidden(true);
            }
        }
    else if (ui->lineEdit_recherche->text().size()==0)
        for (const Article& a : articles){
                QList<QListWidgetItem*> items = ui->liste_articles->findItems(a.getNomArticle()+" "+a.getNumArticle(), Qt::MatchExactly);
                for (QListWidgetItem* i : items)
                if (ui->comboBox_categorie->currentText()=="tout" || ui->comboBox_categorie->currentIndex()==-1)
                        i->setHidden(false);
                else
                        if (ui->comboBox_categorie->currentText()==a.getCategorie())
                                i->setHidden(false);
                        else
                                i->setHidden(true);
        }
}

void MainWindow::triCategorie()
{
    ui->lineEdit_recherche->clear();
    for (const Article& a : articles){
        if (ui->comboBox_categorie->currentText()=="tout"){
            QList<QListWidgetItem*> items = ui->liste_articles->findItems(a.getNomArticle()+" "+a.getNumArticle(), Qt::MatchExactly);
            for (QListWidgetItem* i : items)
                i->setHidden(false);
        } else{
            if (a.getCategorie().indexOf(ui->comboBox_categorie->currentText())==-1){
                QList<QListWidgetItem*> items = ui->liste_articles->findItems(a.getNomArticle()+" "+a.getNumArticle(), Qt::MatchExactly);
                for (QListWidgetItem* i : items)
                    i->setHidden(true);
            } else{
                QList<QListWidgetItem*> items = ui->liste_articles->findItems(a.getNomArticle()+" "+a.getNumArticle(), Qt::MatchExactly);
                for (QListWidgetItem* i : items)
                    i->setHidden(false);
            }
        }
    }
}

void MainWindow::enregistreArticle(){
    for (Article& c : articles)
        if (c.getNomArticle()==current.getNomArticle() && c.getNumArticle()==current.getNumArticle()){
            c.setCategorie(ui->comboBox_categorie_article->currentText());
            c.setDescArticle(ui->textEdit_desc->toPlainText());
            c.setLongueurColis(ui->doubleSpinBox_longueur->value());
            c.setLargeurColis(ui->doubleSpinBox_largeur->value());
            c.setProfondeurColis(ui->doubleSpinBox_profond->value());
            c.setPoidsColis(ui->doubleSpinBox_poids->value());
            c.setNomDesigner(ui->lineEdit_designer->text());
            if (ui->comboBox_finition->currentIndex()!=-1){
                for (Attributs& a : c.setAttributs())
                    if (a.getFinition()==ui->comboBox_finition->currentText()){
                        a.setFinition(ui->lineEdit_couleur->text());
                        a.setPrix(ui->doubleSpinBox_prix->value());
                        a.setDisponible(ui->doubleSpinBox_dispo->value());
                    }
            } else if (ui->comboBox_finition->currentIndex()==-1 && ui->lineEdit_couleur->text().size()!=0){
                c.ajoutAttributs(ui->lineEdit_couleur->text(), ui->doubleSpinBox_prix->value(), ui->doubleSpinBox_dispo->value());
                ui->comboBox_finition->addItem(ui->lineEdit_couleur->text());
                ui->comboBox_finition->setCurrentIndex(ui->comboBox_finition->findText(ui->lineEdit_couleur->text()));
            }
            aJour = false;
            infoArticle();
        }
}

void MainWindow::supprFinition()
{
    for (Article& c : articles)
        if (c.getNomArticle()==current.getNomArticle() && c.getNumArticle()==current.getNumArticle())
            if (ui->comboBox_finition->currentIndex()!=-1)
                for (int i=0; i<c.setAttributs().size(); ++i)
                    if (c.setAttributs()[i].getFinition()==ui->comboBox_finition->currentText()){
                        c.setAttributs().removeAt(i);
                        infoArticle();
                        aJour = false;
                    }
}

void MainWindow::annuleModif(){
    infoArticle();
}

void MainWindow::chargerFichier()
{
    ui->liste_articles->setCurrentItem(nullptr);

    QFile fichier(nomFichier);
    QString texteJson;

    if (fichier.open(QIODevice::ReadOnly))
    {
        texteJson = fichier.readAll();
        fichier.close();
    }

    QJsonDocument document = QJsonDocument::fromJson(texteJson.toUtf8());
    QJsonObject objetJSON = document.object();

    foreach (const QString& cate, categories) {
        for (QJsonValue o : objetJSON[cate].toArray()) {
            QJsonObject objet = o.toObject();
            Article article(cate, objet["nom_article"].toString(), objet["photo_article"].toString(),
                            objet["numero_article"].toString(), objet["description_article"].toString(),
                            objet["nom_designer"].toString(), objet["longueur_cm"].toDouble(),
                            objet["largeur_cm"].toDouble(), objet["profondeur_cm"].toDouble(), objet["poids_kg"].toDouble());

            for (QJsonValue attribut : objet["sous-formulaire"].toArray()) {
                article.ajoutAttributs(attribut["finition"].toString(), attribut["prix_euros"].toDouble(), attribut["nb_dispo"].toInt());
            }

            articles.append(article);
        }
    }
    ajouterArticlesListe();
}

// méthode qui charge un fichier JSON dont le chemin d'accès est _nomFichier
void MainWindow::charger()
{
    QFile fichier(this->nomFichier);

    ui->liste_articles->setCurrentItem(nullptr);

    this->nomFichier = QFileDialog::getOpenFileName(this, "Sélectionner un fichier JSON", "", "Fichier JSON (*.json)", new QString("yoyoyo"));
    if (nomFichier.isEmpty())
        return;

    articles.clear(); // Effacer les éléments de la liste articles
    ui->liste_articles->clear();

    chargerFichier();
}

void MainWindow::nouveau()
{
    QString nouveauNomFichier = QFileDialog::getSaveFileName(this, "Nouveau JSON", "", "Fichier JSON (*.json)");//Recupere le nom du fichier donnée dans un QDialog
    if (nouveauNomFichier.isEmpty())
    {
        QMessageBox* messageAlerte = new QMessageBox;
        messageAlerte->setText(tr("La création du fichier a été interrompue.\n\nCause: L'utilisateur a annulé la création."));//Permet de prevenir d'une erreur de l'utilisateur
        messageAlerte->exec();
        return;
    }
    else{
        nomFichier = nouveauNomFichier;
        articles.clear();
        ajouterArticlesListe();
        infoArticle();
        aJour = false;
    }
}

void MainWindow::ajouterArticlesListe()
{
    ui->liste_articles->clear();
    ui->label_nb_articles->setText(tr("Nombre total d'articles : ")+QString::number(articles.size()));
    for (int i = 0; i < articles.size(); i++) {
        const Article& a = articles.at(i);
        ui->liste_articles->addItem(a.getNomArticle() + " " + a.getNumArticle());
    }
}

bool MainWindow::formatNumArticleOK(const QString& expression) {
    std::regex pattern("^\\d{3}\\.\\d{3}\\.\\d{3}$");
    std::string strExpression = expression.toStdString();
    return std::regex_match(strExpression, pattern);
}

void MainWindow::ajouter()
{
    ajouterArticle = new DialogAjouter(this);

    QPushButton * valider=ajouterArticle->getboutonValider();
    QPushButton * annuler=ajouterArticle->getboutonAnnuler();

    connect(valider, SIGNAL(clicked()), this, SLOT(validerCliquer()));
    connect(annuler, SIGNAL(clicked()), this, SLOT(annulerCliquer()));

    ajouterArticle->exec();

}

void MainWindow::validerCliquer()
{
    for (const Article& a : articles)
        if (a.getNomArticle()==ajouterArticle->getNomArticleEdit() || a.getNumArticle()==ajouterArticle->getnumArticleEdit()){
            QMessageBox a_propos(this);
            a_propos.setWindowTitle(tr("Erreur"));
            a_propos.setText(tr("Abandon de la création d'article.\nLe nom ou le numéro d'article est celui d'un article déjà existant. Les articles doivent avoir des noms et numéros distincts."));
            a_propos.exec();
            return;
        }
    if (!formatNumArticleOK(ajouterArticle->getnumArticleEdit())){
        QMessageBox a_propos(this);
        a_propos.setWindowTitle(tr("Erreur"));
        a_propos.setText(tr("Abandon de la création d'article.\nLe numéro d'article est incorrect. Celui-ci doit être au format \"000.000.000\", aucun autre format n'est accepté."));
        a_propos.exec();
        return;
    } else if (ajouterArticle->getcategorieEdit()==""){
        QMessageBox a_propos(this);
        a_propos.setWindowTitle(tr("Erreur"));
        a_propos.setText(tr("Abandon de la création d'article.\nVeuillez sélectionner une catégorie."));
        a_propos.exec();
        return;
    } else{
        QString _nomArticle=ajouterArticle->getNomArticleEdit();
        QString _categorieArticle=ajouterArticle->getcategorieEdit();
        QString _numArticle=ajouterArticle->getnumArticleEdit();
        QString _descArticle=ajouterArticle->getdescArticleEdit();
        QString _nomDesigner=ajouterArticle->getnomDesignerEdit();
        QString _finition=ajouterArticle->getfinitionEdit();
        QString _nomPhoto=ajouterArticle->getnomPhotoEdit();
        double _longueur=ajouterArticle->getlongueurEdit();
        double _largeur=ajouterArticle->getlargeurEdit();
        double _profondeur=ajouterArticle->getprofondeurEdit();
        double _poids=ajouterArticle->getpoidsEdit();
        double _prix=ajouterArticle->getPrixEdit();
        unsigned int _dispo=ajouterArticle->getdispoEdit();
        Article _article(_categorieArticle, _nomArticle, _nomPhoto, _numArticle, _descArticle, _nomDesigner, _longueur, _largeur, _profondeur, _poids);
        _article.ajoutAttributs(_finition, _prix, _dispo);
        articles.push_back(_article);
        ajouterArticlesListe();
        aJour = false;
        ajouterArticle->accept();
        delete ajouterArticle;
    }
}
void MainWindow::annulerCliquer()
{
    ajouterArticle->reject();
    delete ajouterArticle;
}
void MainWindow::supprimer()
{
    if (ui->liste_articles->selectedItems().size()!=0){
        QMessageBox a_propos(this);
        a_propos.setWindowTitle(tr("Supprimer"));
        a_propos.setText(tr("Êtes-vous vraiment sûr de vouloir supprimer l'élément \"")+ui->liste_articles->selectedItems()[0]->text()+"\" ?");
        QAbstractButton *bSupprimer = a_propos.addButton(tr("Supprimer"), QMessageBox::AcceptRole);
        QAbstractButton *bAnnuler = a_propos.addButton(tr("Annuler"), QMessageBox::RejectRole);
        a_propos.exec();

        if (a_propos.clickedButton() == bSupprimer){
            QString nomObjet = ui->liste_articles->selectedItems()[0]->text();
            QStringList listeNomObjet = nomObjet.split(" ");
            for (int i=0; i<articles.size(); ++i)
                if (articles[i].getNomArticle()==listeNomObjet[0] && articles[i].getNumArticle()==listeNomObjet[1])
                    articles.removeAt(i);
            ajouterArticlesListe();
            aJour = false;
        } else if (a_propos.clickedButton() == bAnnuler)
            return;
    }
}

void MainWindow::infoArticle()
{
    ui->comboBox_finition->clear();

    QList<QListWidgetItem*> selectedItems = ui->liste_articles->selectedItems();
    if (selectedItems.isEmpty()){
        ui->label_nom_article->setText("(Nom d'article)");
        ui->label_photo->clear();
        ui->label_numero_contenu->clear();
        ui->textEdit_desc->clear();
        ui->doubleSpinBox_longueur->setValue(0);
        ui->doubleSpinBox_largeur->setValue(0);
        ui->doubleSpinBox_profond->setValue(0);
        ui->doubleSpinBox_poids->setValue(0);
        ui->lineEdit_designer->clear();
        ui->comboBox_categorie_article->clear();
        ui->comboBox_finition->clear();
        ui->label_photo->clear();
    } else{
        ui->comboBox_categorie_article->addItems(categories);

        QString article = selectedItems[0]->text();
        QStringList idArticle = article.split(" ");

        foreach (const Article& a , articles)
        {
            if (a.getNomArticle()==idArticle[0] && a.getNumArticle()==idArticle[1])
                current = a;
        }
        ui->label_nom_article->setText(current.getNomArticle());
        ui->label_photo->setText(current.getPhoto());
        ui->label_numero_contenu->setText(current.getNumArticle());
        ui->textEdit_desc->setText(current.getDescArticle());
        ui->doubleSpinBox_longueur->setValue(current.getLongueurColis());
        ui->doubleSpinBox_largeur->setValue(current.getLargeurColis());
        ui->doubleSpinBox_profond->setValue(current.getProfondeurColis());
        ui->doubleSpinBox_poids->setValue(current.getPoidsColis());
        ui->lineEdit_designer->setText(current.getNomDesigner());
        ui->comboBox_categorie_article->setCurrentIndex(ui->comboBox_categorie_article->findText(current.getCategorie()));

        for (const Attributs& a : current.getAttributs())
            ui->comboBox_finition->addItem(a.getFinition());

        QStringList listeNomPhoto = nomFichier.split("/");
        QString nomPhoto = current.getPhoto();
        for (int i=listeNomPhoto.size()-2; i>=0; --i)
            nomPhoto = listeNomPhoto[i] + "/" + nomPhoto;
        ui->label_photo->setPixmap(QPixmap(nomPhoto).scaledToHeight(300));
        ui->label_photo->show();
    }
}

void MainWindow::modifieFinition()
{
    if (ui->comboBox_finition->currentIndex()==-1){
        ui->lineEdit_couleur->setText("");
        ui->doubleSpinBox_prix->setValue(0);
        ui->doubleSpinBox_dispo->setValue(0);
    } else{
        Attributs currentAttributs;
        for (const Attributs& a : current.getAttributs())
            if (a.getFinition()==ui->comboBox_finition->currentText())
                currentAttributs = a;
        ui->lineEdit_couleur->setText(currentAttributs.getFinition());
        ui->doubleSpinBox_prix->setValue(currentAttributs.getPrix());
        ui->doubleSpinBox_dispo->setValue(currentAttributs.getDisponible());
    }
}

// méthode qui sauvegarde un fichier en .json
void MainWindow::sauvegarder()
{
    sauvegarderJSON(nomFichier);//Fais appel a la fonction pour sauvegarder le fichier
}

//méthode qui sauvegarde un fichier en .json dans un autre répertoire
void MainWindow::sauvegarderSous()
{
    QString nouveauNomFichier = QFileDialog::getSaveFileName(this, "Sauvegarder sous", "", "Fichier JSON (*.json)");//Recupere le nom du fichier donnée dans un QDialog
    if (nouveauNomFichier.isEmpty())
    {
        QMessageBox* messageAlerte = new QMessageBox;
        messageAlerte->setText(tr("La sauvegarde du fichier a été interrompue.\n\nCause: L'utilisateur a annulé la sauvegarde."));//Permet de prevenir d'une erreur de l'utilisateur
        messageAlerte->exec();
        return;
    }
    else
        sauvegarderJSON(nouveauNomFichier);
}
void MainWindow::sauvegarderJSON(QString _fichierNom)
{
    QJsonObject objetJSON;

    // Parcours des articles pour créer un objet JSON contenant leurs attributs
    foreach (const Article& article, articles)
    {
        QJsonObject articleObjet;
        articleObjet["nom_article"] = article.getNomArticle();
        articleObjet["description_article"] = article.getDescArticle();
        articleObjet["photo_article"] = article.getPhoto();
        articleObjet["numero_article"] = article.getNumArticle();
        articleObjet["longueur_cm"] = article.getLongueurColis();
        articleObjet["largeur_cm"] = article.getLargeurColis();
        articleObjet["profondeur_cm"] = article.getProfondeurColis();
        articleObjet["poids_kg"] = article.getPoidsColis();
        articleObjet["nom_designer"] = article.getNomDesigner();

        QJsonArray attributsArray; //Liste des attributs de chaque article
        foreach (const Attributs& attribut, article.getAttributs())
        {
            QJsonObject attributObjet;
            attributObjet["finition"] = attribut.getFinition();
            attributObjet["prix_euros"] = attribut.getPrix();
            attributObjet["nb_dispo"] = double(attribut.getDisponible());
            attributsArray.append(attributObjet);
        }
        articleObjet["sous-formulaire"] = attributsArray;//Associe un sous_formulaire à chaque article

        QString categorie = article.getCategorie();//Recupere le nom de la categorie de l'article
        if (!objetJSON.contains(categorie))//Si aucune objet Json ne contient la catégorie alors..
        {
            QJsonArray categorieArray; // crée un tableau de categorie
            objetJSON[categorie] = categorieArray;//crée un objet JSON pour la catégorie
        }

        QJsonArray categorieArray = objetJSON[categorie].toArray(); //Crée un tableau JSON pour la catégorie
        categorieArray.append(articleObjet); // Ajoute l'article à la catégorie correspondante
        objetJSON[categorie] = categorieArray;//ecris dans le JSON toutes les catégories
    }

    //Permet de crée le fichier JSON
    QJsonDocument document(objetJSON);
    QString texteJson = document.toJson();

    QFile fichier(_fichierNom);
    if (fichier.open(QIODevice::WriteOnly))
    {
        fichier.write(texteJson.toUtf8());
        fichier.close();

        nomFichier = _fichierNom;
        aJour = true;

    }
}

void MainWindow::quitter()
{
    if (!aJour){
        QMessageBox a_propos(this);
        a_propos.setWindowTitle(tr("Supprimer"));
        a_propos.setText(tr("Des données ne sont actuellement pas sauvegardées.\nÊtes-vous vraiment sûr de vouloir quitter l'application sans sauvegarder ?\nQuitter ce message vous fera quitter sans sauvegarder aucunes données."));
        QAbstractButton *bSauvegarder = a_propos.addButton(tr("Sauvegarder"), QMessageBox::AcceptRole);
        QAbstractButton *bQuitter = a_propos.addButton(tr("Quitter"), QMessageBox::RejectRole);
        a_propos.exec();

        if (a_propos.clickedButton() == bSauvegarder){
            sauvegarderJSON(nomFichier);
            qApp->quit();
        }
        else if (a_propos.clickedButton() == bQuitter)
            qApp->quit();
        else
            qApp->quit();
    } else
        qApp->quit();
}
