#include "entrance.h"
#include "ui_entrance.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <ctime>
//#include <stack>
#include <queue>
#include <vector>
using namespace std;

const int MAX_N = 100;

int n, m;
char c;
char maze[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

struct Point {
    int x, y;
    Point(){}
    Point(int x, int y) : x(x), y(y) {}
};

std::vector<Point> search_path;

// 判断点是否合法
bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != '1' && !visited[x][y];
} // 坐标需在合法范围内且未访问过

// 广度优先搜索
bool bfs(Point start, Point end, std::vector<Point>& path) {
    std::queue<Point> q;
    q.push(start);
    visited[start.x][start.y] = true;

    // 用一个二维数组记录每个点的父节点
    Point parent[MAX_N][MAX_N];
    memset(parent, -1, sizeof(parent));

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (cur.x == end.x && cur.y == end.y) {
            // 输出路径
            path.push_back(cur);

            // 从终点开始往回走，保存路径上的所有点
            while (parent[cur.x][cur.y].x != -1 && parent[cur.x][cur.y].y != -1) {
                cur = parent[cur.x][cur.y];
                path.push_back(cur);
            }

            // 将路径翻转，使其从起点到终点
            reverse(path.begin(), path.end());

            return true;
        }

        // 四个方向搜索
        const int dx[4] = {0, 1, -1, 0};
        const int dy[4] = {1, 0, 0, -1};
        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (is_valid(nx, ny)) {
                q.push(Point(nx, ny));
                visited[nx][ny] = true;
                parent[nx][ny] = cur; // 记录父节点
            }
        }
    }

    return false; // true为找到路径
}

// 深度优先搜索
//bool dfs(Point start, Point end, std::vector<Point>& path) {
//    std::stack<Point> s;
//    s.push(start);
//    visited[start.x][start.y] = true;

//    while (!s.empty()) {
//        Point cur = s.top();
//        s.pop();

//        if (cur.x == end.x && cur.y == end.y) {
//            // 输出路径
//            path.push_back(cur);
//            return true;
//        }

//        // 四个方向搜索
//        const int dx[4] = {0, 1, -1, 0};
//        const int dy[4] = {1, 0, 0, -1};
//        for (int i = 0; i < 4; ++i) {
//            int nx = cur.x + dx[i];
//            int ny = cur.y + dy[i];
//            if (is_valid(nx, ny)) {
//                s.push(Point(nx, ny));
//                visited[nx][ny] = true;
//                if (dfs(Point(nx, ny), end, path)) {
//                    path.push_back(Point(nx, ny));
//                    return true;
//                }
//            }
//        }
//    }

//    return false;
//}

Entrance::Entrance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Entrance)
{
    ui->setupUi(this);
}

Entrance::~Entrance()
{
    delete ui;
}

void Entrance::on_actionOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("打开失败"));
        return;
    }

    search_path.clear();

    QTextStream in(&file);
    in >> n >> m;
    in >> c;

    // 读入迷宫
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            in >> c;
            if (c == '0' || c == '1' || c == 'S' || c =='T')
                maze[i][j] = c;
        }
        in >> c;
    }

    file.close();
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j) {
//            printf("%c",maze[i][j]);
//        }
//        printf("\n");
//    }
    // 重绘窗口
    update();
}


void Entrance::on_actionSearch_clicked()
{
    // 清空搜索结果
    search_path.clear();
    memset(visited, false, sizeof(visited));

    // 寻找起点和终点
    Point start(0, 0), end(1, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (maze[i][j] == 'S') {
                start.x = i;
                start.y = j;
            }
            if (maze[i][j] == 'T') {
                end.x = i;
                end.y = j;
            }
        }
    }

    // 搜索
    std::vector<Point> path;

    if (bfs(start, end, path)) {
        search_path = path;
//        search_path.push_back(start);

//        for(Point p:search_path)
//            printf("(%d,%d)",p.x,p.y);
        QMessageBox m;
        m.setText("路径已找到");
        m.exec();

    } else {
        QMessageBox m;
        m.setText("未找到路径");
        m.exec();
    }

    // 重绘窗口
    update();
}

void Entrance::on_default_maze_clicked()
{
//    QString str = qApp->applicationDirPath() + "/maze.txt";
    QString str = ":/preset/maze.txt";
    QFile file(str);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(NULL, "warning", QString("无法打开该文件：%1 (原因：%2)").arg(str).arg(file.errorString()));
        return;
    }

    search_path.clear();

    QTextStream in(&file);
    in >> n >> m;
    in >> c;

    // 读入迷宫
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            in >> c;
            if (c == '0' || c == '1' || c == 'S' || c =='T')
                maze[i][j] = c;
        }
        in >> c;
    }

    file.close();

    // 重绘窗口
    update();
}

int getRand(int a,int b){
    return rand()%(b-a+1)+a;
}

void Entrance::on_actionGenerate_clicked()
{
    search_path.clear();
    srand(time(0));
    n = getRand(2, 20);
    m = getRand(2, 20);

    int x1 = getRand(0, n-1),y1 = getRand(0, m-1);
    int x2 = getRand(0, n-1),y2 = getRand(0, m-1);
    while (x1 == x2 || y1 == y2) {
        x2 = getRand(0,n-1);
        y2 = getRand(0,m-1);
    }
    for (int i = 0; i < n;i++)
        for (int j = 0; j < m;j++)
            maze[i][j] = (char)(getRand(0, 1) + '0');
    maze[x1][y1] = 'S';
    maze[x2][y2] = 'T';

    update();
}

void Entrance::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制迷宫
    const int cell_size = qMin(width(), height())/(qMax(n, m) + 1);
    const int margin = cell_size/2;
    painter.translate(margin, margin);

    QPen pen(QColor(0, 0, 0), 2);
    painter.setPen(pen);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            QPoint top_left(j * cell_size, i * cell_size);
            QRect cell(top_left, QSize(cell_size, cell_size));

            if (maze[i][j] == '1') {
                painter.fillRect(cell, QColor(0, 0, 0));
            } else if (maze[i][j] == 'S') {
                painter.fillRect(cell, QColor(0, 255, 0));
            } else if (maze[i][j] == 'T') {
                painter.fillRect(cell, QColor(255, 0, 0));
            } else if (maze[i][j] == '0'){
                painter.fillRect(cell, QColor(255, 255, 255));
            }

            painter.drawRect(cell);
        }
    }

    // 搜索路径
    if (!search_path.empty()) {
        painter.save();
        painter.setPen(QPen(QColor(0, 0, 255), cell_size/3));
        QPoint last_point(search_path[0].y * cell_size + cell_size / 2, search_path[0].x * cell_size + cell_size / 2);
        for (int i = 1; i < search_path.size(); ++i) {
            QPoint cur_point(search_path[i].y * cell_size + cell_size / 2, search_path[i].x * cell_size + cell_size / 2);
            painter.drawLine(last_point, cur_point);
            last_point = cur_point;
        }
        painter.restore();
    }
}

void Entrance::on_actionExit_clicked()
{
    exit(0);
}
