#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDateTime>

class Project
{
public:
    enum ProjectType
    {
        ARTICLE = 1,
        BOOK,
        TOPIC,
        NONE
    };

public:
    Project(int projectId,
            ProjectType projectType,
            const QString& name,
            const QString& url,
            const QString& source,
            const QString& author,
            const QDateTime& created,
            const QDateTime& updated,
            const QStringList& tags);

    Project();

    int id()const;
    ProjectType projectType()const;
    QString name()const;
    QString url()const;
    QString source()const;
    QString author()const;
    QDateTime created()const;
    QDateTime updated()const;
    QStringList tags()const;
    bool valid()const;

private:
    ProjectType _projectType;
    int         _projectId;

    QString     _name;
    QString     _url;
    QString     _source;
    QString     _author;

    QDateTime   _created;
    QDateTime   _updated;

    QStringList _tags;
    bool _valid;
};

#endif // PROJECT_H
