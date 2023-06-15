#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include "../imagearea.h"

#include <QDialog>
#include <QTextEdit>

/**
 * @brief QDialog for text instrument.
 *
 */
class TextDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param parent Pointer for parent.
     */
    explicit TextDialog(QString text, ImageArea *parent);
   
private:
    void initializeGui();
    QTextEdit *mTextEdit;
  
signals:
    void textChanged(ImageArea *, const QString);
    void canceled(ImageArea *);

private slots:
    void textChanged();
    void selectFont();    
    void cancel();
    void reject();
};

#endif // TEXTDIALOG_H
