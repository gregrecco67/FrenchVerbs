#include <visage/app.h>
#include <string>
#include "App.h"
int main()
{
//    const char *env_user = std::getenv("USER");
//    std::string user_str(env_user);
// #ifdef IS_MACOS
//     // user_str = "/Users/" + user_str + "/Library/Application Support/FrenchVerbs/frvb.sqlite3";
//     user_str = ":memory:";
// #endif
    gwr::frvb::App app;
    app.show(1200, 900);
    app.runEventLoop();
    return 0;
}
