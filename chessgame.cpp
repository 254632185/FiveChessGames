#include "chessgame.h"
#include "mainwindow.h"
#include<QPushButton>

#include <QPixmap>
#include <QPalette>
#include <QPainter>
#include <QMouseEvent>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

ChessGame::ChessGame(QWidget *parent)
    : QMainWindow(parent),isAllMusicPlaying(true), hasWinner(false)
{

    // 设置游戏窗口标题名称
    setWindowTitle("五子棋游戏");

    // 设置游戏窗口的尺寸
    setMinimumSize(1000, 800);
    setMaximumSize(1000, 800);

    // 设置游戏背景图片
    QPixmap background(":/new/prefix1/images/8d732e1e83e0d423821f95019b109392.jpg"); // 创建一个QPixmap对象并加载图片
    if (background.isNull()) {
        qWarning() << "Failed to load background image";
        return;
        }

    // 缩放图片以适应窗口大小，并保持纵横比
    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette; // 创建palette对象，并且将背景图片设置为窗口背景
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);


    // 展示游戏UI信息
    QPushButton *button_mode = new QPushButton(this);
    button_mode->setStyleSheet("font:Bold;font-size:36px;color:white;background-color: rgb(30, 144, 255);border:2px ;border-radius:10px;padding:2px 4px;");
    button_mode->setGeometry(QRect(785, 100, 200, 50));
    button_mode->setText("PVP");

    QLabel *label_name = new QLabel(this);
    label_name->setStyleSheet("color:white;font-size:32px;");
    label_name->setText("经典智益游戏");
    label_name->setGeometry(785, 700, 200, 50);

    // 玩家先手按钮实现
    game_type = 1;
    SelectModeGroup = new QButtonGroup(this);

    QRadioButton *Play1 = new QRadioButton("黑棋先手", this);
    SelectModeGroup->addButton(Play1, 1);
    Play1->setStyleSheet("font: Bold; font-size:36px; color:white;");
    Play1->setGeometry(825, 200, 100, 30);
    connect(Play1, SIGNAL(clicked()), this, SLOT(SelectRadio()));

    QRadioButton *Play2 = new QRadioButton("白棋先手", this);
    SelectModeGroup->addButton(Play2, 2);
    Play2->setStyleSheet("font: Bold; font-size:36px; color:white;");
    Play2->setGeometry(825, 270, 100, 30);
    connect(Play2, SIGNAL(clicked()), this, SLOT(SelectRadio()));

    Play1->setChecked(true);

    // 实现游戏开始/游戏结束按钮
    flag = 0;
    button = new QPushButton(this);
    button->setStyleSheet("font:Bold;font-size:36px;color:white;background-color: rgb(30, 144, 255);border:2px ;border-radius:10px;padding:2px 4px;");
    button->setGeometry(QRect(785, 390, 200, 50));
    button->setText("游戏开始");
    connect(button, SIGNAL(clicked()), this, SLOT(GameOper()));

    // 初始化：处理开启鼠标监听操作
    setMouseTracking(true);
    lock = true;
    memset(chessboard, 0, sizeof(chessboard));


    // 创建并初始化媒体播放器实例
    mediaPlayer = new QMediaPlayer(this);
    winSound = new QMediaPlayer(this);
    blackMoveSound = new QMediaPlayer(this);
    whiteMoveSound = new QMediaPlayer(this);

    // 加载音频文件
    mediaPlayer->setMedia(QUrl("qrc:/new/prefix1/images/yuzgouchangwan.mp3"));
    winSound->setMedia(QUrl("qrc:/new/prefix1/images/sound.mp3"));
    blackMoveSound->setMedia(QUrl("qrc:/new/prefix1/images/black_move.mp3"));
    whiteMoveSound->setMedia(QUrl("qrc:/new/prefix1/images/white_move.mp3"));

    // 自动播放背景音乐
    if (isAllMusicPlaying) {
        mediaPlayer->play();
        if (mediaPlayer->state() != QMediaPlayer::PlayingState) {
            qDebug() << "Background music not playing, state:" << mediaPlayer->state();
        }
    }

    // 创建音乐开关按钮
    musicButton = new QPushButton(this);
    musicButton->setStyleSheet("font:Bold;font-size:36px;color:white;background-color: rgb(30, 144, 255);border:2px ;border-radius:10px;padding:2px 4px;");
    musicButton->setGeometry(QRect(785, 500, 200, 50));
    musicButton->setText("关闭音乐");
    // 连接音乐开关按钮点击事件到槽函数
    connect(musicButton, &QPushButton::clicked, this, &ChessGame::toggleAllMusic);
}

ChessGame::~ChessGame()
{
    delete ui;
}

// 成员函数
// 更新棋盘上的棋子位置
void ChessGame::update_chessboard(int x, int y)
{
    if (!chessboard[x][y]) {
        chessboard[x][y] = player;  // 切换棋子颜色操作
        currentX = x;
        currentY = y;
        update();

        // 检查是否有玩家获胜
        Is_Someone_Winner(x, y);

        if (!hasWinner && isAllMusicPlaying) {
            if (player == 1) { // 黑棋
                blackMoveSound->play();
            } else { // 白棋
                whiteMoveSound->play();
            }
        }

        player = (player % 2) + 1; // 切换玩家
    }
}

// 检测是否有玩家获胜
void ChessGame::Is_Someone_Winner(int x, int y)
{
    QPoint ps(x, y);
    if (isWinner(ps)) {
        lock = true;
        hasWinner = true; // 设置胜利标志

        if (game_type == 1) {
            if (chessboard[x][y] == 1)
                strWinner = "BLACK";
            else
                strWinner = "WHITE";
        }

        // 播放胜利音效
        if (isAllMusicPlaying) {
            winSound->play();
        }

        QMessageBox::information(NULL, "退出", strWinner + "战胜，请继续努力！", QMessageBox::Ok);
    }
}

// 获取指定位置的棋子类型 dir方向 offset位移
int ChessGame::getPointAt(QPoint p, int dir, int offset)
{
    int x = p.x(), y = p.y();

    x = x + offset * m_dir[dir].x();
    y = y + offset * m_dir[dir].y();

    // 边界检查
    if (x >= 15 || x < 0 || y >= 15 || y < 0) {
        return -100;
    }

    // 如果坐标有效，该函数返回位置的棋子类型
    return chessboard[x][y];
}


// 判断指定位置是否形成五子连珠
int ChessGame::isWinner(QPoint p)
{
    int dir_cnt[8] = {0};

    memset(dir_cnt, 0, sizeof(dir_cnt));

    for (int i = 0; i < 8; i++) {
        for (int j = 1;; j++) {
            if (getPointAt(p, i, j) != chessboard[p.x()][p.y()])
                break;
            dir_cnt[i]++;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (dir_cnt[i] + dir_cnt[i + 4] + 1 >= 5) {
            return 1;
        }
    }
    // 如果在任何一个方向检测到五子连珠，返回1表示玩家获胜

    return 0;
}

// 人物下棋 重载鼠标按压，获取位置，处理玩家的下棋操作
void ChessGame::PERSON_time(QMouseEvent *e)
{
    // 通过计算操作，将鼠标的屏幕坐标转换成棋盘上面的行列索引
    // 这样做可以在棋盘逻辑坐标系当中确定玩家点击的位置
    int x, y;
    if ((e->x() >= 25 && e->x() <= 755) && (e->y() >= 25 && e->y() <= 755)) {
        x = (e->x() + 25) / 50 - 1;
        y = (e->y() + 25) / 50 - 1;
        update_chessboard(x, y);
    }
}

// 绘制棋盘和棋子（绘图事件 重写绘图事件）
void ChessGame::paintEvent(QPaintEvent *e)
{
    QPainter pt(this);
    // 调用此接口来设置绘制图时的渲染操作
    pt.setRenderHint(QPainter::Antialiasing, true);

    // 绘制棋盘
    QBrush brush;
    brush.setColor(QColor(123, 176, 141));
    brush.setStyle(Qt::SolidPattern);
    pt.setBrush(brush);

    // 处理边框
    QPen pen = pt.pen();
    pt.setPen(pen);
    pt.drawRect(30, 30, 740, 740);

    for (int i = 0; i < 15; i++) {
        pt.drawLine(50, 50 + i * 50, 750, 50 + i * 50); // 横线
        pt.drawLine(50 + i * 50, 50, 50 + i * 50, 750); // 竖线
    }

    // 绘制5个正方形黑色点
    brush.setColor(Qt::black);
    pt.setBrush(brush);
    pt.drawRect(195, 195, 10, 10); // 上左
    pt.drawRect(595, 195, 10, 10); // 上右
    pt.drawRect(195, 595, 10, 10); // 下左
    pt.drawRect(595, 595, 10, 10); // 下右
    pt.drawRect(395, 395, 10, 10); // 中间

    // 绘制棋子
    brush.setStyle(Qt::SolidPattern);
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chessboard[i][j] == 1) {
                // 黑棋
                brush.setColor(Qt::black);
                pt.setBrush(brush);
                pt.drawEllipse(QPoint(i * 50 + 50, j * 50 + 50), 20, 20);
            } else if (chessboard[i][j] == 2) {
                // 白棋
                brush.setColor(Qt::white);
                pt.setPen(Qt::NoPen);
                pt.setBrush(brush);
                pt.drawEllipse(QPoint(i * 50 + 50, j * 50 + 50), 20, 20);
            }
        }
    }

    if (!flag)
        return;

    // 绘制最近一个落子的标识
    pen.setColor(Qt::red);
    pen.setWidth(1);
    pt.setPen(pen);
    pt.setBrush(Qt::NoBrush); // 移除画刷
    pt.drawRect(currentX * 50 + 50 - 23, currentY * 50 + 50 - 23, 46, 46);

    // 锁住棋盘（禁止下棋），产生胜负/游戏结束
    if (lock)
        return;

    // 绘制鼠标跟踪预览标识
     if((moveX>=0 && moveX<=14) && (moveY>=0 && moveY<=14) && chessboard[moveX][moveY]==0){
        if (player == 1) {
            // 黑色预览标识
            brush.setColor(QColor(0, 0, 0, 150));
        } else {
            // 白色预览标识
            brush.setColor(QColor(255, 255, 255, 150));
        }
        pt.setPen(Qt::NoPen);
        pt.setBrush(brush);
        pt.drawEllipse(QPoint(moveX * 50 + 50, moveY * 50 + 50), 20, 20);
    }
}

// 更新moveX moveY（处理鼠标移动事件）
void ChessGame::mouseMoveEvent(QMouseEvent *e) // OK
{
    moveX=(e->x()+25)/50-1;
    moveY=(e->y()+25)/50-1;
    update();
}

// 玩家下棋（处理鼠标按压事件）
void ChessGame::mousePressEvent(QMouseEvent *e)
{
    if (lock)
        return;

    // 根据游戏类型和当前玩家判断是否允许下棋
    if (game_type == 1) {
        PERSON_time(e);
    }
}

void ChessGame::GameOper()
{
    if (flag == 0) {
        SelectPlayer();
        lock = false;
        currentX = -100;
        currentY = -100;
        moveX = -100;
        moveY = -100;

        memset(chessboard, 0, sizeof(chessboard));

        button->setText("游戏结束");
        button->setStyleSheet("font:Bold;font-size:36px;color:white;background-color: rgb(255, 0, 0);border:2px ;border-radius:10px;padding:2px 4px;");

    } else {
        button->setText("游戏开始");
        button->setStyleSheet("font:Bold;font-size:36px;color:white;background-color: rgb(30, 144, 255);border:2px ;border-radius:10px;padding:2px 4px;");
        lock = true;
        memset(chessboard, 0, sizeof(chessboard));
        update();

        // 停止背景音乐
        mediaPlayer->stop();
    }

    flag = !flag;
}

void ChessGame::SelectPlayer()
{
    switch (SelectModeGroup->checkedId()) // OK
    {
    case 1: // 黑棋先手
        game_type = 1;
        player = 1;
        break;

    case 2: // 白棋先手
        game_type = 1;
        player = 2;
        break;
    }
}

void ChessGame::SelectRadio()
{
    SelectPlayer();
}

void ChessGame::toggleAllMusic()
{
    qDebug() << "Toggling all music, current state:" << isAllMusicPlaying;

    if (isAllMusicPlaying) {
        mediaPlayer->pause();
        winSound->pause();
        blackMoveSound->pause();
        whiteMoveSound->pause();
        isAllMusicPlaying = false;
        musicButton->setText("开启音乐");
    } else {
        mediaPlayer->play();
        isAllMusicPlaying = true;
        musicButton->setText("关闭音乐");
    }

    qDebug() << "After toggle, media player state:" << mediaPlayer->state();
}
