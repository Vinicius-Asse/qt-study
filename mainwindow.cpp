#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(filename, QString()) != 0 )
    {
        bool isValid = image.load(filename);

        if (isValid)
        {
            QLabel* label = ui->imageView;

            // Setup Image
            image = image.scaled(label->width(), label->height(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
            label->setPixmap(QPixmap::fromImage(image));

            // Setup Sliders
            QSlider* rSlider = ui->rColorSlider;
            QSlider* gSlider = ui->gColorSlider;
            QSlider* bSlider = ui->bColorSlider;
            QSlider* imageScaleSlider = ui->imageScaleSlider;
            QPushButton* saveButton = ui->saveFileButton;

            rSlider->setEnabled(true);
            gSlider->setEnabled(true);
            bSlider->setEnabled(true);
            imageScaleSlider->setEnabled(true);
            saveButton->setEnabled(true);
        }
        else
        {
            // Handle Invalid Image
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    on_openFileButton_clicked();
}

void MainWindow::on_saveFileButton_clicked()
{
    on_actionSave_as_triggered();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save as"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(filename, QString()) != 0 )
    {
        QImage newImage = updateImage();

        bool isValid = newImage.save(filename);

        if (isValid)
        {
            printf("OK: FILE SAVED!\n");
        }
        else
        {
            printf("NOK: FILE NOT SAVED!\n");
        }
    }
}

void MainWindow::on_rColorSlider_valueChanged(int value)
{
    r = value / 100.0;
    updateView();
}

void MainWindow::on_gColorSlider_valueChanged(int value)
{
    g = value / 100.0;
    updateView();
}

void MainWindow::on_bColorSlider_valueChanged(int value)
{
    b = value / 100.0;
    updateView();
}

void MainWindow::on_imageScaleSlider_valueChanged(int value)
{
    scale = 1 + value / 100.0;
    updateView();
}

QImage MainWindow::updateImage()
{
    if (!image.isNull())
    {
        QImage newImage = QImage(image);
        int width = newImage.width();
        int height = newImage.height();

        QRgb color;
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                color = image.pixel(i, j);
                newImage.setPixel(i, j, qRgb(qRed(color) * r, qGreen(color) * g, qBlue(color) * b));
            }
        }

        return newImage.scaled(QSize(width * scale, height * scale));
    }
    return image;
}

void MainWindow::updateView()
{
    QImage newImage = updateImage();
    ui->imageView->setPixmap(QPixmap::fromImage(newImage));
}
