#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("IconMaker by jzw");
    setWindowIcon(QIcon(":/Icon.png"));
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    ui->choose->setFocus();
    shapes.add(ui->shape1);
    shapes.add(ui->shape2);
    sizes.add(ui->size1);
    sizes.add(ui->size2);
    sizes.add(ui->size3);
    sizes.add(ui->size4);
    sizes.add(ui->size5);
    sizes.add(ui->size6);
    sizes.add(ui->size7);
    angles.add(ui->angle1);
    angles.add(ui->angle2);
    angles.add(ui->angle3);
    angles.add(ui->angle4);
    ui->clear->setToolTip("Clear all");
    ui->background->setToolTip("Change background color between None & White");
    ui->newname->setEnabled(false);
    ui->save->setEnabled(false);
    on_angle3_clicked();
    on_shape1_clicked();
    on_size6_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Check::Check()
{

}

Check::~Check()
{

}

void Check::add(QCheckBox * checkbox)
{
    list.append(checkbox);
}

void Check::select(const int index)
{
    for (int i=0;i<list.length();i++) {
        if (i != index)
        {
            list[i]->setChecked(false);
        } else {
            list[i]->setChecked(true);
        }
    }
}

void Check::show()
{
    foreach (QCheckBox * checkbox, list) {
        checkbox->setVisible(true);
    }
}

void Check::hide()
{
    foreach (QCheckBox * checkbox, list) {
        checkbox->setVisible(false);
    }
}


void MainWindow::Warning(const QString & string)
{
    QMessageBox messageBox;
    messageBox.setWindowTitle("Warning");
    messageBox.setText(string);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.addButton("confirm", QMessageBox::AcceptRole);
    messageBox.exec();
}


void MainWindow::ImgShow(QLabel * label, QImage img)
{
    QImage img1, img2;
    if (img.width() > label->width())
    {
        img1 = img.scaled(label->width(), img.height() * (label->width() / static_cast<float>(img.width())));
    } else {
        img1 = img;
    }
    if (img1.height() > label->height())
    {
        img2 = img1.scaled(img1.width() * (label->height() / static_cast<float>(img1.height())), img1.height());
    } else {
        img2 = img1;
    }
    label->setPixmap(QPixmap::fromImage(img2));
    label->show();
}


void MainWindow::Process()
{
    if (Path != "")
    {
        ui->newimg->setStyleSheet(defaultcolor);
    }
    int radius = 0.5 * angle * size;
    if (img.size() != QSize(0, 0))
    {
        newimg = img.scaled(size, size);
        if (shape == 0)
        {
            for (int i=0;i<size;i++) {
                for (int j=0;j<size;j++) {
                    if (i <= radius && j <= radius && GetDistance(i, j, radius, radius) >= radius)
                    {
                        newimg.setPixel(i, j, qRgba(0,0,0,0));
                    } else if (i <= radius && j >= size - radius && GetDistance(i, j, radius, size - radius) >= radius) {
                        newimg.setPixel(i, j, qRgba(0,0,0,0));
                    } else if (i >= size - radius && j <= radius && GetDistance(i, j, size - radius, radius) >= radius) {
                        newimg.setPixel(i, j, qRgba(0,0,0,0));
                    } else if (i >= size - radius && j >= size - radius && GetDistance(i, j, size - radius, size - radius) >= radius) {
                        newimg.setPixel(i, j, qRgba(0,0,0,0));
                    }
                }
            }
        }
        ImgShow(ui->newimg, newimg);
    }
}


double MainWindow::GetDistance(int i, int j, int x, int y)
{
    return sqrt(pow(i - x, 2) + pow(j - y, 2));
}


void MainWindow::on_shape1_clicked()
{
    shapes.select(0);
    angles.show();
    ui->label_6->setVisible(true);
    shape = 0;
    Process();
}


void MainWindow::on_shape2_clicked()
{
    shapes.select(1);
    angles.hide();
    ui->label_6->setVisible(false);
    shape = 1;
    Process();
}


void MainWindow::on_angle1_clicked()
{
    angles.select(0);
    angle = 0.25;
    Process();
}


void MainWindow::on_angle2_clicked()
{
    angles.select(1);
    angle = 0.33;
    Process();
}


void MainWindow::on_angle3_clicked()
{
    angles.select(2);
    angle = 0.5;
    Process();
}


void MainWindow::on_angle4_clicked()
{
    angles.select(3);
    angle = 1.0;
    Process();
}


void MainWindow::on_size1_clicked()
{
    sizes.select(0);
    size = 16;
    Process();
}


void MainWindow::on_size2_clicked()
{
    sizes.select(1);
    size = 32;
    Process();
}


void MainWindow::on_size3_clicked()
{
    sizes.select(2);
    size = 48;
    Process();
}


void MainWindow::on_size4_clicked()
{
    sizes.select(3);
    size = 64;
    Process();
}


void MainWindow::on_size5_clicked()
{
    sizes.select(4);
    size = 128;
    Process();
}


void MainWindow::on_size6_clicked()
{
    sizes.select(5);
    size = 256;
    Process();
}


void MainWindow::on_size7_clicked()
{
    sizes.select(6);
    size = 512;
    Process();
}


void MainWindow::on_choose_clicked()
{
    Path = QFileDialog::getOpenFileName(this, "Choose a image file", "/", "(*.png *.jpg *.jpeg *.bmp)");
    if (Path.isEmpty())
    {
        qDebug() << "Error";
    }
    else
    {
        QFileInfo fileInfo(Path);
        path = fileInfo.path();
        fileName = fileInfo.fileName();
        ui->rawname->setText(fileName);
        ui->newname->setText("logo.ico");
        ui->newname->setEnabled(true);
        ui->save->setEnabled(true);
        img.load(Path);
        ImgShow(ui->rawimg, img);
        Process();
    }
}


void MainWindow::on_save_clicked()
{
    if (ui->newname->text() == "")
    {
        Warning("FileName necessary!");
    } else {
        QString newname = ui->newname->text();
        newimg.save(path + "/" + newname);
    }
}


void MainWindow::on_clear_clicked()
{
    ui->shape1->setChecked(true);
    ui->size4->setChecked(true);
    ui->angle2->setChecked(true);
    ui->rawimg->clear();
    ui->newimg->clear();
    ui->rawname->clear();
    ui->newname->clear();
    ui->newname->setEnabled(false);
    ui->save->setEnabled(false);
    ui->newimg->setStyleSheet("background:white");
}


void MainWindow::on_background_clicked()
{
    if (defaultcolor == "")
    {
        defaultcolor = "background:white";
    } else {
        defaultcolor = "";
    }
    ui->newimg->setStyleSheet(defaultcolor);
}
