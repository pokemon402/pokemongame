#include "start.h"
#include "ui_start.h"
#include "mainwindow.h"

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_clicked()
{
    MainWindow *game=new MainWindow;
    game->show();
    this->close();
}
