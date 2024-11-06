#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(e.display());
    //input__control control saisie
        ui->contact->setValidator(new QIntValidator(0,999999,this));
        ui->contact_2->setValidator(new QIntValidator(0,999999,this));
        ui->id->setValidator(new QIntValidator(0,999999,this));
        ui->id2->setValidator(new QIntValidator(0,999999,this));
        QRegularExpression rx("[a-zA-Z]+");
        QValidator *validator = new QRegularExpressionValidator(rx, this);
        ui->nom->setValidator(validator);
        ui->nom_2->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// ajout
void MainWindow::on_pushButton_clicked()
{
    QString nom =ui->nom->text();
    QString adresse =ui->adresse->text();
    QString contact =ui->contact->text();
    // constructeur
    Employee e(nom,adresse,contact);
    bool test=e.add();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajoute \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->nom->clear();
        ui->contact->clear();
        ui->adresse->clear();
        ui->tableView->setModel(e.display());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);
}
//modifier
void MainWindow::on_pushButton_2_clicked()
{
    int id =ui->id->text().toUInt();
    QString nom =ui->nom_2->text();
    QString adresse =ui->adresse_2->text();
    QString contact =ui->contact_2->text();
    bool test=e.update(id ,nom,adresse,contact);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("modifié \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->nom_2->clear();
        ui->adresse_2->clear();
        ui->adresse_2->clear();
        ui->contact_2->clear();
        ui->tableView->setModel(e.display());
    }
else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("modification non effectué"),QMessageBox::Cancel);
}
//supprimer
void MainWindow::on_pushButton_3_clicked()
{
    int id =ui->id2->text().toUInt();
    bool test=e.remove(id);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Supprimé \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->id2->clear();
        ui->tableView->setModel(e.display());
    }
    else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("suppression non effectué"),QMessageBox::Cancel);
}
// remplissage auto
void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from employee  where id_E='"+val+"' or name_E='"+val+"' or address_E='"+val+"' or contact_E='"+val+"' or contact_E='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->id->setText(qry.value(0).toString());
            ui->nom_2->setText(qry.value(1).toString());
            ui->adresse_2->setText(qry.value(2).toString());
            ui->contact_2->setText(qry.value(3).toString());
            //delete
            //id
            ui->id2->setText(qry.value(0).toString());
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableView->setModel(e.display());
}

