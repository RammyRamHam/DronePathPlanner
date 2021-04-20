#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QCompleter>
#include <QDebug>
#include <math.h>
#include <algorithm>
#include "../backend/sorter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    class Sort {
    public:
        enum SortType {BUBBLE, SELECTION, QUICK, MERGE} type;
        enum Ordering {RANDOM, ASCENDING, DESCENDING} order;
        int num;

        Sort(SortType sortType, Ordering ordering, int numElements) :
            type(sortType), order(ordering), num(numElements) {};

        static std::string typeString(SortType type) {
            switch(type) {
                case Sort::BUBBLE:
                     return "Bubble Sort";
                    break;
                case Sort::SELECTION:
                    return "Selection Sort";
                    break;
                case Sort::QUICK:
                    return "Quick Sort";
                    break;
                case Sort::MERGE:
                    return "Merge Sort";
                    break;
            }
        }

        static std::string orderString(Ordering order) {
            switch(order) {
                case Sort::RANDOM:
                     return "Random";
                    break;
                case Sort::ASCENDING:
                    return "Ascending";
                    break;
                case Sort::DESCENDING:
                    return "Descending";
                    break;
            }
        }


    };

private slots:
    void on_genNum_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    bool numGenValid = false;
    std::vector<Sort> sortList;
    int numTest = 0;

    void validInputFeedback(QLineEdit *lineEdit, bool validIndicator);
    void genRandomElements();
    void addToSortList();
    void removeSort();
    void runSorts();

};
#endif // MAINWINDOW_H
