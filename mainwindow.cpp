#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createConnection()
{

    connect(ui->ouvrirAct, SIGNAL(triggered()), this, SLOT(ouvrir()));

   // connect(ui->enregistrerAct, SIGNAL(triggered()), this, SLOT(enregistrer()));

   // connect(ui->fermerAct, SIGNAL(triggered()), this, SLOT(close()));

}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox inf;

    inf.setText("OPEN Pen");
    inf.exec();
}

void MainWindow::on_action_triggered()
{
//    cacherParametre();
//    fileName = QFileDialog::getOpenFileName(this, "Open file...", QString());

//    if (!fileName.isEmpty()) {
//        QImage image(fileName);
//        image1=image;
//        m_chemin=fileName;
//        if (image1.isNull()) {
//            QMessageBox::information(this, "MainWindow ",
//                                     tr("Unable to open .").arg(fileName));
//            return;
//        }
//        int fact=image1.depth()/8;
//        im1=new TraiterImage(image1.height(),fact*image1.width());
//        this->loadImage();
//    }
}

void MainWindow::ouvrir()
{
//    cacherParametre();
    fileName = QFileDialog::getOpenFileName(this, "Open file...", QString());

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        image1=image;
        m_chemin=fileName;
        if (image1.isNull()) {
            QMessageBox::information(this, "MainWindow ",
                                     tr("Unable to open .").arg(fileName));
            return;
        }
        int fact=image1.depth()/8;
        im1=new TraiterImage(image1.height(),fact*image1.width());
        this->loadImage();
    }
}
void MainWindow::loadImage()
{

    QSize size(ui->imageLabel->width(), ui->imageLabel->height());
    QImage image2 = image1.scaled(size, Qt::KeepAspectRatio);
//    ui->imageLabel->set;
    QGraphicsScene *qwe = new QGraphicsScene(this);
    qwe->addPixmap(QPixmap::fromImage(image2));
    ui->imageLabel->setScene(qwe);
            //ui->imageLabel->setPixmap(QPixmap::fromImage(image2));


}
