#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QCompleter>
#include <math.h>
#include <algorithm>

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

    void on_nearestNeighbor_clicked();

    void on_christofides_clicked();

    void on_dijkstra_clicked();

    void on_genNum_textChanged(const QString &arg1);

    void on_addressInput_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    bool numGenValid = false;
    std::vector<std::string> addresses;

    void addToAddressList(QString toAdd = "");
    void validInputFeedback(QLineEdit *lineEdit, bool validIndicator);
    void genRandomAddresses();
    void removeAddress();

};
#endif // MAINWINDOW_H
