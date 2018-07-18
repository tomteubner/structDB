#include "section.h"
//Sucht nach keyword innerhald der file, wird durch sectionStart/End begrenzt
std::string getFileLine(std::string sectionStart, std::string sectionEnd, std::string keyword, std::string file)
{
    if (sectionStart.empty() || sectionEnd.empty()  || keyword.empty() || file.empty()){
        throw std::invalid_argument ( "one of the given arguments are empty" );
    }
    else {
        std::ifstream ifs;                  //Input Filestream
        ifs.open(file);                     //öffnen der Datei
        if (ifs.is_open()) {                //wenn Filestream offen:
            std::string line;               //Rückgabevariable; Zwichenspeicherung der Zeilen
            while (!ifs.eof()) {            //solange Filestream inhalt hat:
                std::getline(ifs, line);    //nächste Zeile auf Filestream nehmen und in line speichern
                if (std::regex_match (line, std::regex("(.*)("+sectionStart+")(.*)"))) {   //wenn Anfang des Abschnittes in liine gefunden wurde:
                    std::getline(ifs,line);                                                //nächste Zeile auf Filestream nehmen und in line speichern
                    while (!std::regex_match (line, std::regex("(.*)("+sectionEnd+")(.*)"))) {  //solange line nicht Ende des Abschnittes ist:
                        if(std::regex_match (line, std::regex("(.*)("+keyword+")(.*)"))) {      //wenn keyword in line gefunden wird:
                            ifs.close();    //input Filestream schließen
                            return line;    //line mit Keyword ausgeben
                        }
                        else {
                            std::getline(ifs,line);     //wenn keyword nicht in line gefunden wird nächste Line abfragen
                        }
                    }
                }
            }
        }
        else {
            throw std::logic_error ( "unable to open file "+ file );
        }
    }
    return "";
}









