#include "autoscrollinglabel.h"
#include <QPainter>

AutoScrollingLabel::AutoScrollingLabel(QWidget *parent) : QLabel(parent)
{
    px = 0;
    py = height()>>1;
//    speed = 2;
    direction = RightToLeft;

    this->timer = new QTimer(this) ;
    connect(this->timer, SIGNAL(timeout()), this, SLOT(refreshLabel()));
    timer->start(20);
}

void AutoScrollingLabel::refreshLabel()
{
    repaint();
}

AutoScrollingLabel::~AutoScrollingLabel()
{}

//void AutoScrollingLabel::show()
//{
//    QLabel::show();
//}

void AutoScrollingLabel::setAlignment(Qt::Alignment al)
{
    m_align = al;
    QLabel::setAlignment(al);
    updateCoordinates();
}

void AutoScrollingLabel::paintEvent(QPaintEvent *evt)
{
    if (this->textLength < this->width())
        QLabel::paintEvent(evt);
    else
    {
        QPainter p(this);
        if(direction==RightToLeft)
        {
    //        px -= speed;
            if(--px <= (-textLength))
                px = width();
        }
        else
        {
    //        px += speed;
            if(++px >= width())
                px = - textLength;
        }
        p.drawText(px, py + fontPointSize, text());
        p.translate(px,0);
    }
}

void AutoScrollingLabel::resizeEvent(QResizeEvent *evt)
{
    QLabel::resizeEvent(evt);
    updateCoordinates();
}

void AutoScrollingLabel::updateCoordinates()
{
    QRect bR = this->fontMetrics().boundingRect(this->text()) ;
    switch(m_align)
    {
        case Qt::AlignTop:
            py = bR.height() >> 1;
            break;
        case Qt::AlignBottom:
            py = height() - (bR.height()>>1) ;
            break;
        case Qt::AlignVCenter:
            py = height()>>1;
            break;
    }
    fontPointSize = font().pointSize()>>1;
    textLength = bR.width();
}

void AutoScrollingLabel::setTimerInterval(const int &s)
{
    this->timer->start(s);
}

int AutoScrollingLabel::getTimerInterval()
{
    return this->timer->interval();
}

void AutoScrollingLabel::setDirection(const Direction &d)
{
    direction = d;
    if (direction==RightToLeft)
        px = width() - textLength;
    else
        px = 0;
    refreshLabel();
}
