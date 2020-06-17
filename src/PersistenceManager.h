#pragma once
#include <sqlite3.h>
#include <string>

/**
 * @brief Basic persistence added to the modules, just kinda saving historic register.
 */
class PersistenceManager
{
private:
    const std::string DATABASE_NAME{"AVL_Operations.db"};
    sqlite3 *dbHanlder{nullptr};

public:
    PersistenceManager() { InitDatabase(); };
    ~PersistenceManager() { CloseConnection(); };

    /**
     * @brief Saves the traverse of the requested AVL tree creation.
     * 
     * @remark This method just captures the operations which pass through
     * the API.
     * 
     * @param traverse Traverse path to the respective tree.
     * @return true if insert results sucessfully false otherwise.
     */
    bool InsertAVLTree(const std::string &traverse);

    /**
     * @brief Saves the parameters and result of the requested 
     * Common Ancestor calculation, this could save somewhat to
     * recreate the AVL tree if needed. You can see this just
     * like an audit log.
     * 
     * @remark This method just captures the operations which pass through
     * the API.
     * 
     * @param all parameters corresponds with the inputs/outputs of LCA operation
     * @return true if insert results sucessfully false otherwise.     
     */
    bool InsertLCAOperation(int firstValue, int secondValue, int result);

private:
    /**
     * @brief Initialize database connection and basic DDL
     */
    void InitDatabase();

    /**
     * @brief Establish connecion
     * 
     */
    void Connect();

    /**
     * @brief Close connection
     * 
     */
    void CloseConnection();

    /**
     * @brief Auxiliar method to execute queries.     
     * @param queryString query to execute     
     */
    void ExecuteQuery(const std::string &queryString);
};