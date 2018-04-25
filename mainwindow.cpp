#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set number button group listener
    ui->colorSelectGroup->connect(ui->colorSelectGroup, SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(colorSelectGroup_clicked(QAbstractButton*)));
    //Set default brush size label
    ui->brushSize_label->setText("5");
    //Set default color to color indicator
    ui->colorIndicator->setStyleSheet("background-color: black");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//============================================================
//Color method
//============================================================
void MainWindow::colorSelectGroup_clicked(QAbstractButton* button)
{

    QString buttonName = button->objectName();

    //Default color - black
    QColor selectedColor;

    //Set color according to button name
    if (buttonName == "color_red") {
        selectedColor = Qt::red;
        ui->colorIndicator->setStyleSheet("background-color: red");
    }
    else {
        //Default color - black
        selectedColor = Qt::black;
        ui->colorIndicator->setStyleSheet("background-color: black");
    }
    //Call appropriate method
    ui->canvasWidget->setColor(selectedColor);

}

//============================================================
//Slider methods
//============================================================
void MainWindow::on_brushSize_slider_sliderReleased()
{
    //Call appropriate method to set brush size
    ui->canvasWidget->setBrushSize(ui->brushSize_slider->value());
}

void MainWindow::on_brushSize_slider_sliderMoved(int position)
{
    ui->brushSize_label->setText(QString::number(position));
}

void MainWindow::on_brushSize_slider_valueChanged(int value)
{
    ui->brushSize_label->setText(QString::number(value));
    ui->canvasWidget->setBrushSize(value);

}

//============================================================
//Various methods
//============================================================
void MainWindow::on_clearAll_clicked()
{
    ui->canvasWidget->clearAll();
}

void MainWindow::on_color_custom_clicked()
{
    //Open custom color dialog
    QColor customColor = QColorDialog::getColor(Qt::white, this, QString("Select a draw color"), QColorDialog::ShowAlphaChannel);
    //Update indicator and brush
    ui->colorIndicator->setStyleSheet("background-color: " + customColor.name());
    ui->canvasWidget->setColor(customColor);
}


void MainWindow::on_save_triggered()
{
    QImage canvasImage = ui->canvasWidget->getImage();
    //Get filename path (don't forget to add suffix at the end! .jpg for example)
    QString filePath = QFileDialog::getSaveFileName(this, "SaveImage", "", "PNG (*.png);;JPEG (*.jpg *.jpeg)");
    //Check if path is null
    if (filePath == "") {
        return;
    }
    //Save image
    canvasImage.save(filePath);
}

void MainWindow::on_open_triggered()
{
    //Set up image
    QString filepath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("PNG (*.png)" )
                );

    if (filepath != "") {
        QImage canvasImage = QImage(filepath);
        ui->canvasWidget->setCanvasImage(canvasImage);
    }
}
