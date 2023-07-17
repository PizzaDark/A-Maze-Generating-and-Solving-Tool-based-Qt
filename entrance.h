#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <QWidget>

namespace Ui {
class Entrance;
}

class Entrance : public QWidget
{
    Q_OBJECT

public:
    explicit Entrance(QWidget *parent = nullptr);
    ~Entrance();

private slots:

    void paintEvent(QPaintEvent *event);

    void on_actionOpen_clicked();

    void on_actionExit_clicked();

    void on_actionSearch_clicked();

    void on_default_maze_clicked();

    void on_actionGenerate_clicked();

private:
    Ui::Entrance *ui;
};

#endif // ENTRANCE_H
