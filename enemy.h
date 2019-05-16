#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class MainWindow;

class Enemy : public QObject
{
        Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MainWindow *game,
          const QPixmap &sprite = QPixmap(":/image/enemy1_1.png"),
          const QPixmap &sprite1= QPixmap(":/image/enemy1_2.png"),
          const QPixmap &sprite2= QPixmap(":/image/enemy1_3.png"),
          const QPixmap &sprite3= QPixmap(":/image/enemy1_4.png"),
          const QPixmap &sprite4= QPixmap(":/image/enemy1_5.png"));
        ~Enemy();

        void draw(QPainter *painter) const;
        void move();
        void getDamage(int damage);
        void getRemoved();
    QPoint pos() const;

public slots:
        void doActivate();

private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    double			m_walkingSpeed;

    QPoint			m_pos;
    WayPoint *		        m_destinationWayPoint;

    const QPixmap   m_sprite; //妖精
    const QPixmap   m_sprite1;
    const QPixmap   m_sprite2;
    const QPixmap   m_sprite3;
    const QPixmap   m_sprite4;
};

#endif // ENEMY_H
