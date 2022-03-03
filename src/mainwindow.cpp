#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <chrono>
#include <thread>
#include <QApplication>
#include <string>

using namespace Eigen;

MainWindow::MainWindow(QWidget *parent, std::vector<Vector2d> points, Vector2d startingPos, Vector2d endingPos)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->points = points;

    this->startingPos = startingPos;
    this->endingPos = endingPos;
    initializeGrid(points);

//    printGrid();
//    std::cout << std::endl;

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeGrid(const std::vector<Vector2d>& points) {
    for (int i = 0; i < gridSize; ++i) {
        std::vector<int> row;
        std::vector<QFrame*> frameRow;
        for (int j = 0; j < gridSize; ++j) {
            std::string frameName = "frame_"+std::to_string(i)+std::to_string(j);
            QFrame* frame = new QFrame();
            frame->setParent(this->ui->centralwidget);
            frame->setObjectName(frameName.c_str());
            frame->setGeometry(j*blockSize,i*blockSize,blockSize,blockSize);
            frame->setStyleSheet("background-color:rgb(0,0,0)");

            row.push_back(0);
            frameRow.push_back(frame);
//            frameRow.push_back(this->ui->centralwidget->findChild<QFrame*>(frameName.c_str()));
        }
        grid.push_back(row);
        frameGrid.push_back(frameRow);
    }

    for (int i = 0, n = points.size(); i < n; ++i) {
        int x = points[i](0);
        int y = points[i](1);
        grid[x][y] = 1;
        frameGrid[x][y]->setStyleSheet("background-color:rgb(255,255,255)");
    }

    dronePos(0) = startingPos(0);
    dronePos(1) = startingPos(1);
    int drone_x = dronePos(0), drone_y = dronePos(1);
    assert(grid[drone_x][drone_y] != 1);

    grid[drone_x][drone_y] = 2;
    frameGrid[drone_x][drone_y]->setStyleSheet("background-color:rgb(0,255,0)");

    int end_x = endingPos(0), end_y = endingPos(1);
    grid[end_x][end_y] = 4;
    frameGrid[end_x][end_y]->setStyleSheet("background-color:rgb(255, 255, 0)");
}

void MainWindow::printGrid() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j)
            std::cout << grid[i][j] << " ";
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> MainWindow::getGrid() {
    return grid;
}

void MainWindow::setDronePos(const Vector2d& point) {
    int x = point(0), y = point(1);
    grid[x][y] = 2;
    frameGrid[x][y]->setStyleSheet("background-color:rgb(255,0,0)");

    int old_x = dronePos(0), old_y = dronePos(1);
    grid[old_x][old_y] = 3;
    if (old_x != startingPos(0) || old_y != startingPos(1))
        frameGrid[old_x][old_y]->setStyleSheet("background-color:rgb(0,0,255)");
    dronePos = point;
}

int MainWindow::pointToVertex(const Vector2d& point) {
    return point(0)*gridSize + point(1);
}

Vector2d MainWindow::vertexToPoint(int vertex) {
    int x = vertex / gridSize, y = vertex % gridSize;
    return Vector2d(x, y);
}

