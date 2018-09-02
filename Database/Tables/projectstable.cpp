#include "projectstable.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

/***************************************************************************************/
bool ProjectsTable::createTable()
{
    QSqlDatabase db = QSqlDatabase::database();
    QStringList tables = db.tables();
    if(tables.contains(QString("projects")))
    {
        qDebug() << "projects table already exists";
        return true;
    }

    QSqlQuery q;
    if(q.exec(QString("CREATE table projects "
                      "("
                      "id integer primary key,"
                      "projectType integer"
                      "name varchar,"
                      "url varchar,"
                      "source varchar,"
                      "author varchar"
                      "created TIMESTAMP,"
                      "updated TIMESTAMP,"
                      "tags varchar"
                      ")")))
    {
        return true;
    }
    else
    {
        qDebug() << q.lastError().text();
        return false;
    }

    return false;
}

/***************************************************************************************/
Project ProjectsTable::create(const QString&name, const QString& url, const QString& source, const QString& author,
                              const Project::ProjectType& projectType, const QStringList& tags)
{
    QSqlQuery q;
    if(q.prepare(QString("insert into projects (projectType, name, url, source, author, created, updated, tags) values(?,?,?,?,?,?,?,?)")))
    {
        QDateTime created = QDateTime::currentDateTimeUtc();
        QDateTime updated = QDateTime::currentDateTimeUtc();
        QString tagsString = (tags.isEmpty()) ?  QString("") : tags.join(",");

        q.addBindValue(projectType);
        q.addBindValue(name);
        q.addBindValue(url);
        q.addBindValue(source);
        q.addBindValue(author);
        q.addBindValue(created);
        q.addBindValue(updated);
        q.addBindValue(tagsString);

        if(q.exec())
        {
            return Project(q.lastInsertId().toInt(),
                           projectType,
                           name,
                           url,
                           source,
                           author,
                           created,
                           updated,
                           tags);
        }
        else
        {
            qDebug << QString("ProjectsTable::create failed, error - ") << q.lastError().text();
            return Project();
        }
    }
    else
    {
        qDebug << QString("ProjectsTable::create failed, error - ") << q.lastError().text();
        return Project();
    }

    return Project();
}

/***************************************************************************************/
Project ProjectsTable::getByName(const QString& name)
{
    QSqlQuery q;
    if(q.exec(QString("SELECT * from projects where name = \"%1\"").arg(name)))
    {
        if(q.next())
        {
            QStringList tags = q.value(8).toString().split(",");
            return Project(q.value(0).toInt(),
                           q.value(1).toInt(),
                           q.value(2).toString(),
                           q.value(3).toString(),
                           q.value(4).toString(),
                           q.value(5).toString(),
                           q.value(6).toDateTime(),
                           q.value(7).toDateTime(),
                           tags);
        }
        else
        {
            qDebug << QString("ProjectsTable::getByName failed, error - ") << q.lastError().text();
            return Project();
        }
    }
    else
    {
        qDebug << QString("ProjectsTable::getByName failed, error - ") << q.lastError().text();
        return Project();
    }

    return Project();
}

/***************************************************************************************/
Project ProjectsTable::getByUrl(const QString& url)
{
    QSqlQuery q;
    if(q.exec(QString("SELECT * from projects where url = \"%1\"").arg(url)))
    {
        if(q.next())
        {
            QStringList tags = q.value(8).toString().split(",");
            return Project(q.value(0).toInt(),
                           q.value(1).toInt(),
                           q.value(2).toString(),
                           q.value(3).toString(),
                           q.value(4).toString(),
                           q.value(5).toString(),
                           q.value(6).toDateTime(),
                           q.value(7).toDateTime(),
                           tags);
        }
        else
        {
            qDebug << QString("ProjectsTable::getByUrl failed, error - ") << q.lastError().text();
            return Project();
        }
    }
    else
    {
        qDebug << QString("ProjectsTable::getByUrl failed, error - ") << q.lastError().text();
        return Project();
    }

    return Project();
}

/***************************************************************************************/
QList<Project> ProjectsTable::getAll()
{
    QList<Project> projects;
    QSqlQuery q;
    if(q.exec(QString("SELECT * from projects")))
    {
        while(q.next())
        {
            QStringList tags = q.value(8).toString().split(",");
            Project project(q.value(0).toInt(),
                            q.value(1).toInt(),
                            q.value(2).toString(),
                            q.value(3).toString(),
                            q.value(4).toString(),
                            q.value(5).toString(),
                            q.value(6).toDateTime(),
                            q.value(7).toDateTime(),
                            tags);

            projects.push_back(project);
        }

        return projects;
    }
    else
    {
        qDebug << QString("ProjectsTable::getAll failed, error - ") << q.lastError().text();
        return projects;
    }

    return projects;
}

/***************************************************************************************/
bool ProjectsTable::update(const Project& project)
{
    if(!project.valid())
    {
        qDebug << QString("ProjectsTable::update failed, error - project is not valid");
        return false;
    }

    QSqlQuery q;
    if(q.prepare(QString("UPDATE projects SET projectType=?,name=?,url=?,source=?,author=?,created=?,updated=?,tags=? where id =?")))
    {
        q.addBindValue(static_cast<int>(project.projectType()));
        q.addBindValue(project.name());
        q.addBindValue(project.url());
        q.addBindValue(project.source());
        q.addBindValue(project.author());
        q.addBindValue(project.created());
        q.addBindValue(project.updated());
        q.addBindValue(project.tags().isEmpty() ? QString("") : project.tags().join(","));
        q.addBindValue(project.id());

        if(q.exec())
        {
            return true;
        }
        else
        {
            qDebug << QString("ProjectsTable::update failed, error - ") << q.lastError().text();
            return false;
        }
    }
    else
    {
        qDebug << QString("ProjectsTable::update failed, error - ") << q.lastError().text();
        return false;
    }

    return false;
}

/***************************************************************************************/
bool ProjectsTable::remove(const Project& project)
{
    QSqlQuery q;
    if(q.exec(QString("DELETE from projects where id = %1").arg(project.id())))
    {
        return true;
    }
    else
    {
        qDebug << QString("ProjectsTable::remove failed, error - ") << q.lastError().text();
        return false;
    }

    return false;
}

/***************************************************************************************/
bool ProjectsTable::removeAll()
{
    QSqlQuery q;
    if(q.exec(QString("DELETE from projects")))
    {
        return true;
    }
    else
    {
        qDebug << QString("ProjectsTable::removeAll failed, error - ") << q.lastError().text();
        return false;
    }

    return false;
}

