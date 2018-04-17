#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QString>
//#include <QPrintDialog>
#include <QFileDialog>
#include <QMainWindow>
//#include <QPrinter>
#include "traiterimage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void createConnection();
    void ouvrir();
    void on_action_triggered();

    void loadImage();

private:
//    TraiterImage* im1; // class TraiterImage
    QImage image1;
    QImage image2;
    QString m_chemin;
    QString fileName;
    TraiterImage* im1;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
