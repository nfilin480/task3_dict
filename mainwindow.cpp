#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString fileName = ":/mueller.dict";
    statusBar(fileName);
    load_dictionary(fileName);
    ui->wordList->addItems(words);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_dictionary(QString fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    QString line;
    QString word;
    QString translation;

    while (!in.atEnd()){
        line = in.readLine();
        if(!line.isEmpty() && !line[0].isSpace()){
            if(!word.isEmpty()){
                words.append(word);
                translations.insert(word, translation);
            }
            word = line.simplified();
            translation = word;
        } else
            translation = translation + QString("\n") + line;

    }

    if(!word.isEmpty()){
            words.append(word);
            translations.insert(word, translation);
    }



    file.close();
}

void MainWindow::on_wordList_currentTextChanged(const QString &currentText)
{
    ui->translationArea->setPlainText(translations[currentText]);
}

void MainWindow::on_searchLine_textChanged(const QString &arg1)
{
    QRegExp rx(arg1);
    ui->wordList->clear();
    ui->wordList->addItems(words.filter(rx));
}

void MainWindow::openNewDictionary(){
    QString fileName =  QFileDialog:: getOpenFileName(this, tr("Open Dictionary"), "D:/",  tr("Dictionary Files ( *.dict)"));
    words.clear();
    translations.clear();
    load_dictionary(fileName);
    ui->wordList->clear();
    ui->translationArea->clear();
    ui->wordList->addItems(words);
    statusBar(fileName);
}

void MainWindow::statusBar(QString fileName){
    QString a = QCoreApplication::applicationDirPath();
    a.append("/mueller.dict");
    if ((fileName == ":/mueller.dict") || (fileName == a))
    fileName = tr("Standart dictionary");
    ui->statusbar->showMessage(fileName);
}
