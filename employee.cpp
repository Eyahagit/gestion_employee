#include "employee.h"
#include <QString>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QString>
// constructeur
Employee::Employee()
{
    name_E = "";
    address_E = "";
    contact_E = "";
}
// constructeur parametre
Employee::Employee(QString name_E, QString address_E, QString contact_E, QString genre)
{
    this->name_E = name_E;
    this->address_E = address_E;
    this->contact_E = contact_E;
    this->genre = genre;
}
// getter setter
int Employee::getID_E() { return id_E; }
void Employee::setName_E(QString val) { name_E = val; }
QString Employee::getName_E() { return name_E; }
void Employee::setAddress_E(QString val) { address_E = val; }
QString Employee::getAddress_E() { return address_E; }
void Employee::setContact_E(QString val) { contact_E = val; }
QString Employee::getContact_E() { return contact_E; }
// ajouter
// qurey yaani requeete hia eli tkoul lel base de edonne aamel tel chose
// aleh nestaamlou requette preparé ? khater bch nman3ou rwe7na men attack esmha sql injection
// binvalue t inseri valeur mel clavier lel requette
//query.exec() ->> execution

bool Employee::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Employee (name_E, address_E, contact_E,genre)"
                  "VALUES (:name_E, :address_E, :contact_E, :genre)");
    query.bindValue(":name_E", name_E);
    query.bindValue(":address_E", address_E);
    query.bindValue(":contact_E", contact_E);
    query.bindValue(":genre", genre);
    return query.exec();
}
// afficher
QSqlQueryModel* Employee::display()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Genre"));
    return model;
}
// afficher
QSqlQueryModel* Employee::trie_id()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee Order by id_E");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Genre"));
    return model;
}
// afficher
QSqlQueryModel* Employee::trie_nom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee Order by name_E");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Genre"));
    return model;
}
// afficher
QSqlQueryModel* Employee::trie_contact()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee Order by contact_E");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));
    return model;
}
// suprimer
bool Employee::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Employee WHERE id_E = :id");
    query.bindValue(":id", id);
    return query.exec();
}
// modifier
bool Employee::update(int id, QString name_E, QString address_E, QString contact_E, QString genre)
{
    QSqlQuery query;
    query.prepare("UPDATE Employee SET name_E = (?), address_E = (?), contact_E = (?) , genre = (?) WHERE id_E = (?)");
    query.addBindValue(name_E);
    query.addBindValue(address_E);
    query.addBindValue(contact_E);
    query.addBindValue(genre);
    query.addBindValue(id);
    return query.exec();
}
