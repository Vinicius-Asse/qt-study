#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string>

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
    void on_openFileButton_clicked();
    void on_saveFileButton_clicked();

    void on_rColorSlider_valueChanged(int value);
    void on_gColorSlider_valueChanged(int value);
    void on_bColorSlider_valueChanged(int value);

    void on_imageScaleSlider_valueChanged(int value);

    void on_actionSave_as_triggered();
    void on_actionOpen_triggered();


private:
    Ui::MainWindow *ui;
    QImage image;
    float scale = 1, r = 1, g = 1, b = 1;

    QImage updateImage();
    void updateView();
    void saveImage();

};
#endif // MAINWINDOW_H
