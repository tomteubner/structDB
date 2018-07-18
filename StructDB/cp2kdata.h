#ifndef CP2KDATA_H
#define CP2KDATA_H

#include <string>
#include <vector>

class cp2kData
{
public:
    cp2kData();
    std::string Gl_Ru = "";      //Logfile Run Type
    std::string Fe_Me = "";      //Logfile QS| (QS)
    std::string Fe_Df_Uk = "";   //Logfile QS| UKS
    std::string Fe_Df_Ro = "";   //Logfile QS| ROKS
    std::string Fe_Df_Mu = "";   //Logfile DFT| Multiplicity
    std::string Fe_Su_Ce_A[3];  //Logfile CELL| vector a
    std::string Fe_Su_Ce_B[3];  //Logfile CELL| vector a
    std::string Fe_Su_Ce_C[3];  //Logfile CELL| vector a
    std::vector< std::vector< std::string> > Ou_Col;    //All Locked Atoms (Logfile COOLVARS/FIXED_ATOMS)
    std::string Fe_Df_Po_Pe = "";    //&POISSON PERIODIC
    std::string Fe_Df_Po_Mu_Rc = ""; //&MULTIPOLE RCUT
    std::string Fe_Df_Qs_Me = "";    //&QS METHOD
    std::string Fe_Df_Xc_Vd_Ty = ""; //&VDW_POTENTIAL POTENTIAL_TYPE
    std::string Fe_Df_Xc_Vd_Pa_Rc = "";  //&VDW_POTENTIAL RCUT
    int Fe_Df_Xc_Vd_Pa_C9;      //&VDW_POTENTIAL CALCULATE_C9_TERM (0/1)
    std::string Fe_Df_Xc_Vd_Pa_Ty = "";  //&PAIR_POTENTIAL TYPE
    std::string Fe_Su_Ce_Pe = "";    //&CELL PERIODIC
    std::string Fe_Su_Ce_Sy = "";    //&CELL SYMETRY
    std::string Mo_Ge_Op = "";   //&GEO_OPT OPTIMIZER
    std::string Mo_Ce_Ty = "";   //&CELL_OPT TYPE
    std::string Mo_Ba_Ba = "";   //&BAND BAND_TYPE
    std::string Mo_Ba_Ks = "";   //&BAND KSPRING
    std::string Mo_Ba_Nu = "";   //&BAND NUMBER_OF_REPLICA
    int Mo_Ba_Op_Ope;   //&OPTIMIZE_BAND OPTIMIZE_END_POINTS (0/1)
    std::string Mo_Ba_Op_Opt = "";   //&OPTIMIZE_BAND OPT_TYPE
    std::string Fe_Df_Xc_Fu = "";    //&XC_FUNCTIONAL
    std::vector< std::vector< std::string> > Coords; //COORDS
    std::vector< std::vector< std::string> > Fe_Su_Ki;  //KIND BASIS_SET & POTENTIAL from ATkinds aus Inpfile
    int Fe_Su_Ce_Gag = 0;
    int Fe_Su_Ce_Pog = 0;
    std::string Fe_St = "";
    std::string Fe_Df_Po_So = "";
    int Df_Fe_Ex = 0;
    std::string Fe_Df_Sc_Ep = "";
    int Fe_Df_Si = 0;
    int Fe_Df_Xc_Hf = 0;
    std::vector<std::string> Ou_QMEne;
    std::vector<std::string> Ou_Ene;
    std::vector<std::string> Ou_Int;
    std::vector<std::string> Ou_Sin;
    std::vector<std::string> Ou_Ide;
    std::string Ou_Pre = "";
    std::string Ou_Rea = "";
    std::string Ou_Mas = "";
    std::string Ou_Rms = "";
    std::string Ou_Maf = "";
    std::string Ou_Rmf = "";
    std::vector<std::string> Ou_Neb_Dist;


    std::string Charge = ""; //GENINFO
    std::string Toolkit = "";    //GENINFO
    std::string Version = "";    //GENINFO
    int AtNum = 0;  //Number of Atoms
    int NumElements[119];   //[1] = H, [2] = He,...
    std::vector<std::string> AtKinds;   //Unterschiedliche Atome
    std::string SumEq = "";
    // Parsing List Zelle = Ordnungszahl
    std::string Elementlist[119] = {"", "H","He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Uut", "Fl", "Uup", "Lv", "Uus", "Uuo"};
    int oep = 1;
    std::vector<std::string> Names;
};

#endif // CP2KDATA_H
