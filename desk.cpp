#include "desk.h"
#include <stdlib.h>
#include <time.h>

Desk::Desk()
{
    ///who go first?
    srand(time(0));
    int nowPlayer = rand()%2;


}
