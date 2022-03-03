#include "mythread.h"
#include <QDebug>
#include "mainwindow.h"
#include "graph.h"
#include <Eigen/Dense>
#include <chrono>
#include <iostream>

MyThread::MyThread(QString s, MainWindow* w, Vector2d startingPos, Vector2d endingPos) : name(s) {
    this->w = w;
    this->startingPos = startingPos;
    this->endingPos = endingPos;

}

void MyThread::run() {
//    for (int i = 0; i <= 100; ++i) {
//        qDebug() << this->name << " " << i;
//    }
    Graph g(w->getGrid());


//    std::chrono::steady_clock::time_point start_dijkstra = std::chrono::steady_clock::now();
//    std::vector<int> vertices_dijkstra = g.dijkstra(w->pointToVertex(startingPos), w->pointToVertex(endingPos));
//    std::chrono::steady_clock::time_point end_dijkstra = std::chrono::steady_clock::now();

//    std::cout << "Dijkstra time difference: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_dijkstra - start_dijkstra).count() << " milliseconds.\n";

    std::chrono::steady_clock::time_point start_astar = std::chrono::steady_clock::now();
    std::vector<int> vertices_astar = g.astar(w->pointToVertex(startingPos), w->pointToVertex(endingPos));
    std::chrono::steady_clock::time_point end_astar = std::chrono::steady_clock::now();
    std::cout << "A* time difference: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_astar - start_astar).count() << " milliseconds.\n";

//assert(vertices_astar == vertices_dijkstra);
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    for (int i = 0, n = vertices_astar.size(); i < n; ++i) {
        w->setDronePos(w->vertexToPoint(vertices_astar[i]));
//        printGrid();
//        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}
