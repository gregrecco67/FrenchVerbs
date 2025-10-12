#include "DbManager.h"

namespace gwr::frvb
{

SQLite::Statement DbManager::getStmt(std::string s) { return SQLite::Statement{db, s}; }

DbManager::DbManager(std::string dbFilename) : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
#ifndef DB_DEBUG
    try
    {
        db.exec(dbschema);
    }
    catch (std::exception &e)
    {
        std::cout << "Got exception: " << e.what() << std::endl;
    }
#endif

}

} // namespace gwr::frvb
