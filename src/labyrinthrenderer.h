#ifndef LABYRINTHRENDERER_H
#define LABYRINTHRENDERER_H

#include <QPainter>
#include <QRect>

class Labyrinth;
class LabyrinthGraph;
class PathSolver;

class LabyrinthRenderer
{
public:
    static void paint(QPainter& painter, QRect availableRect,
                      const Labyrinth& lab,
                      const LabyrinthGraph& graph,
                      const PathSolver& solver,
                      bool showLab, bool showLabPaths,
                      bool showGraph, bool showGraphPaths);

private:
    static void drawLabyrinth(QPainter& painter, const Labyrinth& lab, int cellSize);
    static void drawLabyrinthPaths(QPainter& painter, const Labyrinth& lab, const PathSolver& solver, int cellSize);
    static void drawGraph(QPainter& painter, const LabyrinthGraph& graph, int nodeSpacing, int nodeRadius, int offsetX, int offsetY);
    static void drawGraphPaths(QPainter& painter, const PathSolver& solver, int nodeSpacing, int offsetX, int offsetY);
};

#endif // LABYRINTHRENDERER_H
