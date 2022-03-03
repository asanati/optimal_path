#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <Eigen/Dense>
#include <QFrame>

using namespace Eigen;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, std::vector<Vector2d> points = {}, Vector2d startingPos = Vector2d(0,0), Vector2d endingPos = Vector2d(10,10));
    ~MainWindow();
    void initializeGrid(const std::vector<Vector2d>& points);
    void printGrid();
    std::vector<std::vector<int>> getGrid();
    void setDronePos(const Vector2d& point);
    int pointToVertex(const Vector2d& point);
    Vector2d vertexToPoint(int vertex);

private:
    Ui::MainWindow *ui;
    const int gridSize = 27, blockSize = 30;
    std::vector<Vector2d> points;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<QFrame*>> frameGrid;
    Vector2d dronePos, startingPos, endingPos;

};
#endif // MAINWINDOW_H
