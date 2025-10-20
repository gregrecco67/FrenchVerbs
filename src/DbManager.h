#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <visage_file_embed/embedded_file.h>

namespace gwr::frvb
{

class DbManager
{
  public:
    SQLite::Database db;
    DbManager(std::string dbFileName);
    SQLite::Statement getStmt(std::string s);
    void secondHalf();
    const char *dbschema = R"foo(
CREATE TABLE frenchVerbs(
verbID INTEGER PRIMARY KEY AUTOINCREMENT,
infinitive TEXT,
pastParticiple TEXT,
presParticiple TEXT,
auxiliary TEXT,
imperative TEXT,
present TEXT,
imperfect TEXT,
passeSimple TEXT,
future TEXT,
conditional TEXT,
subjunctivePres TEXT,
subjunctiveImpf TEXT
);

 )foo";

    const char *dbWipe = R"foo(
drop table frenchVerbs;
    )foo";
};

} // namespace gwr::frvb
