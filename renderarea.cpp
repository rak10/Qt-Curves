#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor (0, 0, 255),
    mShapeColor (255, 255, 255),
    mShape(Asteroid)
{
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint()  const
{
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(mBackgroundColor);
    painter.setRenderHint(QPainter::Antialiasing, true);


    switch (mShape) {
    case Asteroid:
        mBackgroundColor = Qt::red;
        break;

    case Cycloid:
        mBackgroundColor = Qt::green;
        break;

    case HuygensCycloid:
        mBackgroundColor = Qt::blue;
        break;

    case HypoCycloid:
        mBackgroundColor = Qt::yellow;
        break;

    }

     painter.setBrush(mBackgroundColor);
     painter.setPen(mShapeColor);

    //drawing area
    painter.drawRect(this->rect());
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());



}
