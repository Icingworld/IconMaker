#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include <QRgb>
#include <QDebug>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Check
{
private:
    QVector <QCheckBox *> list;
public:
    Check();
    ~Check();
    void add(QCheckBox * checkbox);
    void select(const int index);
    void show();
    void hide();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Warning(const QString & string);
    void ImgShow(QLabel * label, QImage img);
    void Process();
    double GetDistance(int i, int j, int x, int y);
    Check shapes, sizes, angles;
    int shape, size;
    double angle;
    QString Path, path, fileName;
    QImage img, newimg;
    QString defaultcolor;


private slots:
    void on_shape1_clicked();
    void on_shape2_clicked();
    void on_angle1_clicked();
    void on_angle2_clicked();
    void on_angle3_clicked();
    void on_angle4_clicked();
    void on_size1_clicked();
    void on_size2_clicked();
    void on_size3_clicked();
    void on_size4_clicked();
    void on_size5_clicked();
    void on_size6_clicked();
    void on_size7_clicked();
    void on_choose_clicked();
    void on_save_clicked();
    void on_clear_clicked();
    void on_background_clicked();


private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
