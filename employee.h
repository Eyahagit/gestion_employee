#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

class Employee
{
public:
    // constructeur
    Employee();
    // constructeur parametre
    Employee(QString, QString, QString, QString);

    // getter setter
    int getID_E();
    void setName_E(QString val);
    QString getName_E();
    void setAddress_E(QString val);
    QString getAddress_E();
    void setContact_E(QString val);
    QString getContact_E();

    ///////////// CRUD Operations /////////////////
    bool add();
    bool update(int, QString, QString, QString, QString);
    bool remove(int id);
    QSqlQueryModel* display();
    QSqlQueryModel* trie_id();
    QSqlQueryModel* trie_nom();
    QSqlQueryModel* trie_contact();


private:
    int id_E;
    QString name_E;
    QString address_E;
    QString contact_E;
    QString genre;
};

#endif // EMPLOYEE_H
