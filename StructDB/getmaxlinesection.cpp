#include "section.h"

int getMaxLineSection(std::string line)
{
    if (line.empty())
        throw std::invalid_argument ( "line argument is empty 1" );
    else {
        int counter = -1;       //Counter für stringstream
        std::string trash;      //Variable um denn Strigstream zu leeren
        std::stringstream ss;   //Stringstream
        ss << line;             //Zeile in Stringstream übertragen
        while (!ss.eof())       //solange stringstream nicht leer ist:
        {
            ss >> trash;        //Wert aus stringstream entfernen
            counter++;          //counter erhöhen
        }
        return counter;         //Wenn stringstream leer counter zurückgeben
    }
    return 0;
}
