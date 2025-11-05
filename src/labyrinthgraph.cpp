#include "labyrinthgraph.h"
#include "labyrinth.h"
#include <algorithm>

LabyrinthGraph::LabyrinthGraph() : m_maxX(0), m_maxY(0)
{
}

void LabyrinthGraph::build(const Labyrinth &lab)
{
    m_adjacencyList.clear();
    m_maxX = 0;
    m_maxY = 0;

    if (lab.isEmpty()) return;

    int rows = lab.getRows();
    int cols = lab.getCols();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {

            if (lab.getValue(r, c) == 0) {
                continue;
            }

            QPoint currentNode(c, r);
            QVector<QPoint> neighbors;

            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (lab.getValue(nr, nc) != 0) {
                    neighbors.append(QPoint(nc, nr));
                }
            }

            if (!neighbors.isEmpty()) {
                m_adjacencyList[currentNode] = neighbors;
                m_maxX = std::max(m_maxX, c);
                m_maxY = std::max(m_maxY, r);
            }
        }
    }
}

const QVector<QPoint>& LabyrinthGraph::getNeighbors(const QPoint& node) const
{
    auto it = m_adjacencyList.find(node);
    if (it != m_adjacencyList.end()) {
        return it.value();
    }
    return m_emptyNeighbors;
}
