#include "project.h"

Project::Project(int projectId,
                 ProjectType projectType,
                 const QString &name,
                 const QString &url,
                 const QString &source,
                 const QString &author,
                 const QDateTime &created,
                 const QDateTime &updated,
                 const QStringList &tags)
    : _projectId(projectId),
      _projectType(projectType),
      _name(name),
      _url(url),
      _source(source),
      _author(author),
      _created(created),
      _updated(updated),
      _tags(tags)
{
    _valid = ( _projectId != 0 );
}

Project::Project()
    : _valid(false)
{

}

int Project::id()const
{
    return _projectId;
}

Project::ProjectType Project::projectType()const
{
    return _projectType;
}

QString Project::name()const
{
    return _name;
}

QString Project::url()const
{
    return _url;
}

QString Project::source()const
{
    return _source;
}

QString Project::author()const
{
    return _author;
}

QDateTime Project::created()const
{
    return _craeted;
}

QDateTime Project::updated()const
{
    return _updated;
}

QStringList Project::tags()const
{
    return _tags;
}

bool Project::valid()const
{
    return _valid;
}


