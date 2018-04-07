#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <encrypter.h>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <iostream>
#include <fstream>

encrypter myEncrypter;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ReadTextButton_released()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Wybierz plik"), "/", tr("Text files (*.txt)"));

    myEncrypter.readText(path);

    ui->InputText->setText(myEncrypter.inText);
}

void MainWindow::on_EncryptButton_released()
{
    myEncrypter.inText = ui->InputText->toPlainText();

    if(myEncrypter.inText.length()==0){
        QMessageBox::information(this, "Błąd", "Podaj tekst");
        return;
    }

    myEncrypter.newencrypt();

    ui->OutputText->setText(myEncrypter.outText);
}

void MainWindow::on_DecryptButton_released()
{
    myEncrypter.inText = ui->InputText->toPlainText();

    if(myEncrypter.inText.length()==0){
        QMessageBox::information(this, "Błąd", "Podaj tekst");
        return;
    }

    myEncrypter.newdecrypt();

    ui->OutputText->setText(myEncrypter.outText);
}

void MainWindow::on_SaveTextButton_released()
{
    myEncrypter.outText = ui->OutputText->toPlainText();

    if(myEncrypter.outText.length()==0){
        QMessageBox::information(this, "Błąd", "Brak tekstu");
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, tr("Wybierz plik"), "/", tr("Text files (*.txt)"));

    myEncrypter.saveText(path);
}
