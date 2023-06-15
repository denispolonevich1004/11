#ifndef ABSTRACTEFFECT_H
#define ABSTRACTEFFECT_H

#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
class ImageArea;
QT_END_NAMESPACE

/**
 * @brief Abstract class for implementing effects.
 *
 */
class AbstractEffect : public QObject
{
    Q_OBJECT

public:
    explicit AbstractEffect(QObject *parent = 0);
    virtual ~AbstractEffect(){}

    virtual void applyEffect(ImageArea &imageArea) = 0;
    
protected:
    /**
     * @brief Creates UndoCommand & pushes it to UndoStack.
     *
     * Base realisation simply save all image to UndoStack
     * @param imageArea corresponse to image, which is edited
     */
    virtual void makeUndoCommand(ImageArea &imageArea);

};

#endif // ABSTRACTEFFECT_H
