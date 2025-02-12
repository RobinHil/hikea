#include <QDebug>

#include "article.h"

Attributs::Attributs()
    : finition(""), prix(-1), disponible(-1)
{}

// constructeur de Attributs
Attributs::Attributs(QString _finition, double _prix, unsigned int _disponible)
    : finition(_finition), prix(_prix), disponible(_disponible)
{}

// constructeur de copie de Attributs
Attributs::Attributs(const Attributs& _Attributs)
    : finition(_Attributs.finition), prix(_Attributs.prix), disponible(_Attributs.disponible)
{}

// destructeur de Attributs
Attributs::~Attributs()
{}

// operateur d'affectation de Attributs
Attributs& Attributs::operator=(const Attributs& src)
{
    finition = src.finition;
    prix = src.prix;
    disponible = src.disponible;
    return *this;
}

const QString& Attributs::getFinition() const
{return finition;}

const double& Attributs::getPrix() const
{return prix;}

const unsigned int& Attributs::getDisponible() const
{return disponible;}

void Attributs::setFinition(const QString& val)
{finition = val;}

void Attributs::setPrix(const double& val)
{prix = val;}

void Attributs::setDisponible(const unsigned int& val)
{disponible = val;}

// constructeur pas défaut de Article
Article::Article()
    : categorie(""), nomArticle(""), photo(""),
    numArticle(""), descArticle(""), nomDesigner(""),
    longueur(-1), largeur(-1), profondeur(-1), poids(-1), attributs(QVector<Attributs>())
{}

// constructeur de Article
Article::Article(QString _categorie, QString _nomArticle, QString _photo,
                 QString _numArticle, QString _descArticle, QString _nomDesigner,
                 double _longueur, double _largeur, double _profondeur, double _poids)
    : categorie(_categorie), nomArticle(_nomArticle), photo(_photo),
    numArticle(_numArticle), descArticle(_descArticle), nomDesigner(_nomDesigner),
    longueur(_longueur), largeur(_largeur), profondeur(_profondeur), poids(_poids), attributs(QList<Attributs>())
{}

// constructeur de copie de Article
Article::Article(const Article& _Article)
    : categorie(_Article.getCategorie()), nomArticle(_Article.nomArticle), photo(_Article.photo),
    numArticle(_Article.numArticle), descArticle(_Article.descArticle), nomDesigner(_Article.nomDesigner),
    longueur(_Article.longueur), largeur(_Article.largeur), profondeur(_Article.profondeur), poids(_Article.poids),
    attributs(_Article.attributs)
{}

// destructeur de Article
Article::~Article()
{}

// opérateur d'affectation de Article
Article& Article::operator=(const Article& src)
{
    categorie = src.categorie;
    nomArticle = src.nomArticle;
    photo = src.photo;
    numArticle = src.numArticle;
    descArticle = src.descArticle;
    nomDesigner = src.nomDesigner;
    longueur = src.longueur;
    largeur = src.largeur;
    profondeur = src.profondeur;
    poids = src.poids;
    attributs = src.attributs;
    return *this;
}

// méthode qui crée une instance de Attributs puis l'ajoute dans la donnée membre attributs de Article
void Article::ajoutAttributs(const QString _finition, const double _prix, const uint _disponible)
{
    Attributs att(_finition, _prix, _disponible);
    attributs.push_back(att);
}

const QString& Article::getCategorie() const
{return categorie;}

// méthode qui renvoie le nom d'article
const QString& Article::getNomArticle() const
{return nomArticle;}

const QString& Article::getPhoto() const
{return photo;}

// méthode qui renvoie le numéro d'article
const QString& Article::getNumArticle() const
{return numArticle;}

const QString& Article::getDescArticle() const
{return descArticle;}

const QString& Article::getNomDesigner() const
{return nomDesigner;}

const double& Article::getLongueurColis() const
{return longueur;}

const double& Article::getLargeurColis() const
{return largeur;}

const double& Article::getProfondeurColis() const
{return profondeur;}

const double& Article::getPoidsColis() const
{return poids;}

double Article::getAttributsSize() const
{return attributs.size();}

const QVector<Attributs>& Article::getAttributs() const
{return attributs;}

void Article::setCategorie(const QString& val)
{categorie = val;}

void Article::setNomArticle(const QString& val)
{nomArticle = val;}

void Article::setPhoto(const QString& val)
{photo = val;}

void Article::setNumArticle(const QString& val)
{numArticle = val;}

void Article::setDescArticle(const QString& val)
{descArticle = val;}

void Article::setNomDesigner(const QString& val)
{nomDesigner = val;}

void Article::setLongueurColis(const double& val)
{longueur = val;}

void Article::setLargeurColis(const double& val)
{largeur = val;}

void Article::setProfondeurColis(const double& val)
{profondeur = val;}

void Article::setPoidsColis(const double& val)
{poids = val;}

QVector<Attributs>& Article::setAttributs()
{return attributs;}

QDebug operator<<(QDebug debug, const Article& article)
{
    debug << "Article("
          << "catégorie:" << article.getCategorie()
          << ", nom:" << article.getNomArticle()
          << ", photo:" << article.getPhoto()
          << ", numéro:" << article.getNumArticle()
          << ", description:" << article.getDescArticle()
          << ", designer:" << article.getNomDesigner()
          << ", longueur:" << article.getLongueurColis()
          << ", largeur:" << article.getLargeurColis()
          << ", profondeur:" << article.getProfondeurColis()
          << ", poids:" << article.getPoidsColis()
          << ", attributs taille:" << article.getAttributsSize()
          << ")";
    return debug;
}
