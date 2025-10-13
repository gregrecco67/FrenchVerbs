#include "DbManager.h"

namespace gwr::frvb
{

SQLite::Statement DbManager::getStmt(std::string s) { return SQLite::Statement{db, s}; }

DbManager::DbManager(std::string dbFilename) : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    try
    {
        db.exec(dbschema);
        auto st = getStmt("INSERT INTO frenchVerbs (infinitive) values (?)");
        
        const unsigned char* db_char = resources::dbs::conjugations_json.data;
        st.bind(1, "avaler");
        st.exec();
    }
    catch (std::exception &e)
    {
        std::cout << "Got exception: " << e.what() << std::endl;
    }
    
    

}

} // namespace gwr::frvb
