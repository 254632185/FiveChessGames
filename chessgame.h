

#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QMainWindow>

#include <QTimer>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QMessageBox>
#include <QRadioButton>
#include <QPushButton>
#include <QPalette>
#include <QLabel>
#include <QButtonGroup>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <bits/stdc++.h>  // stack
using namespace std;

#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>


QT_BEGIN_NAMESPACE
namespace Ui { class ChessGame; }
QT_END_NAMESPACE

class ChessGame : public QMainWindow
{
    Q_OBJECT

public:
    ChessGame(QWidget *parent = nullptr);
    ~ChessGame();

signals:
    void back();


private slots:
    void GameOper();
    void SelectPlayer();
    void SelectRadio();
    void toggleAllMusic();

private:
    // 定义二维数组，用来存储棋盘的状态
    int chessboard[15][15];

    // 定义玩家 假设值为1第一个玩家（黑棋），2第二个玩家（白棋）。通过这个变量来记录当前玩家的编号
    int player;

    // 处理鼠标移动位置，记录鼠标移动时的位置
    int moveX, moveY;

    // 处理上次落子的位置
    int currentX, currentY;

    // 定义一个布尔值类型，专门用于锁定棋盘（防止下棋）
    bool lock;

    // 定义一个游戏状态：0游戏开始 1游戏结束
    int flag;

    // 定义游戏类型：PVP
    int game_type;

    // 定义游戏开始和结束按钮
    QPushButton *button;

    // 定义一个指针来管理游戏类型的单选按钮
    QButtonGroup *SelectModeGroup;

    // 定义一个字符串，专门用来记录游戏胜利者
    QString strWinner;

    // 定义一个数组，处理8个方向
    QPoint m_dir[8] = {QPoint(0, -1), QPoint(1, -1), QPoint(1, 0), QPoint(1, 1),
                       QPoint(0, 1), QPoint(-1, 1), QPoint(-1, 0), QPoint(-1, -1)};

    // 成员函数
    // 更新棋盘上的棋子位置
    void update_chessboard(int x, int y);

    // 获取指定位置的棋子类型 dir方向 offset位移
    int getPointAt(QPoint p, int dir, int offset);

    // 检测是否有玩家获胜 人物/AI
    void Is_Someone_Winner(int x, int y);

    // 判断指定位置是否形成五子连珠
    int isWinner(QPoint p);

    // 人物下棋 重载鼠标按压，获取位置，处理玩家的下棋操作
    void PERSON_time(QMouseEvent *e);

    // 绘制棋盘和棋子（绘图事件 重写绘图事件）
    void paintEvent(QPaintEvent *e);

    // 更新moveX moveY（处理鼠标移动事件）
    void mouseMoveEvent(QMouseEvent *e);

    // 玩家下棋（处理鼠标按压事件）
    void mousePressEvent(QMouseEvent *e);

    // 音频播放器
    QMediaPlayer *mediaPlayer;
    QMediaPlayer *winSound;
    QMediaPlayer *blackMoveSound;
    QMediaPlayer *whiteMoveSound;

    bool isAllMusicPlaying; // 追踪所有音乐的播放状态
    QPushButton *musicButton; // 音乐开关按钮

    bool hasWinner;

private:
    Ui::ChessGame *ui;
};

#endif // CHESSGAME_H
