#include "section.h"

std::string getLineSection(std::string line, int depth)
{
    if (line.empty()){
        throw std::invalid_argument ( "line argument is empty 1" );
    }
    else {
        std::string section;        //Rückgabevariable
        std::stringstream ss;       //Stringstream
        ss << line;                 //Zeile in ss einspeichern
        for (int i = 0; i <= depth; i++)    //solange daten aus dem ss zwichenspeichern/überspeichern bis gewünschte section erreicht ist
        {
            ss >> section;
        }
        return section;         //wenn gewünschte section erreicht ist zurückgeben
    }
}
