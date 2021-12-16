#include <QApplication>
#include "mainwindow.h"
#include "main.h"
using namespace std;

string ErrorLines;
string StringOriginalData;
string Comprssed_data="";
string DeCompresseddata="";
unsigned int sizeOfXML = 0;
unsigned int sizeOriginal= 0;
unsigned int sizeCompressed= 0;

vector<string> XML_ReadFile;
vector<string> XML_Decompressed;
vector<string> XML_Corrected;
vector<string> XML_JSONdata;
vector<string> XML_EncodedPairs;
vector<char> XML_CodingCharacters;
vector<string> Spaces;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void Output_File( const vector<string> &XML_string, int size)	  // For JSON File
{
    fstream newfile;
    newfile.open("JSONfile.json",ios::out);
    if(newfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            newfile << XML_string[i] << "\n";
        }
    }
}

void Output_File(const vector<string> &Spaces, const vector<string> &XML_string, int size, string caller)
{
    fstream newfile;
    string fname;
    if(caller == "Format"){
        fname = "Format.xml";
    }
    else if(caller == "Decompress")
        {
            fname = "Decompress.xml";
        }
    else if(caller == "Minified"){
        fname = "Minified.xml";
    }
    else if (caller == "Fixed"){
        fname = "Fixed.xml";
    }
    newfile.open(fname,ios::out);
    if(newfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            newfile << Spaces[i] << XML_string[i] << "\n";
        }
    }
}
