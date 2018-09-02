#ifndef PROJECTSTABLE_H
#define PROJECTSTABLE_H

#include "Objects/project.h"

class ProjectsTable
{
public:
    static bool createTable();

    static Project create(const QString&name, const QString& url, const QString& source, const QString& author,
                          const Project::ProjectType& projectType, const QStringList& tags);

    static Project        getByName(const QString& name);
    static Project        getByUrl(const QString& url);
    static QList<Project> getAll();

    static bool update(const Project& project);

    static bool remove(const Project& project);
    static bool removeAll();
};

#endif // PROJECTSTABLE_H
