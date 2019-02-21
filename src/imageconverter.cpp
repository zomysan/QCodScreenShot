#include "imageconverter.h"

#include <QPixmap>
#include <QImage>
#include <QPainter>

QPoint ImageConverter::ARROW_IMAGE_OFFSET = QPoint(12, 27); // arrow tip

ImageConverter::ImageConverter()
{

}

QPixmap ImageConverter::convertToAlphaSecretly(const QPixmap &image)
{
  return QPixmap::fromImage(convertToAlphaSecretly(image.toImage()));
}

QImage ImageConverter::convertToAlphaSecretly(const QImage &image)
{
  QImage newImage = image.convertToFormat(QImage::Format_ARGB32);

  // Make top-left pixel transparent(a little)
  QColor topLeftColor = image.pixelColor(0, 0);
  topLeftColor.setAlpha(254);
  newImage.setPixelColor(0, 0, topLeftColor);

  return newImage;
}

QPixmap ImageConverter::addArrow(const QPixmap &image, const QPoint point)
{
  QPixmap newImage = image.copy();
  QPainter painter(&newImage);
  QImage arrowImage;
  arrowImage.load("resource/arrow.png");
  painter.translate(-ARROW_IMAGE_OFFSET);
  painter.drawImage(point, arrowImage);
  return newImage;
}
