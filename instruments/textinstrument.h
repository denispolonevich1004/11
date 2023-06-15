#ifndef TEXTINSTRUMENT_H
#define TEXTINSTRUMENT_H

#include "abstractselection.h"

#include <QtCore/QObject>

/**
 * @brief Text instrument class.
 *
 */
class TextInstrument : public AbstractSelection
{
    Q_OBJECT
public:
    explicit TextInstrument(QObject *parent = 0);

private:
    void startAdjusting(ImageArea &);
    void startSelection(ImageArea &);
    void startResizing(ImageArea &);
    void startMoving(ImageArea &);
    void select(ImageArea &);
    void resize(ImageArea &imageArea);
    void move(ImageArea &imageArea);
    void completeSelection(ImageArea &imageArea);
    void completeResizing(ImageArea &);
    void completeMoving(ImageArea &);
    void clear();
    void paint(ImageArea &imageArea, bool = false, bool = false);
    void showMenu(ImageArea &imageArea);

    QString mText;
    bool mIsEdited;

signals:
    void sendCloseTextDialog();

private slots:
    void updateText(ImageArea *, QString);
    /**
     * @brief Clears text and remove selection.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void cancel(ImageArea *);

};

#endif // TEXTINSTRUMENT_H
