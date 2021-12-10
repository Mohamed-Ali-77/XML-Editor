#include <QApplication>
#include "mainwindow.h"
#include "main.h"
using namespace std;

unsigned int NumOfLines = 0;
unsigned int sizeOfXML =0;

vector<string> XML_ReadFile;


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
