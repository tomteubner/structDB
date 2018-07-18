#include "parseformula.h"

bool checkNumber(QString Suspect)
{
    if (Suspect == "0") return true;
    else if (Suspect == "1") return true;
    else if (Suspect == "2") return true;
    else if (Suspect == "3") return true;
    else if (Suspect == "4") return true;
    else if (Suspect == "5") return true;
    else if (Suspect == "6") return true;
    else if (Suspect == "7") return true;
    else if (Suspect == "8") return true;
    else if (Suspect == "9") return true;
    else return false;
}
