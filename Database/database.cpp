#include "database.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

#include "Tables/projectstable.h"

Database::Database()
{

}


bool Database::init(const QString& dbName)
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
    {
        QMessageBox::critical(NULL, "Unable to load database", "This app needs the SQLITE driver");
        qDebug() << "Unable to load database, this app needs the SQLITE driver";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open())
    {
        qDebug() << "Unable to open db, error - " << db.lastError();
        return false;
    }
}

bool Database::createTables()
{
    if(!ProjectsTable::createTable())
        return false;

    return true;
}

bool Database::close()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen())
    {
        db.close();
    }
    else
    {
        return false;
    }

    return true;
}




