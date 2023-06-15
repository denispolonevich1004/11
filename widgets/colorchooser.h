#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <QLabel>

QT_BEGIN_NAMESPACE
class QColor;
class QPixmap;
class QPainter;
class QMouseEvent;
class QColorDialog;
QT_END_NAMESPACE

/**
 * @brief Widget for selecting color.
 *
 */
class ColorChooser : public QLabel
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param parent Pointer for parent.
     */
    explicit ColorChooser(const int &r, const int &g, const int &b,
                          QWidget *parent = 0);
    ~ColorChooser();
    
private:
    QColor *mCurrentColor;
    QPixmap *mPixmapColor;
    QPainter *mPainterColor;

public slots:
    /**
     * @brief Slot for set color to widget.
     *
     * @param color Color to set.
     */
    void setColor(const QColor &color);

signals:
    /**
     * @brief Signal for sending choosen color
     *
     * @param Color to send
     */
    void sendColor(const QColor &);

protected:
    void mousePressEvent(QMouseEvent *event);
    
};

#endif // COLORCHOOSER_H
