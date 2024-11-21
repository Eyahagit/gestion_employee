#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include<QSystemTrayIcon>
#include <QFileDialog>
#include <QPainter>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtCore>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QUrl>
#include <QPixmap>
#include "qrcode.h"

using namespace qrcodegen;
using namespace std;

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
    QString genre =ui->comboBox->currentText();
    // constructeur
    Employee e(nom,adresse,contact,genre);
    bool test=e.add();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajoute \n"
                                             "click to cancel"), QMessageBox::Cancel);
        sender.sendSms("+21656503211", "employee ajouter avec succes!");
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
    QString genre =ui->comboBox_2->currentText();
    bool test=e.update(id ,nom,adresse,contact,genre);
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
// trie id
void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView->setModel(e.trie_id());
}
// trie nom
void MainWindow::on_pushButton_6_clicked()
{
    ui->tableView->setModel(e.trie_nom());
}
// trie contact
void MainWindow::on_pushButton_7_clicked()
{
    ui->tableView->setModel(e.trie_contact());
}
// recherche
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT * FROM Employee WHERE id_E  LIKE'"+arg1+"%' or name_E  LIKE'"+arg1+"%' or address_E  LIKE'"+arg1+"%' or contact_E LIKE'"+arg1+"%'");
             query->exec();
             if (query->next()) {
             model->setQuery(*query);
             ui->tableView->setModel(model);
             }
             else {
                 QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                                 QObject::tr("NO MATCH FOUND !!\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
              ui->lineEdit->clear();}
}
//pdf
void MainWindow::on_pushButton_8_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
        qDebug()<<dir;
        QPdfWriter pdf(dir+"/PdfList.pdf");
                               QPainter painter(&pdf);
                              int i = 4000;

                                   painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/"));
                                   painter.drawText(900,650,"Gestion Employee");
                                   painter.setPen(Qt::red);
                                   painter.setFont(QFont("Time New Roman", 25));
                                   painter.drawText(3000,1400,"Liste des Employees");
                                   painter.setPen(Qt::black);
                                   painter.setFont(QFont("Time New Roman", 15));
                                   painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                   painter.drawRect(100,3000,9400,500);
                                   painter.setFont(QFont("Time New Roman", 9));
                                   painter.drawText(300,3300,"ID");
                                   painter.drawText(2000,3300,"Nom");
                                   painter.drawText(4000,3300,"Adresse");
                                   painter.drawText(5600,3300,"Contact");
                                   painter.drawRect(100,3000,9400,10700);
                                   //QTextDocument previewDoc;
                                   QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                   //QTextCursor cursor(&previewDoc);
                                   QSqlQuery query;
                                   query.prepare("select * from Employee");
                                   query.exec();
                                   while (query.next())
                                   {
                                       painter.drawText(300,i,query.value(0).toString());
                                       painter.drawText(2000,i,query.value(1).toString());
                                       painter.drawText(4000,i,query.value(2).toString());
                                       painter.drawText(5600,i,query.value(3).toString());
                                      i = i +500;
                                   }
                                   int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                       QMessageBox::Yes|QMessageBox::No);
                                       if (reponse == QMessageBox::Yes)
                                       {
                                           QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                           painter.end();
                                       }
                                       else
                                       {
                                            painter.end();
                                       }
}
//stats
void MainWindow::on_pushButton_9_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                        model->setQuery("select * from Employee where genre = 'Homme' ");
                                        float e=model->rowCount();
                                        model->setQuery("select * from Employee where genre = 'Femme' ");
                                        float ee=model->rowCount();
                                        float total=e+ee;
                                        QString a=QString("homme"+QString::number((e*100)/total,'f',2)+"%" );
                                        QString b=QString("femme"+QString::number((ee*100)/total,'f',2)+"%" );
                                        QPieSeries *series = new QPieSeries();
                                        series->append(a,e);
                                        series->append(b,ee);
                                if (e!=0)
                                {QPieSlice *slice = series->slices().at(0);
                                 slice->setLabelVisible();
                                 slice->setPen(QPen());}
                                if ( ee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice1 = series->slices().at(1);
                                         //slice1->setExploded();
                                         slice1->setLabelVisible();
                                }
                                        // Create the chart widget
                                        QChart *chart = new QChart();
                                        // Add data to chart with title and hide legend
                                        chart->addSeries(series);
                                        chart->setTitle("Pourcentage des homme et femme : nombre total des employee: "+ QString::number(total));
                                        chart->legend()->hide();
                                        // Used to display the chart
                                        QChartView *chartView = new QChartView(chart);
                                        chartView->setRenderHint(QPainter::Antialiasing);
                                        chartView->resize(1000,500);
                                        chartView->show();
}
// code qr
void MainWindow::on_pushButton_4_clicked()
{
    int tabeq=ui->tableView->currentIndex().row();
                  QVariant idd=ui->tableView->model()->data(ui->tableView->model()->index(tabeq,0));
                  QString id=idd.toString();
                 // QString code=idd.toSTring();
                  QSqlQuery qry;
                  qry.prepare("select * from Employee where id_E =:code");
                  qry.bindValue(":code",id);
                  qry.exec();

                   QString nom,adresse,contact;//attributs

                 while(qry.next()){

                     id=qry.value(0).toString();
                      nom=qry.value(1).toString();
                       adresse=qry.value(2).toString();
                      contact=qry.value(3).toString();
                  }
                  id=QString(id);
                         id="ID:\t" +id+ "NOM\t:" +nom+ "Adresse:\t" +adresse+ "contact:\t" +contact;
                  QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

                  // Read the black & white pixels
                  QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                  for (int y = 0; y < qr.getSize(); y++) {
                      for (int x = 0; x < qr.getSize(); x++) {
                          int color = qr.getModule(x, y);  // 0 for white, 1 for black

                          // You need to modify this part
                          if(color==0)
                              im.setPixel(x, y,qRgb(254, 254, 254));
                          else
                              im.setPixel(x, y,qRgb(0, 0, 0));
                      }
                  }
                  im=im.scaled(200,200);
                 ui->label_11->setPixmap(QPixmap::fromImage(im));
}

