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

            newfile << JSON_string;
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

void Graphfile(SocialGraph& Graph){

      ofstream myfile("graph.dot");
      string Colors[] = {"[color=blue]\n","[color=red]\n","[color=green]\n"};

      myfile<<"digraph{\n";
      myfile<<"bgcolor=\"lightyellow\"\n";

      for(int i =1; i<Graph.usersSocialNodes.size(); i++){
          SocialNode* user = Graph.usersSocialNodes[i];
                  myfile << user->id<< Colors[i-1];
                  myfile << user->id<<"-> {";
            for(int k = 0; k<user->followers.size(); k++){
                myfile<<user->followers[k]<<" ";
            }
            myfile<<"}\n";
      }
      myfile<<"}";

      myfile.close();
}
