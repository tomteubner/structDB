#include "cp2kdata.h"

cp2kData::cp2kData()
{
    this->Gl_Ru = "";
    this->Fe_Me = "";
    this->Fe_Df_Uk = "0";
    this->Fe_Df_Ro = "0";
    this->Fe_Df_Mu = "";
    for (int i = 0; i < 120; i++)
        this->NumElements[i] = 0;
    this->Fe_Su_Ce_Gag = 100;
    this->Fe_Su_Ce_Pog = 100;
}
