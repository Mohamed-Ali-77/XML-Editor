#include "mainwindow.h"
#include "ui_mainwindow.h"
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
                    /*          Compression         */

    if(XML_ReadFile.size()==0){
        QMessageBox::warning(this,"Warning" , "There Are No File Specified to Compress ");

    }
    else{

    Comprssed_data = compression(StringOriginalData);
    sizeCompressed = Comprssed_data.size();

    QString text = QString::fromStdString(Comprssed_data);
    ui->plainTextEdit->setPlainText(text);

    QString type = "Byte pair encoding";
    QMessageBox::information(this,  "Compression Info" ,"Original File Size: "+QString::number(sizeOriginal)+" Byte\n"+
                                    "Compressed File Size: "+QString::number(sizeCompressed)+" Byte\n"+
                                    "Compression Technique: "+type);
    }

}

void MainWindow::on_pushButton_3_clicked()
{
                            /*      Decompresion        */
    unsigned int DecompressedSize;
    XML_Decompressed.clear();
    Spaces.clear();

    if(Comprssed_data.size()==0){
        QMessageBox::warning(this,"Warning" , "There Are No File Specified to DeCompress ");

    }
    else{

    DeCompresseddata = decompression(Comprssed_data);

    Spaces.resize(sizeOfXML*2);
    XML_Parser(DeCompresseddata,XML_Decompressed ,DecompressedSize);
    XML_Formating(Spaces,XML_Decompressed,XML_Decompressed.size());   //Formating after decompress data


    Output_File(Spaces, XML_Decompressed, XML_Decompressed.size(),"Decompress");
    QFile x("Decompress.xml");
    int sizeDecompreesed = x.size();
    if(!x.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
    }
    QTextStream inx(&x);
    QString Formated = inx.readAll();

    ui->plainTextEdit->setPlainText(Formated);
    x.close();
    QString type = "Byte pair decoding";
    QMessageBox::information(this,  "DeCompression Info" ,"Original File Size: "+QString::number(sizeOriginal)+" Byte\n"+
                                    "DeCompressed File Size: "+QString::number(sizeDecompreesed)+" Byte\n"+
                                    "DeCompression Technique: "+type);


    }

}

void MainWindow::on_pushButton_4_clicked()
{
                /*          Minifying        */

    if(StringOriginalData.size()==0){
        QMessageBox::warning(this,"Warning" , "There Are No File Specified to Minifying ");

    }
    else{

    string Minified_data = minifying(StringOriginalData);
    QString text = QString::fromStdString(Minified_data);
    ui->plainTextEdit->setPlainText(text);
    }

}

void MainWindow::on_pushButton_5_clicked()
{

                /*          Convert to JSON           */

    unsigned int JSONsize;
    vector<string> XML_JSONdata;


    XMLTree tree(StringOriginalData);
    JSONConverter json(tree);
    string JSONdata = json.JSONString();

    XML_Parser(JSONdata,XML_JSONdata,JSONsize);
    Output_File(XML_JSONdata , JSONsize);
    QFile x("JSONfile.json");
    if(!x.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
    }
    QTextStream inx(&x);
    QString Formated = inx.readAll();

    ui->plainTextEdit->setPlainText(Formated);
    x.close();


}

void MainWindow::on_pushButton_6_clicked()
{

                    /*     Formatting (Prettifying)        */

            Spaces.clear();
            Spaces.resize(sizeOfXML*2);      // Not working without resizing

            XML_Formating(Spaces, XML_ReadFile , XML_ReadFile.size());

            Output_File(Spaces, XML_ReadFile, XML_ReadFile.size(),"Format");
            QFile x("Format.xml");
            if(!x.open(QIODevice::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"Warning" , "Cannot Open File : " + x.errorString());
            }
            QTextStream inx(&x);
            QString Formated = inx.readAll();

            ui->plainTextEdit->setPlainText(Formated);
            x.close();


}

void MainWindow::on_pushButton_7_clicked()
{
                /*          Detection          */

    if(StringOriginalData.size() == 0){
        QMessageBox::information(this,"Information" ,"No File to Detect");      
    }
    else{

        if(Detection(currentFile.toStdString()) == true){
        QString Errors = QString::fromStdString(ErrorLines);
        QMessageBox::warning(this,"Warning" ,"There are Errors Found , Please Press Fix(Error) To Fix it \n"
                             "Errors Found at lines:  "+ Errors);
        }
        else{
        QMessageBox::information(this,"Information" ,"XML File Choosen is Correct  ");
        }
    }


}
