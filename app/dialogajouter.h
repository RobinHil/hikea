#ifndef DIALOGAJOUTER_H
#define DIALOGAJOUTER_H

#include <QDialog>

namespace Ui {
class DialogAjouter;
}

class DialogAjouter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjouter(QWidget *parent = nullptr);
    ~DialogAjouter();
    QString getNomArticleEdit() const;
    QString getnumArticleEdit() const;
    QString getdescArticleEdit() const;
    QString getnomDesignerEdit() const;
    QString getfinitionEdit() const;
    QString getnomPhotoEdit() const;
    QString getcategorieEdit() const;
    double getlongueurEdit() const;
    double getlargeurEdit() const;
    double getprofondeurEdit() const;
    double getpoidsEdit() const;
    double getPrixEdit() const;
    unsigned int getdispoEdit() const;
    QPushButton* getboutonValider() const;
    QPushButton* getboutonAnnuler() const;


private:
    Ui::DialogAjouter *ui;
    QVector<QString> categories;
};

#endif // DIALOGAJOUTER_H
