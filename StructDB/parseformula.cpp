#include "parseformula.h"

std::vector<std::vector<QString>> parseFormula(QString Formula)
{
    std::vector<std::vector<QString>> result;
    std::vector<QString> D1;
    for (int i = 0; i < Formula.size();)
    {
        result.push_back(D1);
        QString suspect = "";
        QString number = "";
        //TODO
        if (Formula[i] == "A")
        {
            // Ac   89
            if (Formula[++i] == "c")
            {
                result[result.size()-1].push_back("At_89");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ag   47
            else if (Formula[i] == "g")
            {
                result[result.size()-1].push_back("At_47");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Al   13
            else if (Formula[i] == "l")
            {
                result[result.size()-1].push_back("At_13");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Am   95
            else if (Formula[i] == "m")
            {
                result[result.size()-1].push_back("At_95");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ar   18
            else if (Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_18");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // As   33
            else if (Formula[i] == "s")
            {
                result[result.size()-1].push_back("At_33");
                suspect = Formula[++i].toLatin1();

                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // At   85
            else if (Formula[i] == "t")
            {
                result[result.size()-1].push_back("At_85");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Au   79
            else if (Formula[i] == "u")
            {
                result[result.size()-1].push_back("At_79");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "B")
        {
            // Ba   56
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_56");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Be   4
            else if(Formula[i] == "e")
            {
                result[result.size()-1].push_back("At_4");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Bh   107
            else if(Formula[i] == "h")
            {
                result[result.size()-1].push_back("At_107");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Bi   83
            else if(Formula[i] == "i")
            {
                result[result.size()-1].push_back("At_83");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Bk   83
            else if(Formula[i] == "k")
            {
                result[result.size()-1].push_back("At_97");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Br   35
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_35");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // B    5
            else
            {
                result[result.size()-1].push_back("At_5");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "C")
        {
            // Ca   20
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_20");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cd   48
            else if(Formula[i] == "d")
            {
                result[result.size()-1].push_back("At_48");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ce   58
            else if(Formula[i] == "e")
            {
                result[result.size()-1].push_back("At_58");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cf   98
            else if(Formula[i] == "f")
            {
                result[result.size()-1].push_back("At_98");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cl   17
            else if(Formula[i] == "l")
            {
                result[result.size()-1].push_back("At_17");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cm   98
            else if(Formula[i] == "m")
            {
                result[result.size()-1].push_back("At_98");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cn   112
            else if(Formula[i] == "n")
            {
                result[result.size()-1].push_back("At_112");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Co   27
            else if(Formula[i] == "o")
            {
                result[result.size()-1].push_back("At_27");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cr   24
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_24");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cs   55
            else if(Formula[i] == "s")
            {
                result[result.size()-1].push_back("At_55");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Cu   29
            else if(Formula[i] == "u")
            {
                result[result.size()-1].push_back("At_29");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // C    6
            else
            {
                result[result.size()-1].push_back("At_6");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "D")
        {
            // Db   105
            if(Formula[++i] == "b")
            {
                result[result.size()-1].push_back("At_105");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ds   110
            else if(Formula[i] == "s")
            {
                result[result.size()-1].push_back("At_110");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Dy   66
            else if(Formula[i] == "y")
            {
                result[result.size()-1].push_back("At_66");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "E")
        {
            // Er   68
            if(Formula[++i] == "r")
            {
                result[result.size()-1].push_back("At_68");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Es   99
            else if(Formula[i] == "s")
            {
                result[result.size()-1].push_back("At_99");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Eu   63
            else if(Formula[i] == "u")
            {
                result[result.size()-1].push_back("At_63");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "F")
        {
            // Fe   26
            if(Formula[++i] == "e")
            {
                result[result.size()-1].push_back("At_26");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Fl   114
            else if(Formula[i] == "l")
            {
                result[result.size()-1].push_back("At_114");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Fm   100
            else if(Formula[i] == "m")
            {
                result[result.size()-1].push_back("At_100");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Fr   87
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_87");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // F    9
            else
            {
                result[result.size()-1].push_back("At_9");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "G")
        {
            // Ga   31
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_31");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Gd   64
            else if(Formula[i] == "d")
            {
                result[result.size()-1].push_back("At_64");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ge   32
            else if(Formula[i] == "e")
            {
                result[result.size()-1].push_back("At_32");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "H")
        {
            // He   2
            if(Formula[++i] == "e")
            {
                result[result.size()-1].push_back("At_2");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Hf   72
            else if(Formula[i] == "f")
            {
                result[result.size()-1].push_back("At_72");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Hg   80
            else if(Formula[i] == "g")
            {
                result[result.size()-1].push_back("At_80");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ho   67
            else if(Formula[i] == "o")
            {
                result[result.size()-1].push_back("At_67");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Hs   108
            else if(Formula[i] == "s")
            {
                result[result.size()-1].push_back("At_108");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // H    1
            else
            {
                result[result.size()-1].push_back("At_1");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "I")
        {
            // In   49
            if(Formula[++i] == "n")
            {
                result[result.size()-1].push_back("At_49");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ir   77
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_77");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // I    53
            else
            {
                result[result.size()-1].push_back("At_53");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "K")
        {
            // Kr   36
            if(Formula[++i] == "r")
            {
                result[result.size()-1].push_back("At_105");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // K    19
            else
            {
                result[result.size()-1].push_back("At_19");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "L")
        {
            // La   57
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_57");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Li   3
            else if(Formula[i] == "i")
            {
                result[result.size()-1].push_back("At_3");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Lr   103
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_103");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Lu   71
            else if(Formula[i] == "u")
            {
                result[result.size()-1].push_back("At_71");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Lv   116
            else if(Formula[i] == "v")
            {
                result[result.size()-1].push_back("At_116");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "M")
        {
            // Mc   115
            if(Formula[++i] == "c")
            {
                result[result.size()-1].push_back("At_115");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Md   101
            else if(Formula[i] == "d")
            {
                result[result.size()-1].push_back("At_101");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Mg   12
            else if(Formula[i] == "g")
            {
                result[result.size()-1].push_back("At_12");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Mn   25
            else if(Formula[i] == "n")
            {
                result[result.size()-1].push_back("At_25");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Mo   42
            else if(Formula[i] == "o")
            {
                result[result.size()-1].push_back("At_42");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Mt   109
            else if(Formula[i] == "t")
            {
                result[result.size()-1].push_back("At_109");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "N")
        {
            // Na   11
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_11");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Nb   41
            else if(Formula[i] == "b")
            {
                result[result.size()-1].push_back("At_41");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Nd   60
            else if(Formula[i] == "d")
            {
                result[result.size()-1].push_back("At_60");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ne   10
            else if(Formula[i] == "e")
            {
                result[result.size()-1].push_back("At_10");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Nh   113
            else if(Formula[i] == "h")
            {
                result[result.size()-1].push_back("At_113");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ni   28
            else if(Formula[i] == "i")
            {
                result[result.size()-1].push_back("At_28");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // No   102
            else if(Formula[i] == "o")
            {
                result[result.size()-1].push_back("At_102");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Np   93
            else if(Formula[i] == "p")
            {
                result[result.size()-1].push_back("At_93");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // N    7
            else
            {
                result[result.size()-1].push_back("At_7");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "O")
        {
            // Og   118
            if(Formula[++i] == "g")
            {
                result[result.size()-1].push_back("At_118");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Os   76
            else if(Formula[i] == "s")
            {
                result[result.size()-1].push_back("At_76");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // O    8
            else
            {
                result[result.size()-1].push_back("At_8");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "P")
        {
            // Pa   91
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_91");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Pb   82
            else if(Formula[i] == "b")
            {
                result[result.size()-1].push_back("At_82");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Pd   46
            else if(Formula[i] == "d")
            {
                result[result.size()-1].push_back("At_46");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Pm   61
            else if(Formula[i] == "m")
            {
                result[result.size()-1].push_back("At_62");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Po   84
            else if(Formula[i] == "o")
            {
                result[result.size()-1].push_back("At_84");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Pr   59
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_59");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Pt   78
            else if(Formula[i] == "t")
            {
                result[result.size()-1].push_back("At_78");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Pu   94
            else if(Formula[i] == "u")
            {
                result[result.size()-1].push_back("At_94");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // P    15
            else
            {
                result[result.size()-1].push_back("At_15");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "R")
        {
            // Ra   88
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_88");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Rb   37
            else if(Formula[i] == "b")
            {
                result[result.size()-1].push_back("At_37");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Re   75
            else if(Formula[i] == "e")
            {
                result[result.size()-1].push_back("At_75");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Rf   104
            else if(Formula[i] == "f")
            {
                result[result.size()-1].push_back("At_104");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Rg   111
            else if(Formula[i] == "g")
            {
                result[result.size()-1].push_back("At_111");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Rh   45
            else if(Formula[i] == "h")
            {
                result[result.size()-1].push_back("At_45");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Rn   86
            else if(Formula[i] == "n")
            {
                result[result.size()-1].push_back("At_86");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ru   44
            else if(Formula[i] == "u")
            {
                result[result.size()-1].push_back("At_44");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "S")
        {
            // Sb   51
            if(Formula[++i] == "b")
            {
                result[result.size()-1].push_back("At_51");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Sc   21
            else if(Formula[i] == "c")
            {
                result[result.size()-1].push_back("At_21");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Se   34
            else if(Formula[i] == "e")
            {
                result[result.size()-1].push_back("At_34");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Sg   106
            else if(Formula[i] == "g")
            {
                result[result.size()-1].push_back("At_106");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Si   14
            else if(Formula[i] == "i")
            {
                result[result.size()-1].push_back("At_14");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Sm   62
            else if(Formula[i] == "m")
            {
                result[result.size()-1].push_back("At_62");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Sn   50
            else if(Formula[i] == "n")
            {
                result[result.size()-1].push_back("At_50");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Sr   38
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_38");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // S    16
            else
            {
                result[result.size()-1].push_back("At_16");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "T")
        {
            // Ta   73
            if(Formula[++i] == "a")
            {
                result[result.size()-1].push_back("At_73");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Tb   65
            else if(Formula[i] == "b")
            {
                result[result.size()-1].push_back("At_65");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Tc   43
            else if(Formula[i] == "c")
            {
                result[result.size()-1].push_back("At_43");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Te   52
            else if(Formula[i] == "e")
            {
                result[result.size()-1].push_back("At_52");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Th   90
            else if(Formula[i] == "h")
            {
                result[result.size()-1].push_back("At_90");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ti   22
            else if(Formula[i] == "i")
            {
                result[result.size()-1].push_back("At_22");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Tl   81
            else if(Formula[i] == "l")
            {
                result[result.size()-1].push_back("At_81");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Tm   69
            else if(Formula[i] == "m")
            {
                result[result.size()-1].push_back("At_69");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Ts   117
            else if(Formula[i] == "s")
            {
                result[result.size()-1].push_back("At_117");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "U")
        {
            // U    92
            result[result.size()-1].push_back("At_92");
            suspect = Formula[++i].toLatin1();
            while (checkNumber(suspect) == true)
            {
                number += Formula[i].toLatin1();
                suspect = Formula[++i].toLatin1();
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "V")
        {
            // V    23
            result[result.size()-1].push_back("At_23");
            suspect = Formula[++i].toLatin1();
            while (checkNumber(suspect) == true)
            {
                number += Formula[i].toLatin1();
                suspect = Formula[++i].toLatin1();
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "W")
        {
            // W    74
            result[result.size()-1].push_back("At_74");
            suspect = Formula[++i].toLatin1();
            while (checkNumber(suspect) == true)
            {
                number += Formula[i].toLatin1();
                suspect = Formula[++i].toLatin1();
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "X")
        {
            // Xe   54
            if(Formula[++i] == "e")
            {
                result[result.size()-1].push_back("At_54");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "Y")
        {
            // Yb   70
            if(Formula[++i] == "b")
            {
                result[result.size()-1].push_back("At_70");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Y    39
            else
            {
                result[result.size()-1].push_back("At_39");
                suspect = Formula[i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else if (Formula[i] == "Z")
        {
            // Zn   30
            if(Formula[++i] == "n")
            {
                result[result.size()-1].push_back("At_30");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            // Zr   40
            else if(Formula[i] == "r")
            {
                result[result.size()-1].push_back("At_40");
                suspect = Formula[++i].toLatin1();
                while (checkNumber(suspect) == true)
                {
                    number += Formula[i].toLatin1();
                    suspect = Formula[++i].toLatin1();
                }
            }
            else
            {
                std::vector<std::vector<QString>> error(1);
                error[0].push_back("Error");
                error[0].push_back("Unknown Symbol");
                return error;
            }
            if (number == "")
                result[result.size()-1].push_back("1");
            else
                result[result.size()-1].push_back(number);
        }
        else
        {
            std::vector<std::vector<QString>> error(1);
            error[0].push_back("Error");
            error[0].push_back("Unknown Symbol");
            return error;
        }
    }
    return result;
}
