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

