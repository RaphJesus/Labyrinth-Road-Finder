#include "pathsolver.h"
#include "labyrinthgraph.h"
#include <QQueue>
#include <QSet>

PathSolver::PathSolver()
{
}

void PathSolver::runBFS(const LabyrinthGraph &graph, QPoint startNode)
{
    m_predecessors.clear();
    if (startNode == QPoint(-1, -1) || graph.isEmpty()) {
        return;
    }

    QQueue<QPoint> queue;
    QSet<QPoint> visited;

    queue.enqueue(startNode);
    visited.insert(startNode);
    m_predecessors[startNode] = QPoint(-1, -1);

    while (!queue.isEmpty()) {
        QPoint current = queue.dequeue();

        for (const QPoint &neighbor : graph.getNeighbors(current)) {
            if (!visited.contains(neighbor)) {
                visited.insert(neighbor);
                m_predecessors[neighbor] = current;
                queue.enqueue(neighbor);
            }
        }
    }
}

void PathSolver::findPaths(QPoint startNode, const QVector<QPoint> &exitNodes)
{
    m_shortestPaths.clear();

    for (const QPoint &exitNode : exitNodes) {
        if (m_predecessors.contains(exitNode)) {
            QVector<QPoint> path;
            QPoint current = exitNode;

            while (current != QPoint(-1, -1)) {
                path.prepend(current);
                current = m_predecessors[current];
            }

            if (!path.isEmpty() && path.first() == startNode) {
                m_shortestPaths.append(path);
            }
        }
    }
}
