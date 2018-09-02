#ifndef DATABASE_H
#define DATABASE_H


class Database
{
public:
    Database();

    bool init(const QString &dbName);
    bool close();

private:
    bool createTables();
};

#endif // DATABASE_H
