#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

#include "article.h"
#include "dialogajouter.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString nomFichier;
    QVector<Article> articles;
    QVector<QString> categories;
    Article current;
    bool aJour;
    bool formatNumArticleOK(const QString&);
    DialogAjouter * ajouterArticle;
    QString ouvrir();
    void chargerFichier();
    void ajouterArticlesListe();
    void sauvegarderJSON(QString _nomFichier);
    QTranslator translator;
private slots:
    void validerCliquer();
    void annulerCliquer();
    void aPropos();
    void sauvegarder();
    void infoArticle();
    void charger();
    void sauvegarderSous();
    void modifieFinition();
    void recherche();
    void triCategorie();
    void ajouter();
    void enregistreArticle();
    void annuleModif();
    void supprimer();
    void nouveau();
    void quitter();
    void supprFinition();
    void anglais();
    void francais();
};

#endif // MAINWINDOW_H
