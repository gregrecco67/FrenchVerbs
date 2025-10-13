#include "DbManager.h"

namespace gwr::frvb
{

SQLite::Statement DbManager::getStmt(std::string s) { return SQLite::Statement{db, s}; }

DbManager::DbManager(std::string dbFilename) : db(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    try
    {
        db.exec(dbschema);
        // auto st = getStmt("INSERT INTO frenchVerbs (infinitive) values (?)");
        // const unsigned char* db_char = resources::dbs::conjugations_json.data;
        // st.bind(1, "avaler");
        // st.exec();
        auto st = getStmt("INSERT INTO frenchVerbs (infinitive, present, imperfect, passeCompose, presParticiple, pastParticiple, passeSimple, future, conditional, subjunctive) values (?,?,?,?,?,?,?,?,?,?)");
        st.bind(1, 'abandonner');
        st.bind(2, '["abandonne", "abandonnes", "abandonne", "abandonnons", "abandonnez", "abandonnent"]');
        st.bind(3, '["abandonnais", "abandonnais", "abandonnait", "abandonnions", "abandonniez", "abandonnaient"]');
        st.bind(4, '["ai abandonn\u00e9", "as abandonn\u00e9", "a abandonn\u00e9", "avons abandonn\u00e9", "avez abandonn\u00e9", "ont abandonn\u00e9"]');
        st.bind(5, 'abandonnant');
        st.bind(6, 'abandonné');
        st.bind(7, '["abandonnai", "abandonnas", "abandonna", "abandonn\u00e2mes", "abandonn\u00e2tes", "abandonn\u00e8rent"]');
        st.bind(8, '["abandonnerai", "abandonneras", "abandonnera", "abandonnerons", "abandonnerez", "abandonneront"]');
        st.bind(9, '["abandonnerais", "abandonnerais", "abandonnerait", "abandonnerions", "abandonneriez", "abandonneraient"]');
        st.bind(10, '["abandonne", "abandonnes", "abandonne", "abandonnions", "abandonniez", "abandonnent"]');st.exec();
        st.clear();

        st.bind(1, 'abattre');
        st.bind(2, '["abats", "abats", "abat", "abattons", "abattez", "abattent"]');
        st.bind(3, '["abattais", "abattais", "abattait", "abattions", "abattiez", "abattaient"]');
        st.bind(4, '["ai abattu", "as abattu", "a abattu", "avons abattu", "avez abattu", "ont abattu"]');
        st.bind(5, 'abattant');
        st.bind(6, 'abattu');
        st.bind(7, '["abattis", "abattis", "abattit", "abatt\u00eemes", "abatt\u00eetes", "abattirent"]');
        st.bind(8, '["abattrai", "abattras", "abattra", "abattrons", "abattrez", "abattront"]');
        st.bind(9, '["abattrais", "abattrais", "abattrait", "abattrions", "abattriez", "abattraient"]');
        st.bind(10, '["abatte", "abattes", "abatte", "abattions", "abattiez", "abattent"]');st.exec();
        st.clear();
        // verbID INTEGER PRIMARY KEY AUTOINCREMENT,
        // infinitive TEXT,
        // pastParticiple TEXT,
        // presParticiple TEXT,
        // auxiliary TEXT,
        // present TEXT,
        // imperfect TEXT,
        // passeCompose TEXT,
        // passeSimple TEXT,
        // future TEXT,
        // conditional TEXT,
        // subjunctivePres TEXT


    }
    catch (std::exception &e)
    {
        std::cout << "Got exception: " << e.what() << std::endl;
    }
    
    

}

} // namespace gwr::frvb
