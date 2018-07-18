#ifndef PARSEFORMULA_H
#define PARSEFORMULA_H

#include <string>
#include <vector>
#include <QMainWindow>

bool checkNumber(QString Suspect);
std::vector<std::vector<QString>> parseFormula(QString Formula);

#endif // PARSEFORMULA_H
