#include "labyrinthrenderer.h"
#include "labyrinth.h"
#include "labyrinthgraph.h"
#include "pathsolver.h"
#include <algorithm>

void LabyrinthRenderer::paint(QPainter &painter, QRect availableRect,
                              const Labyrinth &lab, const LabyrinthGraph &graph, const PathSolver &solver,
                              bool showLab, bool showLabPaths, bool showGraph, bool showGraphPaths)
{
    if (lab.isEmpty()) return;

    availableRect.adjust(20, 20, -20, -20);
    if (!availableRect.isValid()) return;

    int matrixRows = lab.getRows();
    int matrixCols = lab.getCols();
    int graphMaxX = graph.getMaxX();
    int graphMaxY = graph.getMaxY();

    int gapUnits = 3;
    int totalLogicalWidth = matrixCols + gapUnits + graphMaxX;
    int totalLogicalHeight = std::max(matrixRows, graphMaxY);

    if (totalLogicalWidth <= 0 || totalLogicalHeight <= 0) return;

    double scaleX = (double)availableRect.width() / totalLogicalWidth;
    double scaleY = (double)availableRect.height() / totalLogicalHeight;
    int commonScale = (int)std::min(scaleX, scaleY);

    if (commonScale < 2) commonScale = 2;

    int cellSize = commonScale;
    int nodeSpacing = commonScale;
    int nodeRadius = std::max(2, commonScale / 5);
    int graphInternalGap = gapUnits * commonScale;
    int graphOffsetY = 0;

    int labWidth = matrixCols * cellSize;
    int labHeight = matrixRows * cellSize;
    int graphWidth = graphMaxX * nodeSpacing + nodeRadius * 2;
    int graphHeight = graphMaxY * nodeSpacing + nodeRadius * 2;

    int totalDrawingWidth = labWidth + graphInternalGap + graphWidth;
    int totalDrawingHeight = std::max(labHeight, graphOffsetY + graphHeight);

    int drawX = (availableRect.width() - totalDrawingWidth) / 2 + availableRect.left();
    int drawY = (availableRect.height() - totalDrawingHeight) / 2 + availableRect.top();

    painter.save();
    painter.translate(drawX, drawY);

    int graphPixelOffsetX = labWidth + graphInternalGap;

    if (showLab) {
        drawLabyrinth(painter, lab, cellSize);
    }
    if (showLabPaths) {
        drawLabyrinthPaths(painter, lab, solver, cellSize);
    }
    if (showGraph) {
        drawGraph(painter, graph, nodeSpacing, nodeRadius, graphPixelOffsetX, graphOffsetY);
    }
    if (showGraphPaths) {
        drawGraphPaths(painter, solver, nodeSpacing, graphPixelOffsetX, graphOffsetY);
    }

    painter.restore();
}

void LabyrinthRenderer::drawLabyrinth(QPainter &painter, const Labyrinth& lab, int cellSize)
{
    for (int r = 0; r < lab.getRows(); ++r) {
        for (int c = 0; c < lab.getCols(); ++c) {
            QRect cellRect(c * cellSize, r * cellSize, cellSize, cellSize);
            QColor cellColor;

            switch (lab.getValue(r, c)) {
            case 0: cellColor = Qt::black; break;
            case 1: cellColor = Qt::white; break;
            case 2: cellColor = Qt::red; break;
            case 3: cellColor = Qt::blue; break;
            default: cellColor = Qt::gray;
            }
            painter.fillRect(cellRect, cellColor);
            painter.setPen(Qt::darkGray);
            painter.drawRect(cellRect);
        }
    }
}

void LabyrinthRenderer::drawLabyrinthPaths(QPainter &painter, const Labyrinth& lab, const PathSolver& solver, int cellSize)
{
    QColor pathColor(0, 255, 0, 150);
    painter.setBrush(pathColor);
    painter.setPen(Qt::NoPen);

    for (const QVector<QPoint> &path : solver.getShortestPaths()) {
        for (const QPoint &pos : path) {
            if (lab.getValue(pos.y(), pos.x()) == 1) {
                QRect cellRect(pos.x() * cellSize, pos.y() * cellSize, cellSize, cellSize);
                painter.fillRect(cellRect, pathColor);
            }
        }
    }
}

void LabyrinthRenderer::drawGraph(QPainter &painter, const LabyrinthGraph& graph, int nodeSpacing, int nodeRadius, int offsetX, int offsetY)
{
    if (graph.isEmpty()) return;

    painter.setPen(Qt::gray);
    const auto& adjList = graph.getAdjacencyList();
    for (auto it = adjList.constBegin(); it != adjList.constEnd(); ++it) {
        QPoint p1 = it.key();
        QPoint screenP1(p1.x() * nodeSpacing + offsetX, p1.y() * nodeSpacing + offsetY);

        for (const QPoint &p2 : it.value()) {
            QPoint screenP2(p2.x() * nodeSpacing + offsetX, p2.y() * nodeSpacing + offsetY);
            painter.drawLine(screenP1, screenP2);
        }
    }

    painter.setBrush(Qt::blue);
    painter.setPen(Qt::NoPen);
    for (const QPoint &node : adjList.keys()) {
        QPoint screenPos(node.x() * nodeSpacing + offsetX, node.y() * nodeSpacing + offsetY);
        painter.drawEllipse(screenPos, nodeRadius, nodeRadius);
    }
}

void LabyrinthRenderer::drawGraphPaths(QPainter &painter, const PathSolver& solver, int nodeSpacing, int offsetX, int offsetY)
{
    painter.setPen(QPen(Qt::green, 3));

    for (const QVector<QPoint> &path : solver.getShortestPaths()) {
        for (int i = 0; i < path.size() - 1; ++i) {
            QPoint p1 = path[i];
            QPoint p2 = path[i + 1];

            QPoint screenP1(p1.x() * nodeSpacing + offsetX, p1.y() * nodeSpacing + offsetY);
            QPoint screenP2(p2.x() * nodeSpacing + offsetX, p2.y() * nodeSpacing + offsetY);

            painter.drawLine(screenP1, screenP2);
        }
    }
}
