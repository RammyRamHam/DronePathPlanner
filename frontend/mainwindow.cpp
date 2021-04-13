#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->genNum, &QLineEdit::returnPressed, this, &MainWindow::genRandomAddresses);
    connect(ui->genAddresses, &QPushButton::clicked, this, &MainWindow::genRandomAddresses);

    //connect(ui->genNum, SIGNAL(returnPress()), this, SLOT(genRandomAddresses()));
    //connect(ui->genAddresses, SIGNAL(clicked()), this, SLOT(genRandomAddresses()));

    connect(ui->addressInput, &QLineEdit::returnPressed, [=](){addToAddressList();});
    connect(ui->addAddress, &QPushButton::clicked, [=](){addToAddressList();});

    connect(ui->removeAddress, &QPushButton::clicked, this, &MainWindow::removeAddress);

    ui->splitter->setSizes({310, 900});

    QStringList strings = {"1234 Test Dr. Gainesville, FL", "1234 Test2 Dr. Gainesville, FL"};
    QCompleter *completer = new QCompleter(strings, this);
    completer->setMaxVisibleItems(10);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->addressInput->setCompleter(completer);

 }

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addToAddressList(QString toAdd) {
    if (toAdd == "") {
        QString suggestedAddress = ui->addressInput->completer()->currentCompletion();
        QString currAddress = ui->addressInput->text();
        if (suggestedAddress != currAddress) {
            return;
        }

        toAdd = ui->addressInput->text();
    }

    if (std::find(addresses.begin(), addresses.end(), toAdd.toStdString()) == addresses.end()) {
        addresses.push_back(toAdd.toStdString());
        new QListWidgetItem(toAdd, ui->addressList);
    }
}

void MainWindow::genRandomAddresses() {
    if (numGenValid) {
        int numGen = ui->genNum->text().toInt();
        for (int i = 0; i < numGen; i++) {
            int toSelect = rand();
            QString selected = QString::number(toSelect);
            addToAddressList(selected);
        }
    }
}

void MainWindow::removeAddress() {
    if (!ui->addressList->currentItem()) {
        return;
    }

    std::string toDel = ui->addressList->currentItem()->text().toStdString();
    std::vector<std::string>::iterator delIndex = std::find(addresses.begin(), addresses.end(), toDel);
    if (delIndex != addresses.end()) {
        addresses.erase(delIndex);
        ui->addressList->takeItem(ui->addressList->currentRow());
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

void MainWindow::on_addressInput_textChanged(const QString &arg1) {
    bool possibleAddress = ui->addressInput->completer()->currentCompletion() != "";
    validInputFeedback(ui->addressInput, possibleAddress);
}

void MainWindow::on_genNum_textChanged(const QString &arg1) {
    numGenValid = arg1.toInt() > 0;
    validInputFeedback(ui->genNum, numGenValid);
}

void MainWindow::on_nearestNeighbor_clicked() {

}

void MainWindow::on_christofides_clicked() {

}

void MainWindow::on_dijkstra_clicked() {

}


