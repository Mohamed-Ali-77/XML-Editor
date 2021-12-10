#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include "xml_parser.h"

extern string fileInAstring;
extern int key;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionopen_triggered();

    void on_actionNew_triggered();


    void on_actionexit_triggered();

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_pushButton_clicked();               //Check Correctness

    void on_pushButton_2_clicked();             //Compress file
    
    void on_pushButton_clicked();               //Check Correctness

    void on_pushButton_2_clicked();             //Compress file

    void on_pushButton_3_clicked();             //Decompress file

    void on_pushButton_4_clicked();             //Minifying

    void on_pushButton_5_clicked();             /*Convert to JSON*/

    void on_pushButton_6_clicked();             /*Formatting (Prettifying)*/

    void on_pushButton_7_clicked();             /* Detect for errors*/

private:
    Ui::MainWindow *ui;
    QString currentFile;
};
#endif // MAINWINDOW_H
