#include "DbManager2.h"

namespace gwr::frvb
{

SQLite::Statement DbManager2::getStmt(std::string s) { return SQLite::Statement{db, s}; }

DbManager2::DbManager2(std::string dbFilename)
    : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    db.exec(dbschema);

#include "rows.h"
}

} // namespace gwr::frvb