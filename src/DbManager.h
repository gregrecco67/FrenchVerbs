#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

namespace gwr::frvb
{

class DbManager
{
  public:
    SQLite::Database db;
    DbManager(std::string dbFileName);
    SQLite::Statement getStmt(std::string s);
    const char *dbschema = R"foo(
CREATE TABLE IF NOT EXISTS frenchVerbs(
verbID INTEGER PRIMARY KEY AUTOINCREMENT,
infinitive TEXT,
pastParticiple TEXT,
presParticiple TEXT,
auxiliary TEXT,
present TEXT,
imperfect TEXT,
passeCompose TEXT
);

 )foo";

    const char *dbWipe = R"foo(
drop table frenchVerbs;
    )foo";
};

} // namespace gwr::frvb
