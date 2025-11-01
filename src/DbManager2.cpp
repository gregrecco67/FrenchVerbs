#include "DbManager2.h"

namespace gwr::frvb
{

SQLite::Statement DbManager2::getStmt(std::string s) { return SQLite::Statement{db, s}; }

DbManager2::DbManager2(std::string dbFilename)
    : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    SQLite::Transaction tr(db);
    db.exec(dbschema);
    tr.commit();
    xaa();
    xab();
    xac();
    xad();
    xae();
    xaf();
    xag();
    xah();
    xai();
    xaj();
    xak();
    xal();
}

void DbManager2::xaa()
{
    SQLite::Transaction tr(db);
#include "splitrows/xaa"
    tr.commit();
}
void DbManager2::xab()
{
    SQLite::Transaction tr(db);
#include "splitrows/xab"
    tr.commit();
}
void DbManager2::xac()
{
    SQLite::Transaction tr(db);
#include "splitrows/xac"
    tr.commit();
}
void DbManager2::xad()
{
    SQLite::Transaction tr(db);
#include "splitrows/xad"
    tr.commit();
}
void DbManager2::xae()
{
    SQLite::Transaction tr(db);
#include "splitrows/xae"
    tr.commit();
}
void DbManager2::xaf()
{
    SQLite::Transaction tr(db);
#include "splitrows/xaf"
    tr.commit();
}
void DbManager2::xag()
{
    SQLite::Transaction tr(db);
#include "splitrows/xag"
    tr.commit();
}
void DbManager2::xah()
{
    SQLite::Transaction tr(db);
#include "splitrows/xah"
    tr.commit();
}
void DbManager2::xai()
{
    SQLite::Transaction tr(db);
#include "splitrows/xai"
    tr.commit();
}
void DbManager2::xaj()
{
    SQLite::Transaction tr(db);
#include "splitrows/xaj"
    tr.commit();
}
void DbManager2::xak()
{
    SQLite::Transaction tr(db);
#include "splitrows/xak"
    tr.commit();
}
void DbManager2::xal()
{
    SQLite::Transaction tr(db);
#include "splitrows/xal"
    tr.commit();
}

} // namespace gwr::frvb