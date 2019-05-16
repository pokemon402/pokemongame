#include "enemy.h"
#include "waypoint.h"
#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include <QTime>
#include <QTimer>

static const int Health_Bar_Width = 20;

Enemy::Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite /*= QPixmap(":/image/enemy1_1.png")*/,
const QPixmap &sprite1/*=QPixmap(":/image/enemy1_2.png")*/,const QPixmap &sprite2,
             const QPixmap &sprite3,const QPixmap &sprite4)
        : QObject(0)
        , m_active(false)
    , m_maxHp(40)  //40点血
        , m_currentHp(40)
        , m_walkingSpeed(1.0)
        , m_pos(startWayPoint->pos())
        , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_sprite(sprite)
    , m_sprite1(sprite1)
    , m_sprite2(sprite2)
    , m_sprite3(sprite3)
    , m_sprite4(sprite4)
{
}

Enemy::~Enemy()
{
        m_destinationWayPoint = NULL;
}

void Enemy::doActivate()
{
        m_active = true;
}

void Enemy::move()
{
        if (!m_active)
                return;

        if (m_pos.x()==m_destinationWayPoint->pos().x()
                &&m_pos.y()==m_destinationWayPoint->pos().y())
        {
                // 敌人抵达了一个拐点
                if (m_destinationWayPoint->nextWayPoint())
                {
                        // 还有下一个点
                        m_pos = m_destinationWayPoint->pos();
                        m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
                }
                else
                {
                        // 表示进入基地
                    //进一步实现消除敌人
                        return;
                }
        }

        // 还在前往航点的路上
        // 目标航点的坐标
        QPoint targetPoint = m_destinationWayPoint->pos();
        // 未来修改这个可以添加移动状态,加快,减慢
        double movementSpeed = m_walkingSpeed;
        QVector2D normalized(targetPoint - m_pos);
        normalized.normalize();
        m_pos = m_pos + normalized.toPoint() * movementSpeed;
}

void Enemy::draw(QPainter *painter) const
{
        if (!m_active)
                return;

        painter->save();

    QPoint healthBarPoint = m_pos + QPoint((-Health_Bar_Width / 2 -3),
                                           (-52 / 3-10));
        // 绘制血条
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::red);
        QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
        painter->drawRect(healthBarBackRect);

        painter->setBrush(Qt::green);
        QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
        painter->drawRect(healthBarRect);

        // 绘制偏转坐标,由中心+偏移=左上
        static const QPoint offsetPoint(-52 / 2, -52 / 2);
        painter->translate(m_pos);

        QTime time=QTime::currentTime();
        if(this->pos().y()<m_destinationWayPoint->pos().y()
            ||this->pos().y()>m_destinationWayPoint->pos().y()){
        if(time.second()%2==1){
            painter->drawPixmap(offsetPoint, m_sprite);
        }
        else
            painter->drawPixmap(offsetPoint,m_sprite1);
    }
    else if(this->pos().x()<m_destinationWayPoint->pos().x()){
        if(time.second()%4==1)
            painter->drawPixmap(offsetPoint,m_sprite2);
        else if(time.second()%4==2)
            painter->drawPixmap(offsetPoint,m_sprite3);
        else if(time.second()%4==3)
            painter->drawPixmap(offsetPoint,m_sprite4);
        else
            painter->drawPixmap(offsetPoint,m_sprite3);
    }
    else if(this->pos().x()>m_destinationWayPoint->pos().x()){//只有QImage可以镜像
        QImage image1=m_sprite2.toImage();
        QImage image2=m_sprite3.toImage();
        QImage image3=m_sprite4.toImage();
        image1 = image1.mirrored(true, false);
        image2 = image2.mirrored(true, false);
        image3 = image3.mirrored(true, false);
        QPixmap pixmap1= QPixmap::fromImage(image1);
        QPixmap pixmap2= QPixmap::fromImage(image2);
        QPixmap pixmap3= QPixmap::fromImage(image3);
        if(time.second()%4==1)
            painter->drawPixmap(offsetPoint,pixmap1);
        else if(time.second()%4==2)
            painter->drawPixmap(offsetPoint,pixmap2);
        else if(time.second()%4==3)
            painter->drawPixmap(offsetPoint,pixmap3);
        else
            painter->drawPixmap(offsetPoint,pixmap2);
    }

        painter->restore();
}

void Enemy::getRemoved()
{
    //阵亡信息
}

void Enemy::getDamage(int damage)
{
    //移除敌人
}


QPoint Enemy::pos() const
{
    return m_pos;
}
