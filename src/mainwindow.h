#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>

#include "labyrinth.h"
#include "labyrinthgraph.h"
#include "pathsolver.h"

class QMenuBar;
class QMenu;
class QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_actionOpen_triggered();
    void on_toggleLabyrinth_clicked(bool checked);
    void on_toggleLabyrinthPaths_clicked(bool checked);
    void on_toggleGraph_clicked(bool checked);
    void on_toggleGraphPaths_clicked(bool checked);

private:
    void setupUI();

    Labyrinth m_labyrinth;
    LabyrinthGraph m_graph;
    PathSolver m_solver;

    bool m_showLabyrinth;
    bool m_showLabyrinthPaths;
    bool m_showGraph;
    bool m_showGraphPaths;

    QToolBar *m_toolBar;

};
#endif // MAINWINDOW_H
