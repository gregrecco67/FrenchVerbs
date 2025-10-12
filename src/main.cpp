#include <visage/app.h>
#include "App.h"
int main()
{
    gwr::frvb::App app;
    app.show(1200, 900);
    app.runEventLoop();
    return 0;
}
