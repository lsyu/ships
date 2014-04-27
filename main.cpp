#include "application.h"

using namespace std;

int main()
{
    CApplication *app = CApplication::getInstance();
    if (app->configure())
        app->exec();
    return 0;
}

