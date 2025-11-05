#include "labyrinth.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Labyrinth::Labyrinth() : m_rows(0), m_cols(0), m_startNode(-1, -1)
{
}

bool Labyrinth::loadFromFile(const QString &filePath)
{
    m_matrix.clear();
    m_exitNodes.clear();
    m_startNode = QPoint(-1, -1);
    m_rows = 0;
    m_cols = 0;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nu am putut deschide fisierul:" << filePath;
        return false;
    }

    QTextStream in(&file);
    int currentRow = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        if (m_cols == 0) {
            m_cols = line.length();
        }

        QVector<int> rowVector;
        for (int currentCol = 0; currentCol < line.length(); ++currentCol) {
            int value = QString(line[currentCol]).toInt();
            rowVector.append(value);

            if (value == 3) {
                m_startNode = QPoint(currentCol, currentRow);
            } else if (value == 2) {
                m_exitNodes.append(QPoint(currentCol, currentRow));
            }
        }
        m_matrix.append(rowVector);
        currentRow++;
    }
    m_rows = currentRow;
    file.close();

    return !m_matrix.isEmpty();
}

int Labyrinth::getValue(int r, int c) const
{
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) {
        return 0;
    }
    return m_matrix[r][c];
}
