#include <visage/app.h>
#include "App.h"
int main()
{
    const char *env_user = std::getenv("USER");
    std::string user_str(env_user);
#ifdef IS_MACOS
    user_str = "/Users/" + user_str + "/Library/Application Support/FrenchVerbs/frvb.sqlite3";
#endif
    gwr::frvb::App app(user_str);
    app.show(1200, 900);
    app.runEventLoop();
    return 0;
}
