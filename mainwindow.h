#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QMessageBox>

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
    Check shapes, sizes, angles;
    int shape, size, angle;
    QString Path, path, fileName;
    QImage img, newimg;


private slots:
    void on_shape1_stateChanged(int arg1);

    void on_shape2_stateChanged(int arg1);

    void on_angle1_stateChanged(int arg1);

    void on_angle2_stateChanged(int arg1);

    void on_angle3_stateChanged(int arg1);

    void on_angle4_stateChanged(int arg1);

    void on_size1_stateChanged(int arg1);

    void on_size2_stateChanged(int arg1);

    void on_size3_stateChanged(int arg1);

    void on_size4_stateChanged(int arg1);

    void on_size5_stateChanged(int arg1);

    void on_size6_stateChanged(int arg1);

    void on_size7_stateChanged(int arg1);

    void on_choose_clicked();

    void on_save_clicked();

    void on_clear_clicked();

    void on_edit_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
