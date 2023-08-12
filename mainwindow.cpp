#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    ui->statusbar->showMessage("OK");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QFile mFile(QFileDialog::getOpenFileName(this, "Select file", "C:/", "Text File (*.txt);; All Files (*.*);"));

    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this, "Error", "Error open file");
        ui->statusbar->showMessage("Error open file");
        return;
    }
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textEdit->setText(buffer);
    ui->statusbar->showMessage("Read to file");
    mFile.flush();
    mFile.close();
}


void MainWindow::on_actionSave_File_triggered()
{
    QFile mFile(QFileDialog::getSaveFileName());
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::information(this, "Error", "Error save file");
        ui->statusbar->showMessage("Error save file");
        return;
    }
    QTextStream stream(&mFile);
    stream << ui->textEdit->toPlainText();
    ui->statusbar->showMessage("Write to file");
    mFile.close();
}

