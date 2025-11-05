#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <QVector>
#include <QPoint>
#include <QString>

class Labyrinth
{
public:
    Labyrinth();

    bool loadFromFile(const QString& filePath);

    const QVector<QVector<int>>& getMatrix() const { return m_matrix; }
    QPoint getStartNode() const { return m_startNode; }
    const QVector<QPoint>& getExitNodes() const { return m_exitNodes; }
    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }
    int getValue(int r, int c) const;

    bool isEmpty() const { return m_rows == 0; }

private:
    QVector<QVector<int>> m_matrix;
    QPoint m_startNode;
    QVector<QPoint> m_exitNodes;
    int m_rows;
    int m_cols;
};

#endif // LABYRINTH_H
