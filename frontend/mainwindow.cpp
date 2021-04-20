#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MAX_ELEMENTS 200000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(ui->genNum, &QLineEdit::returnPressed, this, &MainWindow::genRandomElements);
    connect(ui->genSort, &QPushButton::clicked, this, &MainWindow::addToSortList);
    connect(ui->removeSort, &QPushButton::clicked, this, &MainWindow::removeSort);
    connect(ui->runSorts, &QPushButton::clicked, this, &MainWindow::runSorts);

    ui->splitter->setSizes({310, 900});

    ui->dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sortList->setEditTriggers(QAbstractItemView::NoEditTriggers);
 }

MainWindow::~MainWindow() {
    delete ui;
}

//void MainWindow::genRandomElements() {
//    if (numGenValid) {
//        int numGen = ui->genNum->text().toInt();
//        for (int i = 0; i < numGen; i++) {
//            int toSelect = rand();
//            QString selected = QString::number(toSelect);
//            addToAddressList(selected);
//        }
//    }
//}

void MainWindow::addToSortList() {
    Sort::SortType type;
    switch(ui->sortType->currentIndex()) {
        case 0:
            return;
        case 1:
             type = Sort::BUBBLE;
            break;
        case 2:
            type = Sort::SELECTION;
            break;
        case 3:
            type = Sort::QUICK;
            break;
        case 4:
            type = Sort::MERGE;
            break;
    }

    Sort::Ordering order;
    switch(ui->sortOrder->currentIndex()) {
        case 0:
            return;
        case 1:
             order = Sort::RANDOM;
            break;
        case 2:
            order = Sort::WORST;
            break;

        case 3:
            order = Sort::BEST;
            break;
    }

    int num = ui->genNum->text().toInt();
    ui->sortList->insertRow(0);

    ui->sortList->setItem(0, 0, new QTableWidgetItem());
    ui->sortList->setItem(0, 1, new QTableWidgetItem());
    ui->sortList->setItem(0, 2, new QTableWidgetItem());

    QString label = QString::fromStdString(Sort::typeString(type));
    ui->sortList->item(0,0)->setText(label);

    label = QString::number(num);
    ui->sortList->item(0,1)->setText(label);

    label = QString::fromStdString(Sort::orderString(order));
    ui->sortList->item(0,2)->setText(label);

    sortList.push_back(Sort(type, order, num));
    //new QListWidgetItem(label, ui->sortList);
}


void MainWindow::removeSort() {
    if (ui->sortList->currentRow() == -1) {
        return;
    }

    for (int i = 0; i < sortList.size(); i++) {
        if (sortList[i].num == ui->sortList->item(ui->sortList->currentRow(), 1)->text().toInt() &&
            Sort::typeString(sortList[i].type) == ui->sortList->item(ui->sortList->currentRow(), 0)->text().toStdString() &&
            Sort::orderString(sortList[i].order) == ui->sortList->item(ui->sortList->currentRow(), 2)->text().toStdString()) {

            sortList.erase(sortList.begin() + i);
            ui->sortList->removeRow(ui->sortList->currentRow());
            break;
        }
    }
}


void MainWindow::validInputFeedback(QLineEdit *lineEdit, bool validIndicator) {
    QPalette pal = palette();
    QColor currDefaultColor = qApp->palette().color(QPalette::Window);

    if (validIndicator) {
        pal.setColor(QPalette::Base, currDefaultColor);
    } else {
        pal.setColor(QPalette::Base, QColor(255, 148, 148, 255));
    }

    lineEdit->setAutoFillBackground(true);
    lineEdit->setPalette(pal);
}


void MainWindow::on_genNum_textChanged(const QString &arg1) {
    validInputFeedback(ui->genNum, arg1.toInt() < MAX_ELEMENTS);
}



void MainWindow::runSorts() {
    if (sortList.size()) {
        for (Sort currSort : sortList) {
            ui->dataTable->insertRow(0);

            ui->dataTable->setItem(0, 0, new QTableWidgetItem());
            ui->dataTable->setItem(0, 1, new QTableWidgetItem());
            ui->dataTable->setItem(0, 2, new QTableWidgetItem());
            ui->dataTable->setItem(0, 3, new QTableWidgetItem());

            ui->dataTable->item(0,0)->setText("");
            ui->dataTable->item(0,1)->setText(QString::fromStdString(Sort::typeString(currSort.type)));
            ui->dataTable->item(0,2)->setText(QString::number(currSort.num));
            ui->dataTable->item(0,3)->setText(QString::fromStdString(Sort::orderString(currSort.order)));
        }

        ui->dataTable->item(0,0)->setText(QString::number(numTest++));

        ui->sortList->clearContents();
        ui->sortList->setRowCount(0);
        sortList.clear();
    }
}




//    connect(ui->genNum, &QLineEdit::returnPressed, this, &MainWindow::genRandomAddresses);
//    connect(ui->genAddresses, &QPushButton::clicked, this, &MainWindow::genRandomAddresses);

//    //connect(ui->genNum, SIGNAL(returnPress()), this, SLOT(genRandomAddresses()));
//    //connect(ui->genAddresses, SIGNAL(clicked()), this, SLOT(genRandomAddresses()));

//    connect(ui->addressInput, &QLineEdit::returnPressed, [=](){addToAddressList();});
//    connect(ui->addAddress, &QPushButton::clicked, [=](){addToAddressList();});

//    connect(ui->removeAddress, &QPushButton::clicked, this, &MainWindow::removeAddress);


