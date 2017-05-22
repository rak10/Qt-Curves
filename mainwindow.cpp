#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->spinScale->setValue(this->ui->renderArea->scale());
    this->ui->spinInterval->setValue(this->ui->renderArea->interval());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui()
{
     this->ui->spinScale->setValue(this->ui->renderArea->scale());
     this->ui->spinInterval->setValue(this->ui->renderArea->interval());
     this->ui->spinCount->setValue(this->ui->renderArea->stepCount());
}


void MainWindow::on_btnAsteroid_clicked()
{
    // change background color for render area
    this->ui->renderArea->setShape(RenderArea::Asteroid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
        this->ui->renderArea->setScale (scale);
}

void MainWindow::on_spinInterval_valueChanged(double interval)
{
    this->ui->renderArea->setInterval (interval);
}

void MainWindow::on_spinCount_valueChanged(int count)
{
    this->ui->renderArea->setStepCount(count);
}

void MainWindow::on_btnBackground_clicked()
{
    QColor colour = QColorDialog::getColor(ui->renderArea->backgroundColor(), this, "Select Color");
    ui->renderArea->setBackgroundColor(colour);
}

void MainWindow::on_btnLineColour_clicked()
{
    QColor lineColour = QColorDialog::getColor(ui->renderArea->shapeColor(), this, "Select Color");
    ui->renderArea->setShapeColor(lineColour);
}
