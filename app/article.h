#ifndef ARTICLE_H
#define ARTICLE_H

#include<QList>
#include<QString>

class Attributs
{
private:
    QString finition;
    double prix;
    unsigned int disponible;

public:
    Attributs();
    Attributs(const Attributs&);
    Attributs(QString, double, unsigned int);
    ~Attributs();

    Attributs& operator=(const Attributs&);

    const QString& getFinition() const;
    const double& getPrix() const;
    const unsigned int& getDisponible() const;

    void setFinition(const QString&);
    void setPrix(const double&);
    void setDisponible(const unsigned int&);
};

class Article
{
private:
    QString categorie, nomArticle, photo, numArticle, descArticle, nomDesigner;
    double longueur, largeur, profondeur, poids;
    QVector<Attributs> attributs;

public:

    Article();
    Article(const Article&);
    Article(QString, QString, QString, QString, QString, QString, double, double, double, double);
    ~Article();

    Article& operator=(const Article&);

    void ajoutAttributs(const Attributs&);
    void ajoutAttributs(const QString, const double, const uint);

    const QString& getCategorie() const;
    const QString& getNomArticle() const;
    const QString& getPhoto() const;
    const QString& getNumArticle() const;
    const QString& getDescArticle() const;
    const QString& getNomDesigner() const;
    const double& getLongueurColis() const;
    const double& getLargeurColis() const;
    const double& getProfondeurColis() const;
    const double& getPoidsColis() const;
    const QVector<Attributs>& getAttributs() const;

    void setCategorie(const QString&);
    void setNomArticle(const QString&);
    void setPhoto(const QString&);
    void setNumArticle(const QString&);
    void setDescArticle(const QString&);
    void setNomDesigner(const QString&);
    void setLongueurColis(const double&);
    void setLargeurColis(const double&);
    void setProfondeurColis(const double&);
    void setPoidsColis(const double&);
    QVector<Attributs>& setAttributs();

    double getAttributsSize() const;
    friend QDebug operator<<(QDebug debug, const Article& article);
};

#endif // ARTICLE_H
