#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xml_parser.h"
#include "compression.h"
#include "main.h"

string fileInAstring = "";
int key=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionopen_triggered()
{
        XML_ReadFile.clear();
        Spaces.clear();
    
        QString filter = "All Files (*.*) ;; XML Files (*.xml)";
        QString filename = QFileDialog::getOpenFileName(this,"Open File","C://",filter);
        QFile file(filename);
    
        sizeOriginal = file.size();
        currentFile = filename;
    
        if(!file.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning" , "Cannot Open File : " + file.errorString());
        }
        setWindowTitle(filename);
        QTextStream in(&file);
        QString text = in.readAll();

        ui->plainTextEdit->setPlainText(text);
        StringOriginalData = text.toStdString();
    
        XML_Parser(StringOriginalData,XML_ReadFile,sizeOfXML);
    
        file.close();
}


void MainWindow::on_actionNew_triggered()
{
    XML_ReadFile.clear();
    Spaces.clear();
    Comprssed_data.clear();
    DeCompresseddata.clear();
    XML_Corrected.clear();
    setWindowTitle("XML-Manager");
    currentFile.clear();
    ui->plainTextEdit->setPlainText(QString());
}




void MainWindow::on_actionexit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionSave_triggered()
{
         QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                    "untitled.xml",
                                    tr("XML files (*.xml);;Text files (*.txt);;JSON files(*.json"));
        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning" , "Cannot Save File : " + file.errorString());
            return;
        }
        currentFile = filename;
        setWindowTitle(filename);
        QTextStream out(&file);
        QString text = ui->plainTextEdit->toPlainText();
        out << text;
        file.close();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_pushButton_clicked()
{
                             /*         CHECK CORRECTNESS           */

    unsigned int CorrectedSize;
    XML_Corrected.clear();
    Spaces.clear();
    string CorrectedData = Correction(currentFile.toStdString());  //Function take filename
    XML_Parser(CorrectedData,XML_Corrected ,CorrectedSize);
    Spaces.resize(sizeOfXML*2);
    XML_Formating(Spaces,XML_Corrected,XML_Corrected.size());

    Output_File(Spaces, XML_Corrected, XML_Corrected.size(),"Fixed");
    QFile x("Fixed.xml");

    if(!x.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
    }
    QTextStream inx(&x);
    QString Corrected = inx.readAll();

    ui->plainTextEdit->setPlainText(Corrected);
    x.close();
}


void MainWindow::on_pushButton_2_clicked()
{

}

