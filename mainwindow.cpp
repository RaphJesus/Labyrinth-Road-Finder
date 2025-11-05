#include "mainwindow.h"
#include "labyrinthrenderer.h"
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QWidget>
#include <QSizePolicy>
#include <QFileDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_showLabyrinth(true),
    m_showLabyrinthPaths(true),
    m_showGraph(true),
    m_showGraphPaths(true),
    m_toolBar(nullptr)
{
    setupUI();
    resize(1200, 800);
    setWindowTitle("Labyrinth Solver");

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(50, 50, 50));
    setAutoFillBackground(true);
    setPalette(pal);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QMenuBar *mainMenuBar = new QMenuBar(this);
    setMenuBar(mainMenuBar);

    QMenu *fileMenu = mainMenuBar->addMenu("File");
    QAction *openAction = fileMenu->addAction("Open...");

    connect(openAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);

    m_toolBar = new QToolBar(this);
    m_toolBar->setMovable(false);
    m_toolBar->setFloatable(false);
    m_toolBar->setStyleSheet("QToolBar { border: none; background-color: #323232; padding: 5px; }");
    addToolBar(m_toolBar);

    QAction *actToggleLab = new QAction("Labirint", this);
    actToggleLab->setCheckable(true);
    actToggleLab->setChecked(true);
    connect(actToggleLab, &QAction::triggered, this, &MainWindow::on_toggleLabyrinth_clicked);

    QAction *actToggleLabPaths = new QAction("Cai Labirint", this);
    actToggleLabPaths->setCheckable(true);
    actToggleLabPaths->setChecked(true);
    connect(actToggleLabPaths, &QAction::triggered, this, &MainWindow::on_toggleLabyrinthPaths_clicked);

    QAction *actToggleGraph = new QAction("Graf", this);
    actToggleGraph->setCheckable(true);
    actToggleGraph->setChecked(true);
    connect(actToggleGraph, &QAction::triggered, this, &MainWindow::on_toggleGraph_clicked);

    QAction *actToggleGraphPaths = new QAction("Cai Graf", this);
    actToggleGraphPaths->setCheckable(true);
    actToggleGraphPaths->setChecked(true);
    connect(actToggleGraphPaths, &QAction::triggered, this, &MainWindow::on_toggleGraphPaths_clicked);

    QWidget* spacerLeft = new QWidget();
    spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QWidget* spacerRight = new QWidget();
    spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_toolBar->addWidget(spacerLeft);
    m_toolBar->addAction(actToggleLab);
    m_toolBar->addAction(actToggleLabPaths);
    m_toolBar->addAction(actToggleGraph);
    m_toolBar->addAction(actToggleGraphPaths);
    m_toolBar->addWidget(spacerRight);
}

void MainWindow::on_toggleLabyrinth_clicked(bool checked)
{
    m_showLabyrinth = checked;
    update();
}

void MainWindow::on_toggleLabyrinthPaths_clicked(bool checked)
{
    m_showLabyrinthPaths = checked;
    update();
}

void MainWindow::on_toggleGraph_clicked(bool checked)
{
    m_showGraph = checked;
    update();
}

void MainWindow::on_toggleGraphPaths_clicked(bool checked)
{
    m_showGraphPaths = checked;
    update();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Deschide Labirint", "", "Text Files (*.txt);;All Files (*)");
    if (filePath.isEmpty()) {
        return;
    }

    if (!m_labyrinth.loadFromFile(filePath)) {
        qWarning() << "Eroare la încărcarea labirintului.";
        m_labyrinth = Labyrinth();
    }

    m_graph.build(m_labyrinth);

    m_solver.runBFS(m_graph, m_labyrinth.getStartNode());

    m_solver.findPaths(m_labyrinth.getStartNode(), m_labyrinth.getExitNodes());

    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_labyrinth.isEmpty() || !m_toolBar || !menuBar()) return;

    int topMargin = menuBar()->height() + m_toolBar->height();
    QRect availableRect(0, topMargin, width(), height() - topMargin);

    LabyrinthRenderer::paint(painter, availableRect,
                             m_labyrinth, m_graph, m_solver,
                             m_showLabyrinth, m_showLabyrinthPaths,
                             m_showGraph, m_showGraphPaths);
}
