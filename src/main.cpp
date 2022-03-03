#include "mainwindow.h"

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <chrono>
#include <thread>
#include <QApplication>
#include <QPushButton>
#include <QThread>

#include "graph.h"
#include "mythread.h"

using namespace Eigen;

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    std::vector<std::vector<int>> coords = {{1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8}, {1,9}, {1,10},
                                            {2,1}, {3,1}, {4,1}, {5,1}, {5, 0}};
    std::vector<Vector2d> points;
    for (int i = 0, n = coords.size(); i < n; ++i)
        points.push_back(Vector2d(coords[i][0], coords[i][1]));
    
    Vector2d startingPos(0,0), endingPos(7,7);

    MainWindow w(nullptr, points, startingPos, endingPos);
    w.show();

    MyThread thread1("A", &w, startingPos, endingPos);

    thread1.start();

    return a.exec();
}
