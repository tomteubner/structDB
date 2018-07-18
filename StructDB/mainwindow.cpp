#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vector"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>


#include "parseformula.h"
#include "section.h"
//Konstruktor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Setup the default values on startup
    ui->uploadButton->setEnabled(false);        //Upload Button ausgrauen
    //Kategorien für Runtype laden
    ui->boxRuntype->addItem("ALL");
    ui->boxRuntype->addItem("BAND");
    ui->boxRuntype->addItem("CELL_OPT");
    ui->boxRuntype->addItem("ENERGY");
    ui->boxRuntype->addItem("ENERGY_FORCE");
    ui->boxRuntype->addItem("GEO_OPT");

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    // You may want to use QRegularExpression for new code with Qt 5 (not mandatory).
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->ipaddress->setValidator(ipValidator);

}
//Dekonstruktor
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDBdata()
{
    MainWindow::connection.set_ip(ui->ipaddress->text().toStdString());
    MainWindow::connection.set_port(ui->port->text().toInt());
    MainWindow::connection.set_db(ui->database->text().toStdString());
    MainWindow::connection.set_username(ui->username->text().toStdString());
    MainWindow::connection.set_password(ui->password->text().toStdString());
}

//Wenn der Table aktualsiert wird, wird er zuerst komplett geleert und anschließend neu mit Spalten und Werten gefüllt
void MainWindow::on_updateTable_clicked()
{
    MainWindow::setDBdata();
    if (MainWindow::connection.openConnection(0) == true)
    {
        // Table wird gelehrt
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);
        //2D Array für die gefilterten Atome
        std::vector<std::vector<QString>> Atoms;
        //Werte für Atoms abspeichern
        Atoms = parseFormula(ui->searchString->text());
        //Ertsellen der MySQL Anfrage
        QString query = "";

        //Genereller Rahmen für Anfrage
        query += "SELECT gen_inf.Struct_Id, gen_inf.SumEq, gen_inf.At_Num, gen_inf.Toolkit, gen_inf.Version, cp2k_v2.Gl_Ru_DB, gen_inf.Charge ";
        query += "FROM gen_inf, cp2k_v2 ";
        query += "WHERE gen_inf.Struct_Id = cp2k_v2.Struct_Id ";

        //Wenn Runtype auswahl nicht auf 0 steht, " AND cp2k_v2.Gl_Ru_DB =..." an Query anhängen
        if (ui->boxRuntype->currentIndex() > 0)
        {
            query += "AND cp2k_v2.Gl_Ru_DB = ";
            query += '"';
            query += ui->boxRuntype->currentText();
            query += '"';
            query += " ";
        }
        //Wenn Summenformel angegeben ist, MYSQL Query erweitern um die Atome
        if (Atoms.size() > 0)
        {
            if (Atoms[0][0] != "Error")
            {
                query += "AND ";
                for (size_t i = 0; i < Atoms.size()-1; i++)
                {
                    query += "gen_inf.";
                    query += Atoms[i][0];
                    query += " = ";
                    query += Atoms[i][1];
                    query += " AND ";
                }
                query += "gen_inf.";
                query += Atoms[Atoms.size()-1][0];
                query += " = ";
                query += Atoms[Atoms.size()-1][1];
            }
        }
        //Ausführen der Query
        std::vector<std::vector<std::string> > Result = connection.executeReturnQuery(query);
        //Verbindung schließen
        MainWindow::connection.closeConnection();
        //Anzahl der Spalten in Table generienren
        for (size_t i = 0; i < Result.size(); i++)
        {
            ui->tableWidget->insertColumn(i);
            ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(Result[i][0])));
        }
        //Anzahl der Reihen im Table generieren
        for (size_t i = 0; i < Result[0].size(); i++)
        {
            ui->tableWidget->insertRow(i);
        }
        //Spalten mit Daten füllen
        for (size_t i = 0; i < Result.size(); i++)
        {
            for (size_t ii = 0; ii < Result[i].size(); ii++)
            {
                QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(Result[i][ii]));
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                ui->tableWidget->setItem(ii, i, item);
            }
        }
        ui->tableWidget->removeRow(0); // Keine Ahnung warum
        //Streckung einstellen
        QHeaderView* header = ui->tableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Stretch);
    }
}

//logFile Browser
void MainWindow::on_setLog_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/"+QDir::home().dirName(),tr("Log Files (*.log*)")); 
    ui->showLog->setText(fileName); //Angezeigten Pfad aktualisieren
}

//xzyFile Browser
void MainWindow::on_setXYZ_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/Users/"+QDir::home().dirName(),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->showXYZ->setText(fileName+"/"); //Angezeigten Pfad aktualisieren
}

//inpFile Browser
void MainWindow::on_setInput_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/"+QDir::home().dirName(),tr("Input Files (*.in*)"));
    ui->showInput->setText(fileName); //Angezeigten Pfad aktualisieren
}

//Filter  = QString fileName = QFileDialog::getOpenFileName(this, tr(Open [FILE, DIRECTORY]),"PATH,tr("FILTER mit Reg Expression"));

void MainWindow::on_checkButton_clicked()
{
    bool BREAK = false;
    std::ifstream ifs;
    std::string tmpString;
    ui->msgBoard->clear();


    //Checking FILE/PATH`s
    tmpString = ui->showInput->text().toStdString();
    if (tmpString != "")
    {
        if (std::regex_match (tmpString, std::regex("(.*)(.inp)()")))
        {
            ifs.open(tmpString);
            if (!ifs.is_open())
            {
                BREAK = true;
                ui->msgBoard->appendHtml("<b>ERROR</b> Cant open FILE<br><i> "+QString::fromStdString(tmpString)+"</i>");
            }
            else
            {
                ui->msgBoard->appendHtml("<b>FOUND</b> FILE</b><br><i> "+QString::fromStdString(tmpString)+"</i>");
                ifs.close();
            }
        }
        else
        {
            BREAK = true;
            ui->msgBoard->appendHtml("<b>ERROR</b> No or wrong FILE<br><i> "+QString::fromStdString(tmpString)+"</i>");
        }
    }
    else
    {
        BREAK = true;
        ui->msgBoard->appendHtml("<b>ERROR</b> Missing FILE<br><i> Input</i>");
    }

    tmpString = ui->showLog->text().toStdString();
    if (tmpString != "")
    {
        if (std::regex_match (tmpString, std::regex("(.*)(.log)()")))
        {
            ifs.open(tmpString);
            if (!ifs.is_open())
            {
                BREAK = true;
                ui->msgBoard->appendHtml("<b>ERROR</b> Cant open FILE<br><i> "+QString::fromStdString(tmpString)+"</i>");
            }
            else
            {
                ui->msgBoard->appendHtml("<b>FOUND</b> Found FILE<br><i> "+QString::fromStdString(tmpString)+"</i>");
                ifs.close();
            }
        }
        else
        {
            BREAK = true;
            ui->msgBoard->appendHtml("<b>ERROR</b> No or wrong FILE<br><i> "+QString::fromStdString(tmpString)+"</i>");
        }
    }
    else
    {
        BREAK = true;
        ui->msgBoard->appendHtml("<b>ERROR</b> Missing FILE<br><i>  Log</i>");
    }

    tmpString = ui->showXYZ->text().toStdString();
    if (tmpString != "")
    {
        if (std::regex_match (tmpString, std::regex("(.*)(/)()")))
        {
            ifs.open(tmpString);
            if (!ifs.is_open())
            {
                BREAK = true;
                ui->msgBoard->appendHtml("<b>ERROR</b> Cant open PATH<br><i>  "+QString::fromStdString(tmpString)+"</i>");
            }
            else
            {
                ui->msgBoard->appendHtml("<b>FOUND</b> Found PATH<br><i>  "+QString::fromStdString(tmpString)+"</i>");
                ifs.close();
            }
        }
        else
        {
            BREAK = true;
            ui->msgBoard->appendHtml("<b>ERROR</b> No PATH<br><i>  "+QString::fromStdString(tmpString)+"</i>");
        }
    }
    else
    {
        BREAK = true;
        ui->msgBoard->appendHtml("<b>ERROR</b> Missing FILE<br><i>  Input</i>");
    }

    if (BREAK == false)
    {
        cp2kData data;
        std::string xyzFile;
        std::string logFile = ui->showLog->text().toStdString();
        std::string inpFile = ui->showInput->text().toStdString();
        std::string tmpString;
        ifs.open(ui->showLog->text().toLatin1());
        if (ifs.is_open())
        {
            //Infos aus Log File Parsen
            std::string line;
            while (!ifs.eof() && line != " ATOMIC KIND INFORMATION" && BREAK == false)
            {
                std::getline(ifs, line);
                // GLOBAL *
                if (std::regex_match (line, std::regex("( GLOBAL)(.*)")))
                {
                    // * Run Type *
                    if(std::regex_match (line, std::regex("(.*)(Run type)(.*)")))
                    {
                        MainWindow::MainWindow::data.Gl_Ru = getLineSection(line, 3);
                        if (getLineSection(line, 3) == "BAND")
                        {
                            MainWindow::data.Gl_Ru = "BAND";
                            ui->msgBoard->appendHtml("<b>FOUND</b> Run type<br><i> "+QString::fromStdString(MainWindow::data.Gl_Ru)+"</i>");
                        }
                        else if (getLineSection(line, 3) == "CELL_OPT")
                        {
                            MainWindow::data.Gl_Ru = "CELL_OPT";
                            ui->msgBoard->appendHtml("<b>FOUND</b> Run type<br><i> "+QString::fromStdString(MainWindow::data.Gl_Ru)+"</i>");
                        }
                        else if (getLineSection(line, 3) == "ENERGY" || getLineSection(line, 3) == "WAVEFUNCTION_OPTIMIZATION" || getLineSection(line, 3) == "WFN_OPT")
                        {
                            MainWindow::data.Gl_Ru = "ENERGY";
                            ui->msgBoard->appendHtml("<b>FOUND</b> Run type<br><i> "+QString::fromStdString(MainWindow::data.Gl_Ru)+"</i>");
                        }
                        else if (getLineSection(line, 3) == "ENERGY_FORCE")
                        {
                            MainWindow::data.Gl_Ru = "ENERGY_FORCE";
                            ui->msgBoard->appendHtml("<b>FOUND</b> Run type<br><i> "+QString::fromStdString(MainWindow::data.Gl_Ru)+"</i>");
                        }
                        else if (getLineSection(line, 3) == "GEO_OPT" || getLineSection(line, 3) == "GEOMETRIE_OPTIMIZATION")
                        {
                            MainWindow::data.Gl_Ru = "GEO_OPT";
                            ui->msgBoard->appendHtml("<b>FOUND</b> Run type<br><i> "+QString::fromStdString(MainWindow::data.Gl_Ru)+"</i>");
                        }
                        else
                        {
                            ui->msgBoard->appendHtml("<b>ERROR</b> Unsupported Run type<br><i> "+QString::fromStdString(getLineSection(line, 3))+"</i>");
                            BREAK = true;
                        }
                    }

                }
                else if (std::regex_match (line, std::regex("( QS)(.*)") ))
                {
                    MainWindow::data.Fe_Me = "QS";
                    if(std::regex_match (line, std::regex("(.*)(UKS)(.*)")))
                    {
                        MainWindow::data.Fe_Df_Uk="1";
                        ui->msgBoard->appendHtml("<b>FOUND</b> QS UKS");
                    }

                    else if (std::regex_match (line, std::regex("(.*)(ROKS)(.*)")))
                    {
                        MainWindow::data.Fe_Df_Ro="1";
                        ui->msgBoard->appendHtml("<b>FOUND</b> QS UKS");
                    }
                }
                else if (std::regex_match (line, std::regex("( DFT)(.*)")))
                {
                    if(std::regex_match (line, std::regex("(.*)(Multiplicity)(.*)")))
                    {
                        MainWindow::data.Fe_Df_Mu = getLineSection(line, 3);
                        ui->msgBoard->appendHtml("<b>FOUND</b> DFT Multiplicity<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Mu)+"</i>");
                    }

                    else if(std::regex_match (line, std::regex("(.*)(Charge)(.*)")))
                    {
                        MainWindow::data.Charge = getLineSection(line, getMaxLineSection(line));
                        ui->msgBoard->appendHtml("<b>FOUND</b> DFT Charge<br><i> "+QString::fromStdString(MainWindow::data.Charge)+"</i>");
                    }
                }
                else if (std::regex_match (line, std::regex("( CELL)(.*)")))
                {
                    if(std::regex_match (line, std::regex("(.*)(Vector a)(.*)")))
                    {
                        //Zahlen aus den Zeilen speichern
                        MainWindow::data.Fe_Su_Ce_A[0] = getLineSection(line, 4);
                        MainWindow::data.Fe_Su_Ce_A[1] = getLineSection(line, 5);
                        MainWindow::data.Fe_Su_Ce_A[2] = getLineSection(line, 6);
                    }
                    else if(std::regex_match (line, std::regex("(.*)(Vector b)(.*)")))
                    {
                        MainWindow::data.Fe_Su_Ce_B[0] = getLineSection(line, 4);
                        MainWindow::data.Fe_Su_Ce_B[1] = getLineSection(line, 5);
                        MainWindow::data.Fe_Su_Ce_B[2] = getLineSection(line, 6);
                    }
                    else if(std::regex_match (line, std::regex("(.*)(Vector c)(.*)")))
                    {
                        MainWindow::data.Fe_Su_Ce_C[0] = getLineSection(line, 4);
                        MainWindow::data.Fe_Su_Ce_C[1] = getLineSection(line, 5);
                        MainWindow::data.Fe_Su_Ce_C[2] = getLineSection(line, 6);
                    }
                }
                // CP2K
                else if (std::regex_match (line, std::regex("( CP2K)(.*)")))
                {
                    if(std::regex_match (line, std::regex("(.*)(version string:)(.*)")))
                    {
                        MainWindow::data.Toolkit = "CP2K";
                        MainWindow::data.Version = getLineSection(line, 5);
                        ui->msgBoard->appendHtml("<b>FOUND</b> Toolkit<br><i> "+QString::fromStdString(MainWindow::data.Toolkit)+"</i>");
                        ui->msgBoard->appendHtml("<b>FOUND</b> Version<br><i> "+QString::fromStdString(MainWindow::data.Version)+"</i>");
                    }
                }
                // COLVARS
                else if (std::regex_match (line, std::regex("( COLVARS)(.*)")))
                {
                    if(std::regex_match (line, std::regex("(.*)(>>> ATOMS:)(.*)")))
                    {
                        std::vector<std::string> row;
                        MainWindow::data.Ou_Col.push_back(row);
                        MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].push_back(getLineSection(line, 1));
                        //Länge der Zeile herausfinden
                        int maxIteration = getMaxLineSection(line);
                        //Alles nach der 4ten Sction speichern
                        for (int i = 4; i <= maxIteration; i++)
                        {
                            MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].push_back(getLineSection(line, i));
                        }
                        // Wenn es weniger als 4 Sind wird ausgefüllt
                        for (int i = MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].size()-1; i < 4; i++)
                        {
                            MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].push_back("FILL");
                        }
                    }
                }
            }
        }
        if (ifs.is_open())
            ifs.close();
        if (BREAK == false)
        {
            //Input File parsen
            MainWindow::data.Fe_Df_Po_Pe = getLineSectionOfFile("&POISSON", "&END POISSON", "PERIODIC", inpFile, 1);
            if (MainWindow::data.Fe_Df_Po_Pe  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> POISSON PERIODIC<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Po_Pe)+"</i>");
            MainWindow::data.Fe_Df_Po_Mu_Rc = getLineSectionOfFile("&MULTIPOLE", "&END MULTIPOLE", "RCUT", inpFile, 1);
            if (MainWindow::data.Fe_Df_Po_Mu_Rc  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> MULTIPOLE RCUT<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Po_Mu_Rc)+"</i>");
            MainWindow::data.Fe_Df_Qs_Me = getLineSectionOfFile("&QS", "&END QS", "METHOD", inpFile, 1);
            if (MainWindow::data.Fe_Df_Qs_Me  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> QS METHOD<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Qs_Me)+"</i>");
            MainWindow::data.Fe_Df_Xc_Vd_Ty = getLineSectionOfFile("&VDW_POTENTIAL", "&END VDW_POTENTIAL", "POTENTIAL_TYPE", inpFile, 1);
            if (MainWindow::data.Fe_Df_Xc_Vd_Ty  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> VDW_POTENTIAL POTENTIAL_TYPE<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Xc_Vd_Ty)+"</i>");
            MainWindow::data.Fe_Df_Xc_Vd_Pa_Rc = getLineSectionOfFile("&VDW_POTENTIAL", "&END VDW_POTENTIAL", "RCUT", inpFile, 1);
            if (MainWindow::data.Fe_Df_Xc_Vd_Pa_Rc  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> VDW_POTENTIAL RCUT<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Xc_Vd_Pa_Rc)+"</i>");
            tmpString = "";
            tmpString = getLineSectionOfFile("&VDW_POTENTIAL", "&END VDW_POTENTIAL", "CALCULATE_C9_TERM", inpFile, 1);
            if (tmpString  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> VDW_POTENTIAL CALCULATE_C9_TERM<br><i> "+QString::fromStdString(tmpString)+"</i>");
            if(std::regex_match (tmpString, std::regex("(.*)(T)(.*)")))
                MainWindow::data.Fe_Df_Xc_Vd_Pa_C9 = 1;
            else
                MainWindow::data.Fe_Df_Xc_Vd_Pa_C9 = 0;

            MainWindow::data.Fe_Df_Xc_Vd_Pa_Ty = getLineSectionOfFile("PAIR_POTENTIAL", "&END PAIR_POTENTIAL", "TYPE", inpFile, 1);
            if (MainWindow::data.Fe_Df_Xc_Vd_Pa_Ty  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> PAIR_POTENTIAL TYPE<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Xc_Vd_Pa_Ty)+"</i>");
            MainWindow::data.Fe_Su_Ce_Pe = getLineSectionOfFile("&CELL", "&END CELL", "PERIODIC", inpFile, 1);
            if (MainWindow::data.Fe_Su_Ce_Pe  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> CELL PERIODIC<br><i> "+QString::fromStdString(MainWindow::data.Fe_Su_Ce_Pe)+"</i>");
            MainWindow::data.Fe_Su_Ce_Sy = getLineSectionOfFile("&CELL", "&END CELL", "SYMMETRY", inpFile, 1);
            if (MainWindow::data.Fe_Su_Ce_Sy  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> CELL SYMMETRY<br><i> "+QString::fromStdString(MainWindow::data.Fe_Su_Ce_Sy)+"</i>");
            MainWindow::data.Mo_Ge_Op = getLineSectionOfFile("&GEO_OPT", "&END GEO_OPT", "OPTIMIZER", inpFile, 1);
            if (MainWindow::data.Mo_Ge_Op  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> GEO_OPT OPTIMIZER<br><i> "+QString::fromStdString(MainWindow::data.Mo_Ge_Op)+"</i>");
            MainWindow::data.Mo_Ce_Ty = getLineSectionOfFile("&CELL_OPT", "&END CELL_OPT", "TYPE", inpFile, 1);
            if (MainWindow::data.Mo_Ce_Ty  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> CELL_OPT TYPE<br><i> "+QString::fromStdString(MainWindow::data.Mo_Ce_Ty)+"</i>");
            MainWindow::data.Mo_Ba_Ba = getLineSectionOfFile("&BAND", "&END BAND", "BAND_TYPE", inpFile, 1);
            if (MainWindow::data.Mo_Ba_Ba  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> BAND BAND_TYPE<br><i> "+QString::fromStdString(MainWindow::data.Mo_Ba_Ba)+"</i>");
            MainWindow::data.Mo_Ba_Ks = getLineSectionOfFile("&BAND", "&END BAND", "KSPRING", inpFile, 1);
            if (MainWindow::data.Mo_Ba_Ks  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> BAND KSPRING<br><i> "+QString::fromStdString(MainWindow::data.Mo_Ba_Ks)+"</i>");
            MainWindow::data.Mo_Ba_Nu = getLineSectionOfFile("&BAND", "&END BAND", "NUMBER_OF_REPLICA", inpFile, 1);
            if (MainWindow::data.Mo_Ba_Nu  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> BAND NUMBER_OF_REPLICA<br><i> "+QString::fromStdString(MainWindow::data.Mo_Ba_Nu)+"</i>");
            tmpString = "";
            tmpString = getLineSectionOfFile("&OPTIMIZE_BAND", "&END OPTIMIZE_BAND", "OPTIMIZE_END_POINTS", inpFile, 1);
            if (tmpString  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> OPTIMIZE_BAND OPTIMIZE_END_POINTS<br><i> "+QString::fromStdString(tmpString)+"</i>");
            if(std::regex_match (tmpString, std::regex("(.*)(T)(.*)")))
                MainWindow::data.Mo_Ba_Op_Ope = 1;
            else
                MainWindow::data.Mo_Ba_Op_Ope = 0;
            MainWindow::data.Mo_Ba_Op_Opt = getLineSectionOfFile("&OPTIMIZE_BAND", "&END OPTIMIZE_BAND", "OPT_TYPE", inpFile, 1);
            if (MainWindow::data.Mo_Ba_Op_Opt  != "")
                ui->msgBoard->appendHtml("<b>FOUND</b> OPTIMIZE_BAND OPT_TYPE<br><i> "+QString::fromStdString(MainWindow::data.Mo_Ba_Op_Opt)+"</i>");
            int maxStructures;
            if (MainWindow::data.Gl_Ru == "BAND")
                std::stringstream(MainWindow::data.Mo_Ba_Nu) >> maxStructures;
            else if (MainWindow::data.Gl_Ru == "GEO_OPT" || MainWindow::data.Gl_Ru == "CELL_OPT")
                maxStructures = 1;
            else
                maxStructures = 0;

            ifs.open(inpFile);
            if (ifs.is_open())
            {
                std::vector<std::string> t_vector;
                std::string line;
                while (!ifs.eof())
                {
                    std::getline(ifs, line);
                    // &FIXED_ATOMS suchen und die Liste parsen und in 4er abspeichern mit der gefunden beschreibung zuerst, die letzten ausfüllen bis es 4 sind
                    if (std::regex_match (line, std::regex("(.*)(&FIXED_ATOMS)(.*)")))
                    {
                        std::getline(ifs, line);
                        while (!std::regex_match (line, std::regex("(.*)(&END FIXED_ATOMS)(.*)")))
                        {
                            if (std::regex_match (line, std::regex("(.*)(LIST)(.*)")))
                            {
                                for (int i = 1; i <= getMaxLineSection(line); i++)
                                    t_vector.push_back(getLineSection(line, i));
                            }
                            std::getline(ifs, line);
                        }
                        std::string ctf = getLineSectionOfFile("&FIXED_ATOMS", "&END FIXED_ATOMS", "COMPONENTS_TO_FIX", inpFile, 1);
                        int i = 0;
                        while (t_vector.size() > 0)
                        {
                            if (i == 0)
                            {
                                if (MainWindow::data.Ou_Col.size() == 0)
                                {
                                    std::vector<std::string> row;
                                    MainWindow::data.Ou_Col.push_back(row);
                                }
                                MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].push_back(ctf);
                            }
                            MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].push_back(t_vector.front());
                            t_vector.erase(t_vector.begin());
                            if (i == 3 && t_vector.size() > 0)
                            {
                                std::vector<std::string> row;
                                MainWindow::data.Ou_Col.push_back(row);
                                i = -1;
                            }
                            i++;
                        }
                        for (int i = MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].size()-1; i < 4; i++)
                        {
                            MainWindow::data.Ou_Col[MainWindow::data.Ou_Col.size()-1].push_back("FILL");
                        }
                    }
                }
            }
            if (ifs.is_open())
                ifs.close();

            ifs.open(inpFile);
            if (ifs.is_open())
            {
                std::string line;
                while (!ifs.eof() && ifs.is_open())
                {
                    std::getline(ifs, line);
                    // &XC_FUNCTIONAL
                    if (std::regex_match (line, std::regex("(.*)(&XC_FUNCTIONAL)(.*)")))
                    {
                        if (getLineSection(line, 1) != "&XC_FUNCTIONAL" && getLineSection(line, 1) != "NO_SHORTCUT")
                        {
                            MainWindow::data.Fe_Df_Xc_Fu = getLineSection(line, 1);
                            ui->msgBoard->appendHtml("<b>FOUND</b> XC_FUNCTIONAL<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Xc_Fu)+"</i>");
                            ifs.close();
                        }
                    }
                }
            }
            if (ifs.is_open())
                ifs.close();

            ifs.open(inpFile);
            if (ifs.is_open())
            {
                // Wenn COORD gefunden wird, zeile dannach
                // C    1.345345345     4.123123123     7.234234234
                // C in Elementlist in Ordnungszahl umwandeln, Coordinaten speichern
                // NumElements die anzahl der Atome speichern
                std::string line;
                while (!ifs.eof() && ifs.is_open())
                {
                    std::getline(ifs, line);
                    // &COORD
                    if (std::regex_match (line, std::regex("(.*)(&COORD)(.*)")))
                    {
                        int at_counter = 1;
                        std::getline(ifs, line);
                        while (!std::regex_match (line, std::regex("(.*)(&END COORD)(.*)")))
                        {
                            if (!std::regex_match (line, std::regex("(.*)(UNIT)(.*)")) && !std::regex_match (line, std::regex("(.*)(SCALED)(.*)")))
                            {
                                if (MainWindow::data.Gl_Ru == "ENERGY" || MainWindow::data.Gl_Ru == "ENERGY_FORCE")
                                {
                                    std::vector<std::string> row;
                                    MainWindow::data.Coords.push_back(row);
                                    MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(QString::number(at_counter).toStdString());
                                    std::string element = getLineSection(line, 0);
                                    for (int i = 1; i < 120; i++)
                                    {
                                        if (MainWindow::data.Elementlist[i] == element)
                                        {
                                            MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(QString::number(i).toStdString());
                                            MainWindow::data.NumElements[i] += 1;
                                            i = 120;
                                        }
                                    }
                                    MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(getLineSection(line, 1));
                                    MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(getLineSection(line, 2));
                                    MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(getLineSection(line, 3));
                                    if (MainWindow::data.AtKinds.size() < 1)
                                    {
                                        MainWindow::data.AtKinds.push_back(getLineSection(line, 0));
                                    }
                                    else
                                    {
                                         bool found = false;
                                         for (size_t i = 0; i < MainWindow::data.AtKinds.size(); i++)
                                         {
                                             if (MainWindow::data.AtKinds[i] == getLineSection(line, 0))
                                             {
                                                 found = true;
                                             }
                                         }
                                         if (found == false)
                                         {
                                             MainWindow::data.AtKinds.push_back(getLineSection(line, 0));
                                         }
                                    }
                                    at_counter++;
                                }
                            }
                            std::getline(ifs, line);
                        }
                        ifs.close();
                    }
                }
            }
            if (ifs.is_open())
                ifs.close();
            for (size_t i = 0; i < MainWindow::data.AtKinds.size(); i++)
            {
                std::vector<std::string> row;
                MainWindow::data.Fe_Su_Ki.push_back(row);
                MainWindow::data.Fe_Su_Ki[MainWindow::data.Fe_Su_Ki.size()-1].push_back(getLineSectionOfFile("&KIND "+MainWindow::data.AtKinds[i], "&END KIND", "BASIS_SET", inpFile, 1));
                MainWindow::data.Fe_Su_Ki[MainWindow::data.Fe_Su_Ki.size()-1].push_back(getLineSectionOfFile("&KIND "+MainWindow::data.AtKinds[i], "&END KIND", "POTENTIAL", inpFile, 1));
            }
            int tGag = 1;
            int tPog = 0;
            for (size_t i = 0; i < MainWindow::data.AtKinds.size(); i++)
            {
                if (std::regex_match (MainWindow::data.Fe_Su_Ki[i][0], std::regex("(.*)(SZV)(.*)")))
                {
                    tGag = 1;
                }
                else if (std::regex_match (MainWindow::data.Fe_Su_Ki[i][0], std::regex("(.*)(DZV)(.*)")))
                {
                    tGag = 2;
                }
                else if (std::regex_match (MainWindow::data.Fe_Su_Ki[i][0], std::regex("(.*)(TZV)(.*)")))
                {
                    tGag = 3;
                }
                else if (std::regex_match (MainWindow::data.Fe_Su_Ki[i][0], std::regex("(.*)(QZV)(.*)")))
                {
                    tGag = 4;
                }
                if (std::regex_match (MainWindow::data.Fe_Su_Ki[i][0], std::regex("(.*)(VP)(.*)")))
                {
                    tPog = 1;
                }
                else if (std::regex_match (MainWindow::data.Fe_Su_Ki[i][0], std::regex("(.*)(V2P)(.*)")))
                {
                    tPog = 2;
                }
                else if (std::regex_match (MainWindow::data.Fe_Su_Ki[i][0], std::regex("(.*)(V3P)(.*)")))
                {
                    tPog = 3;
                }
                else
                {
                    tPog = 0;
                }
                if (tPog < MainWindow::data.Fe_Su_Ce_Pog)
                {
                    MainWindow::data.Fe_Su_Ce_Pog = tPog;
                }
                if (tGag < MainWindow::data.Fe_Su_Ce_Gag)
                {
                    MainWindow::data.Fe_Su_Ce_Gag = tGag;
                }

            }
            ifs.open(inpFile);
            if (ifs.is_open())
            {
                std::string line;
                while (!ifs.eof() && ifs.is_open())
                {
                    std::getline(ifs, line);
                    if (std::regex_match (line, std::regex("(.*)(STRESS_TENSOR)(.*)")))
                    {
                        MainWindow::data.Fe_St = getLineSection(line, 1);
                        ui->msgBoard->appendHtml("<b>FOUND</b> STRESS_TENSOR<br><i> "+QString::fromStdString(MainWindow::data.Fe_St)+"</i>");
                    }
                    else if (std::regex_match (line, std::regex("(.*)(POISSON_SOLVER)(.*)")))
                    {
                        MainWindow::data.Fe_Df_Po_So = getLineSection(line, 1);
                        ui->msgBoard->appendHtml("<b>FOUND</b> POISSON_SOLVER<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Po_So)+"</i>");
                    }
                    else if (std::regex_match (line, std::regex("(.*)(EXCITATIONS)(.*)")))
                    {
                            if (std::regex_match (line, std::regex("(.*)(TDLR)(.*)")))
                                MainWindow::data.Df_Fe_Ex = 1;
                            if (std::regex_match (line, std::regex("(.*)(TDDLR)(.*)")))
                                MainWindow::data.Df_Fe_Ex = 1;
                    }
                    else if (std::regex_match (line, std::regex("(.*)(EPS_SCF)(.*)")))
                    {
                        MainWindow::data.Fe_Df_Sc_Ep = getLineSection(line, 1);
                        ui->msgBoard->appendHtml("<b>FOUND</b> EPS_SCF<br><i> "+QString::fromStdString(MainWindow::data.Fe_Df_Sc_Ep)+"</i>");
                    }
                    else if (std::regex_match (line, std::regex("(.*)(&SIC)(.*)")))
                    {
                        MainWindow::data.Fe_Df_Si = 1;
                        ui->msgBoard->appendHtml("<b>FOUND</b> SIC<br>");
                    }
                    else if (std::regex_match (line, std::regex("(.*)(&HF)(.*)")))
                    {
                        MainWindow::data.Fe_Df_Xc_Hf = 1;
                        ui->msgBoard->appendHtml("<b>FOUND</b> HF<br>");
                    }
                    else if (std::regex_match (line, std::regex("(.*)(&OPTIMIZE_END_POINTS)(.*)")))
                    {
                        tmpString = getLineSection(line, 1);
                        ui->msgBoard->appendHtml("<b>FOUND</b> OPTIMIZE_END_POINTS<br><i> "+QString::fromStdString(tmpString)+"</i>");
                        if (std::regex_match (tmpString, std::regex("(.*)(T)(.*)")))
                            MainWindow::data.oep = 1;
                    }
                }
            }
            if (ifs.is_open())
                ifs.close();
            if ((MainWindow::data.Gl_Ru == "ENERGY" || MainWindow::data.Gl_Ru == "ENERGY_FORCE" || MainWindow::data.Gl_Ru == "GEO_OPT" || MainWindow::data.Gl_Ru == "CELL_OPT") && BREAK == true)
            {
                MainWindow::data.Ou_Ene.push_back("");
                MainWindow::data.Ou_QMEne.push_back("");
                ifs.open(logFile);
                if (ifs.is_open())
                {
                    std::string line;
                    while (!ifs.eof() && ifs.is_open())
                    {
                        std::getline(ifs, line);
                        if (std::regex_match (line, std::regex("(.*)(Total energy:)(.*)")))
                        {
                            MainWindow::data.Ou_QMEne.push_back(getLineSection(line, getMaxLineSection(line)));
                        }
                        else if (std::regex_match (line, std::regex("(.*)(ENERGY)(.*)")))
                        {
                            if (std::regex_match (line, std::regex("(.*)(Total)(.*)")))
                            {
                                MainWindow::data.Ou_Ene.push_back(getLineSection(line, getMaxLineSection(line)));
                            }
                        }
                        else if (std::regex_match (line, std::regex("(.*)(Integrated absolute spin density)(.*)")))
                        {
                            MainWindow::data.Ou_Int.push_back(getLineSection(line, getMaxLineSection(line)));
                        }
                        else if (std::regex_match (line, std::regex("(.*)(Ideal and single determinant)(.*)")))
                        {
                            MainWindow::data.Ou_Sin.push_back(getLineSection(line, getMaxLineSection(line)));
                            MainWindow::data.Ou_Ide.push_back(getLineSection(line, getMaxLineSection(line)-1));
                        }
                    }
                    if (MainWindow::data.Ou_QMEne[MainWindow::data.Ou_QMEne.size()-1] == "")
                    {
                        ui->msgBoard->appendHtml("ERROR| No Energys found\t");
                        BREAK = true;
                    }
                 }
                 if (ifs.is_open())
                    ifs.close();
            }
            if ((MainWindow::data.Gl_Ru == "GEO_OPT" || MainWindow::data.Gl_Ru == "CELL_OPT") && BREAK == false)
            {
                ifs.open(logFile);
                if (ifs.is_open())
                {
                    std::string line;
                    while (!ifs.eof() && ifs.is_open())
                    {
                        std::getline(ifs, line);
                        if (std::regex_match (line, std::regex("(.*)(Internal Pressure)(.*)")))
                        {
                            MainWindow::data.Ou_Pre = getLineSection(line, getMaxLineSection(line));
                            ui->msgBoard->appendHtml("<b>FOUND</b> Internal Pressure<br><i> "+QString::fromStdString(MainWindow::data.Ou_Pre)+"</i>");
                        }
                        else if (std::regex_match (line, std::regex("(.*)(Real energy change)(.*)")))
                        {
                            MainWindow::data.Ou_Rea = getLineSection(line, getMaxLineSection(line));
                            ui->msgBoard->appendHtml("<b>FOUND</b> Real energy change<br><i> "+QString::fromStdString(MainWindow::data.Ou_Rea)+"</i>");
                        }
                        else if (std::regex_match (line, std::regex("(.*)(Max. step size)(.*)")))
                        {
                            MainWindow::data.Ou_Mas = getLineSection(line, getMaxLineSection(line));
                            ui->msgBoard->appendHtml("<b>FOUND</b> Max. step size<br><i> "+QString::fromStdString(MainWindow::data.Ou_Mas)+"</i>");
                        }
                        else if (std::regex_match (line, std::regex("(.*)(RMS step size)(.*)")))
                        {
                            MainWindow::data.Ou_Rms = getLineSection(line, getMaxLineSection(line));
                            ui->msgBoard->appendHtml("<b>FOUND</b> RMS step size<br><i> "+QString::fromStdString(MainWindow::data.Ou_Rms)+"</i>");
                        }
                        else if (std::regex_match (line, std::regex("(.*)(Max. gradient)(.*)")))
                        {
                            MainWindow::data.Ou_Maf = getLineSection(line, getMaxLineSection(line));
                            ui->msgBoard->appendHtml("<b>FOUND</b> Max. gradient<br><i> "+QString::fromStdString(MainWindow::data.Ou_Maf)+"</i>");
                        }
                        else if (std::regex_match (line, std::regex("(.*)(RMS gradient)(.*)")))
                        {
                            MainWindow::data.Ou_Rmf = getLineSection(line, getMaxLineSection(line));
                            ui->msgBoard->appendHtml("<b>FOUND</b> RMS gradient<br><i> "+QString::fromStdString(MainWindow::data.Ou_Rmf)+"</i>");
                        }
                    }
                 }
                 if (ifs.is_open())
                    ifs.close();
            }
            if (MainWindow::data.Gl_Ru == "BAND" && BREAK == false)
            {
                for (int i = 0; i < maxStructures; i++)
                {
                    MainWindow::data.Ou_QMEne.push_back("");
                }
                qDebug() << QString::number(maxStructures);
                ifs.open(logFile);
                if (ifs.is_open())
                {
                    std::string line;
                    while (!ifs.eof() && ifs.is_open())
                    {
                        std::getline(ifs, line);
                        if (std::regex_match (line, std::regex("(.*)(ENERGIES)(.*)")))
                        {
                            for (int i = 0; i < maxStructures/4; i++)
                            {
                                if (getLineSection(line, getMaxLineSection(line)-3) != "")
                                {
                                MainWindow::data.Ou_QMEne.push_back(getLineSection(line, getMaxLineSection(line)-3));
                                }
                                if (getLineSection(line, getMaxLineSection(line)-2) != "")
                                {
                                MainWindow::data.Ou_QMEne.push_back(getLineSection(line, getMaxLineSection(line)-2));
                                }
                                if (getLineSection(line, getMaxLineSection(line)-1) != "")
                                {
                                MainWindow::data.Ou_QMEne.push_back(getLineSection(line, getMaxLineSection(line)-1));
                                }
                                if (getLineSection(line, getMaxLineSection(line)) != "")
                                {
                                MainWindow::data.Ou_QMEne.push_back(getLineSection(line, getMaxLineSection(line)));
                                }
                                if (i < maxStructures/4-1)
                                    std::getline(ifs, line);
                            }
                        }
                        else if (std::regex_match (line, std::regex("(.*)(DISTANCES)(.*)")))
                        {
                            MainWindow::data.Ou_Neb_Dist.push_back("0");
                            for (int i = 0; i < maxStructures/4; i++)
                            {
                                if (getLineSection(line, getMaxLineSection(line)-3) != "")
                                {
                                    MainWindow::data.Ou_Neb_Dist.push_back(getLineSection(line, getMaxLineSection(line)-3));
                                }
                                if (getLineSection(line, getMaxLineSection(line)-2) != "")
                                {
                                    MainWindow::data.Ou_Neb_Dist.push_back(getLineSection(line, getMaxLineSection(line)-2));
                                }
                                if (getLineSection(line, getMaxLineSection(line)-1) != "")
                                {
                                    MainWindow::data.Ou_Neb_Dist.push_back(getLineSection(line, getMaxLineSection(line)-1));
                                }
                                if (getLineSection(line, getMaxLineSection(line)) != "")
                                {
                                    MainWindow::data.Ou_Neb_Dist.push_back(getLineSection(line, getMaxLineSection(line)));
                                }
                                if (i < maxStructures/4-1)
                                    std::getline(ifs, line);
                            }
                        }
                        else if (std::regex_match (line, std::regex("(.*)(MAX DISPLACEMENT)(.*)")))
                        {
                            MainWindow::data.Ou_Mas = getLineSection(line, 3);
                            ui->msgBoard->appendHtml("<b>FOUND</b> MAX DISPLACEMENT<br><i> "+QString::fromStdString(MainWindow::data.Ou_Mas)+"</i>");

                        }
                        else if (std::regex_match (line, std::regex("(.*)(RMS DISPLACEMENT)(.*)")))
                        {
                            MainWindow::data.Ou_Rms = getLineSection(line, 3);
                            ui->msgBoard->appendHtml("<b>FOUND</b> RMS DISPLACEMENT<br><i> "+QString::fromStdString(MainWindow::data.Ou_Rms)+"</i>");
                        }
                        else if (std::regex_match (line, std::regex("(.*)(MAX FORCE)(.*)")))
                        {
                            MainWindow::data.Ou_Maf = getLineSection(line, 3);
                            ui->msgBoard->appendHtml("<b>FOUND</b> MAX FORCE<br><i> "+QString::fromStdString(MainWindow::data.Ou_Maf)+"</i>");
                        }
                        else if (std::regex_match (line, std::regex("(.*)(RMF FORCE)(.*)")))
                        {
                            MainWindow::data.Ou_Rmf = getLineSection(line, 3);
                            ui->msgBoard->appendHtml("<b>FOUND</b> RMF FORCE<br><i> "+QString::fromStdString(MainWindow::data.Ou_Rmf)+"</i>");
                        }
                    }
                }
                if (ifs.is_open())
                ifs.close();
            }
            std::string projectName;
            ifs.open(inpFile);
            if (ifs.is_open())
            {
                std::string line;
                while (!ifs.eof() && ifs.is_open())
                {
                    std::getline(ifs, line);
                    if (std::regex_match (line, std::regex("(.*)(PROJECT_NAME)(.*)")))
                    {
                        projectName = getLineSection(line, getMaxLineSection(line));
                        MainWindow::data.Names.push_back(projectName);
                        ifs.close();
                    }
                }
            }
            if (ifs.is_open())
                ifs.close();
            for (int c = 0; c < maxStructures; c++)
            {
                if (MainWindow::data.Gl_Ru == "GEO_OPT" || MainWindow::data.Gl_Ru == "CELL_OPT")
                {
                    xyzFile = ui->showXYZ->text().toStdString()+projectName+"-pos-1.xyz";
                }
                else if (MainWindow::data.Gl_Ru == "BAND")
                {
                    xyzFile = ui->showXYZ->text().toStdString()+projectName+"-pos-Replica_nr_"+QString::number(c+1).toStdString()+"-1.xyz";
                }

                ifs.open(xyzFile);
                if (ifs.is_open())
                {
                    std::string line;
                    while (!ifs.eof() && ifs.is_open())
                    {
                        std::getline(ifs, line);
                        int atNum = 0;
                        std::stringstream(line) >> atNum;
                        std::getline(ifs, line);
                        for (int cc = 0; cc < atNum; cc++)
                        {
                            std::getline(ifs,line);
                            std::vector<std::string> row;
                            MainWindow::data.Coords.push_back(row);
                            MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(QString::number(cc+1).toStdString());
                            std::string element = getLineSection(line, 0);
                            for (int i = 1; i < 120; i++)
                            {
                                if (MainWindow::data.Elementlist[i] == element)
                                {
                                    MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(QString::number(i).toStdString());
                                    MainWindow::data.NumElements[i] += 1;
                                    i = 120;
                                }
                            }
                            MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(getLineSection(line,1));
                            MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(getLineSection(line,2));
                            MainWindow::data.Coords[MainWindow::data.Coords.size()-1].push_back(getLineSection(line,3));
                        }
                        ifs.close();
                    }
                    MainWindow::data.AtNum = MainWindow::data.Coords.size();
                }
                else
                {
                    qDebug() << "Cant open\t "+QString::fromStdString(xyzFile);
                    BREAK = true;
                }
            }
            //Building SumEq
            if ( BREAK == false)
            {
                for (int i = 1; i < 119; i++)
                {
                    if (MainWindow::data.NumElements[i] > 0)
                    {
                        MainWindow::data.SumEq += MainWindow::data.Elementlist[i];
                        MainWindow::data.SumEq += std::to_string(MainWindow::data.NumElements[i]);
                    }
                }
            }
            qDebug() << "END";

            if (BREAK == false)
                ui->uploadButton->setEnabled(true);
        }
    }
}

void MainWindow::on_uploadButton_clicked()
{
    MainWindow::setDBdata(); // Initieren der Verbindung
    if (MainWindow::connection.openConnection(1) == true)
    {
    //Wenn die Verbindung geöffnet werden kann, mit erstellen der Query anfangen
    //Formulierung der Query
    QString Query;
    Query = "insert into gen_inf(At_1, At_2, At_3, At_4, At_5, At_6, At_7, At_8, At_9, At_10, At_11, At_12, At_13, At_14, At_15, At_16, At_17, At_18, At_19, At_20, At_21, At_22, At_23, At_24, At_25, At_26, At_27, At_28, At_29, At_30, At_31, At_32, At_33, At_34, At_35, At_36, At_37, At_38, At_39, At_40, At_41, At_42, At_43, At_44, At_45, At_46, At_47, At_48, At_49, At_50, At_51, At_52, At_53, At_54, At_55, At_56, At_57, At_58, At_59, At_60, At_61, At_62, At_63, At_64, At_65, At_66, At_67, At_68, At_69, At_70, At_71, At_72, At_73, At_74, At_75, At_76, At_77, At_78, At_79, At_80, At_81, At_82, At_83, At_84, At_85, At_86, At_87, At_88, At_89, At_90, At_91, At_92, At_93, At_94, At_95, At_96, At_97, At_98, At_99, At_100, At_101, At_102, At_103, At_104, At_105, At_106, At_107, At_108, At_109, At_110, At_111, At_112, At_113, At_114, At_115, At_116, At_117, At_118, At_Num, Toolkit, Version, Charge, SumEq) values(";
    //einzelnen Elemente aus dem CP2K Daten in Query einfügen
    for (int i = 1; i < 119; i++)
    {
        Query += QString::number(MainWindow::data.NumElements[i]); 
        Query += ", ";
    }
    //Daten an Query anhängen die vom Daten Parser zurück gegeben wurden
    Query += QString::number(MainWindow::data.AtNum);
    Query += ",\"";
    Query += QString::fromStdString(MainWindow::data.Toolkit);
    Query += "\",\"";
    Query += QString::fromStdString(MainWindow::data.Version);
    Query += "\",\"";
    Query += QString::fromStdString(MainWindow::data.Charge);
    Query += "\",\"";
    Query += QString::fromStdString(MainWindow::data.SumEq);
    Query += "\");";
    MainWindow::connection.executeQuery(Query);

    typedef std::vector<std::string> Dim1;
    typedef std::vector<Dim1> Matrix2D;
    Matrix2D lastID(1,Dim1(1)); // Erstellen eines Objektes welches von executeReturnQuery() Daten erhalten kann
    lastID = MainWindow::connection.executeReturnQuery("SELECT LAST_INSERT_ID()"); //ID des letzten Objektes erhalten
    Query = "insert into cp2k_v2(Struct_Id, Gl_Ru_DB) values(";
    Query += QString::fromStdString(lastID[0][1]);
    Query += ",\"";
    Query += QString::fromStdString(MainWindow::data.Gl_Ru);
    Query += "\");";
    MainWindow::connection.executeQuery(Query);
    MainWindow::connection.closeConnection();   //Verbindung schließen
    MainWindow::data = cp2kData();              //Aufräumen & für nächste Transaktion bereitmachen
    ui->msgBoard->clear();                      //Aufräumen & für nächste Transaktion bereitmachen
    ui->uploadButton->setEnabled(false);        //Aufräumen & für nächste Transaktion bereitmachen
    MainWindow::on_updateTable_clicked();       //Tabelle Aktualiseiren
    }



}
