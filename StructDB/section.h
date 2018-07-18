#ifndef SECTION_H
#define SECTION_H

#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <QDebug>

int getMaxLineSection(std::string line);
std::string getLineSection(std::string line, int depth);
std::string getFileLine(std::string sectionStart, std::string sectionEnd, std::string keyword, std::string file);
std::string getLineSectionOfFile(std::string sectionStart, std::string sectionEnd, std::string keyword, std::string file, int depth);
#endif // SECTION_H
