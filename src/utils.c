#include <stdlib.h>
#include "utils.h"

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
