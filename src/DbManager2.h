#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <visage_file_embed/embedded_file.h>

namespace gwr::frvb
{

class DbManager2
{
  public:
    SQLite::Database db;
    DbManager2(std::string dbFileName);
    SQLite::Statement getStmt(std::string s);
    void xaa();
    void xab();
    void xac();
    void xad();
    void xae();
    void xaf();
    void xag();
    void xah();
    void xai();
    void xaj();
    void xak();
    void xal();

    const char *dbschema = "CREATE TABLE IF NOT EXISTS recogs(id INTEGER PRIMARY KEY, "
                           "form TEXT, head TEXT, parse TEXT);";
};

} // namespace gwr::frvb
