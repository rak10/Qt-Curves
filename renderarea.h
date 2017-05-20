#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint()  const Q_DECL_OVERRIDE;

    enum ShapeType { Asteroid, Cycloid, HuygensCycloid, HypoCycloid  };

    void setBackgroundColor (QColor color) { mBackgroundColor = color; }
    QColor backgroundColor() const { return mBackgroundColor; }

    void setShape (ShapeType shape) { mShape = shape; }
    ShapeType getShape() const { return mShape; }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;

};

#endif // RENDERAREA_H
