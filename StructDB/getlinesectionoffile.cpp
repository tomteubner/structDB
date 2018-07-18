#include "section.h"

std::string getLineSectionOfFile(std::string sectionStart, std::string sectionEnd, std::string keyword, std::string file, int depth)
{
    //return getLineSection(getFileLine(sectionStart, sectionEnd, keyword, file), depth);
    try {
        return getLineSection(getFileLine(sectionStart, sectionEnd, keyword, file), depth);
    } catch (std::invalid_argument& e) {
        qDebug() << e.what();
    }
}
