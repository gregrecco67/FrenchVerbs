#include <visage/app.h>
#include <string>
#include "App2.h"
int main()
{
    gwr::frvb::App2 app;
    app.show(1200, 900);
    app.runEventLoop();
    return 0;
}
