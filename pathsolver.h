#ifndef PATHSOLVER_H
#define PATHSOLVER_H

#include <QVector>
#include <QHash>
#include <QPoint>

class LabyrinthGraph;

class PathSolver
{
public:
    PathSolver();

    void runBFS(const LabyrinthGraph& graph, QPoint startNode);
    void findPaths(QPoint startNode, const QVector<QPoint>& exitNodes);

    const QVector<QVector<QPoint>>& getShortestPaths() const { return m_shortestPaths; }

private:
    QHash<QPoint, QPoint> m_predecessors;
    QVector<QVector<QPoint>> m_shortestPaths;
};

#endif // PATHSOLVER_H
