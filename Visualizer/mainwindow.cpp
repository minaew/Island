#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QFile>
#include <QTextStream>

const int cellSize = 15;
const int x_offset = 50;
const int y_offset = 50;

MainWindow::MainWindow(QString filePath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _filePath = filePath;
}

QBrush cellToBrush(QChar c)
{
    if (c == QChar('B'))
    {
        return Qt::black;
    }

    if (c == QChar('F'))
    {
        return Qt::green;
    }

    if (c == QChar('<') ||
        c == QChar('^') ||
        c == QChar('>') ||
        c == QChar('V'))
    {
        return Qt::red;
    }

    return Qt::white;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QFile file(_filePath);

    file.open(QFile::ReadOnly);

    QTextStream stream(&file);

    QString line = stream.readLine();

    int size = line.length();

    int i = 0;
    QPainter painter(this);
    for (int j = 0; j < size; j++)
    {
        QChar c = line[j];
        QRect rect(x_offset + j*cellSize,
                   y_offset + i*cellSize,
                   cellSize,
                   cellSize);
        painter.fillRect(rect, cellToBrush(c));
    }

    for (i = 1; i < size; i++)
    {
        line = stream.readLine();
        for (int j = 0; j < size; j++)
        {
            QChar c = line[j];
            QRect rect(x_offset + j*cellSize,
                       y_offset + i*cellSize,
                       cellSize,
                       cellSize);
            painter.fillRect(rect, cellToBrush(c));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
