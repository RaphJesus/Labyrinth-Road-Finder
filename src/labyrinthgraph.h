#ifndef LABYRINTHGRAPH_H
#define LABYRINTHGRAPH_H

#include <QHash>
#include <QVector>
#include <QPoint>

class Labyrinth;

class LabyrinthGraph
{
public:
    LabyrinthGraph();

    void build(const Labyrinth& lab);

    const QHash<QPoint, QVector<QPoint>>& getAdjacencyList() const { return m_adjacencyList; }
    const QVector<QPoint>& getNeighbors(const QPoint& node) const;
    int getMaxX() const { return m_maxX; }
    int getMaxY() const { return m_maxY; }
    bool isEmpty() const { return m_adjacencyList.isEmpty(); }

private:
    QHash<QPoint, QVector<QPoint>> m_adjacencyList;
    QVector<QPoint> m_emptyNeighbors;
    int m_maxX;
    int m_maxY;
};

#endif // LABYRINTHGRAPH_H
