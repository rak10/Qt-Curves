#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor (0, 0, 255),
    mPen(Qt::white),
    mShape(Asteroid)
{
    mPen.setWidth(2);
    on_shape_changed();

}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}

QSize RenderArea::sizeHint()  const
{
    return QSize(400, 400);
}

void RenderArea::on_shape_changed()
{

    switch (mShape) {
    case Asteroid:
        //load asteroid specific values
        mScale = 90;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;

    case Cycloid:
        mScale = 10;
        mIntervalLength = 4 * M_PI;
        mStepCount = 128;
        break;

    case HuygensCycloid:
        mScale = 4;
        mIntervalLength = 4 * M_PI;
        mStepCount = 256;
        break;

    case HypoCycloid:
        mScale = 40;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;

    case Line:
        mIntervalLength = 2;
        mScale = 100;
        mStepCount = 128;
        break;

   case Cloud1:
        mIntervalLength = 28 * M_PI;
        mScale = 10;
        mStepCount = 128;
        break;

   case Cloud2:
         mIntervalLength = 28 * M_PI;
         mScale = 10;
         mStepCount = 128;
         break;

   case Circle:
        mIntervalLength = 2 * M_PI;
        mScale = 100;
        mStepCount = 128;
        break;

   case Ellipse:
          mIntervalLength = 2 * M_PI;
          mScale = 75;
          mStepCount = 256;
          break;

    case Fancy:
           mIntervalLength = 12 * M_PI;
           mScale = 10;
           mStepCount = 512;
           break;

    case Starfish:
           mIntervalLength = 6 * M_PI;
           mScale = 25;
           mStepCount = 256;
           break;

    }
}

QPointF RenderArea::compute(float t)
{
    switch (mShape) {
    case Asteroid:
        return compute_asteroid(t);
        break;

    case Cycloid:
        return compute_cycloid(t);
        break;

    case HuygensCycloid:
        return compute_huygens(t);
        break;

    case HypoCycloid:
        return compute_hypo(t);
        break;

    case Line:
        return compute_line(t);
        break;

    case Cloud1:
        return compute_cloud1(t);
        break;

    case Cloud2:
        return compute_cloud2(t);
        break;

    case Circle:
        return compute_circle(t);
        break;

    case Ellipse:
        return compute_ellipse(t);
        break;

    case Fancy:
        return compute_fancy(t);
        break;

    case Starfish:
        return compute_starfish(t);
        break;

    default:
        break;
    }
    return QPointF (0,0);
}

QPointF RenderArea::compute_asteroid(float t)
{
    float cos_t = cos (t);
    float sin_t = sin (t);
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF (x, y);

}

QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF(
                1.5 * (1 - cos(t)) , //x coordinate
                1.5 * (t - sin(t))   //y coordinate
                );
}
QPointF RenderArea::compute_huygens(float t)
{
    return QPointF (
                4 * (3 * cos(t) - cos (3 * t)) , //x coordinate
                4 * (3 * sin(t) - sin (3 * t))   //y coordinate
                );
}
QPointF RenderArea::compute_hypo(float t) {
    return QPointF(
                1.5 * (2 * cos(t) + cos(2 * t)), //x coordinate
                1.5 * (2 * sin(t) - sin(2 * t))  //y coordinate
                );
}
QPointF RenderArea::compute_line(float t)
{
    return QPointF (
            1-t, 1 - t
                );
}

QPointF RenderArea::compute_cloud1(float t)
{
   return compute_cloud_with_sign(t, -1);
}

QPointF RenderArea::compute_cloud2(float t)
{
    return compute_cloud_with_sign(t, 1);
}

QPointF RenderArea::compute_cloud_with_sign (float t, float sign)
{
    float a = 14;
    float b = 1;

    float x = (a+b) * cos(t * b / a) + sign * b * cos(t*(a+b) / a);
    float y = (a+b) * sin(t * b / a) - b * sin(t*(a+b) / a);

    return QPointF(x,y);
}

QPointF RenderArea::compute_circle(float t)
{
    return QPointF(
                cos(t),
                sin(t)

                );
}

QPointF RenderArea::compute_ellipse(float t)
{
    float a = 2;
    float b = 1.1;

    return QPointF(
                a * cos(t),
                b * sin(t)
                );
}

QPointF RenderArea::compute_fancy(float t)
{
    return QPointF(
                11 * cos(t) - 6 * cos(11.0f * t / 6),
                11 * sin(t) - 6 * sin(11.0f * t / 6)
                );
}

QPointF RenderArea::compute_starfish(float t)
{
    float R = 5;
    float r = 3;
    float d = 5;

    return QPointF(
                (R - r) * cos (t) + d * cos(t * (R-r) / r),
                (R - r) * sin (t) - d * sin(t * (R-r) / r)

                );
}


void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(mBackgroundColor);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(mBackgroundColor);
    painter.setPen(mPen);

    //drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());


    float step = mIntervalLength / mStepCount;
    for (float t = 0; t< mIntervalLength; t += step)
    {
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());


        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }

    QPointF point = compute(mIntervalLength);

    QPoint pixel;
    pixel.setX(point.x() * mScale + center.x());
    pixel.setY(point.y() * mScale + center.y());


    painter.drawLine(pixel, prevPixel);



}
