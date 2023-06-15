#ifndef ADDITIONALTOOLS_H
#define ADDITIONALTOOLS_H

#include <QtCore/QObject>
#include <QImage>

QT_BEGIN_NAMESPACE
class ImageArea;
class QSize;
QT_END_NAMESPACE

/**
 * @brief Class for implementation of additional tools which changing state of image.
 *
 */
class AdditionalTools : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param pImageArea A pointer to ImageArea.
     * @param parent Pointer for parent.
     */
    explicit AdditionalTools(ImageArea *pImageArea, QObject *parent);
    ~AdditionalTools();

    /**
     * @brief Resize image area
     *
     * @param width
     * @param height
     */
    void resizeCanvas(int width, int height, bool flag = false);

    /**
     * @brief Resize image
     *
     */
    void resizeImage();

    /**
     * @brief Rotate image
     *
     * @param flag Left or right
     */
    void rotateImage(bool flag);
    /**
     * @brief Zoom image
     *
     * @param factor Scale factor
     * @return returns true in case of success
     */
    bool zoomImage(qreal factor);
    bool rotateImage(int x,int y);
    
private:
    ImageArea *mPImageArea; /**< A pointer to ImageArea */
    ImageArea *mPOriginalImageArea; /**< A pointer to ImageArea */
    qreal mZoomedFactor; /**< Difference between original and current image */

signals:
    void sendNewImageSize(const QSize&);
    
public slots:
    
};

#endif // ADDITIONALTOOLS_H
