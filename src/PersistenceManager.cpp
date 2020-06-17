#include <iostream>
#include <sstream>
#include <vector>
#include "PersistenceManager.h"

using namespace std;

const vector<string> TABLE_DDL{"CREATE TABLE IF NOT EXISTS AVLTreeHistory ( id INTEGER PRIMARY KEY AUTOINCREMENT, traverse TEXT NOT NULL);",
                               "CREATE TABLE IF NOT EXISTS LCAHistory ( id INTEGER PRIMARY KEY AUTOINCREMENT, firstValue INTEGER NOT NULL, secondValue INTEGER NOT NULL, commonAncestor INTEGER NOT NULL);"};

int callback(void *NotUsed, int argc, char **argv, char **colName)
{
    for (size_t i = 0; i < argc; ++i)
    {
        cout << colName[i] << " " << (argv[i] ? argv[i] : "NULL") << endl;
    }

    return 0;
}

void PersistenceManager::InitDatabase()
{
    try
    {
        Connect();
        for (auto const &tableDDL : TABLE_DDL)
        {
            ExecuteQuery(tableDDL);
        }
    }
    catch (const exception &e)
    {
        cerr << "Error initializing database " << endl
             << e.what() << endl;
    }
}

bool PersistenceManager::InsertAVLTree(const string &traverse)
{
    stringstream sqlBuilder;
    sqlBuilder << "INSERT INTO AVLTreeHistory (traverse) "
               << "VALUES (\"" << traverse << "\");";
    ExecuteQuery(sqlBuilder.str());
    return false;
}

bool PersistenceManager::InsertLCAOperation(int firstValue, int secondValue, int result)
{
    stringstream sqlBuilder;
    sqlBuilder << "INSERT INTO LCAHistory (firstValue, secondValue, commonAncestor) "
               << "VALUES (" << firstValue << ", " << secondValue << ", "
               << result << ");";
    ExecuteQuery(sqlBuilder.str());
    return false;
}

void PersistenceManager::Connect()
{
    auto result = sqlite3_open(DATABASE_NAME.c_str(), &dbHanlder);

    if (result)
        throw exception(sqlite3_errmsg(dbHanlder));
    else
        cout << "Database opened successfully" << endl;
}

void PersistenceManager::CloseConnection()
{
    if (dbHanlder == nullptr)
    {
        cerr << "Invalid call to PersistenceManager::CloseConnection, there isn't opened connections" << endl;
        return;
    }

    sqlite3_close(dbHanlder);
}

void PersistenceManager::ExecuteQuery(const string &queryString)
{
    char *sqliteError;
    auto result = sqlite3_exec(dbHanlder, queryString.c_str(), callback, nullptr, &sqliteError);

    if (result != SQLITE_OK)
    {
        cerr << "Error executing query: " << sqliteError << endl;
        sqlite3_free(sqliteError);
    }
}