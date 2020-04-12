#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_wordList_currentTextChanged(const QString &currentText);

    void on_searchLine_textChanged(const QString &arg1);

    void openNewDictionary();

private:
    Ui::MainWindow *ui;
    void load_dictionary(QString fileName);
    QStringList words;
    QHash<QString, QString> translations;
    void statusBar(QString fileName);
};
#endif // MAINWINDOW_H
