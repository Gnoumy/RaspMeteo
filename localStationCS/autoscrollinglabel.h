#ifndef AUTOSCROLLINGLABEL_H
#define AUTOSCROLLINGLABEL_H


#include <QLabel>
#include <QTimer>

class AutoScrollingLabel : public QLabel
{
    Q_OBJECT

    public: //Member Functions
        enum Direction {RightToLeft, LeftToRight};
        AutoScrollingLabel(QWidget *parent = 0);
        ~AutoScrollingLabel();
//        void show();
        void setAlignment(Qt::Alignment);
        int getTimerInterval();

    public slots: //Public Member Slots
        void setTimerInterval(const int &s);
        void setDirection(const Direction &d);

    protected: //Member Functions
        void paintEvent(QPaintEvent *evt);
        void resizeEvent(QResizeEvent *evt);
        void updateCoordinates();

    private: //Data Members
        int px;
        int py;
        QTimer *timer;
        Qt::Alignment m_align;
//        int speed;
        Direction direction;
        int fontPointSize;
        int textLength;

    private slots: //Private Member Slots
        void refreshLabel();
};

#endif // AUTOSCROLLINGLABEL_H
