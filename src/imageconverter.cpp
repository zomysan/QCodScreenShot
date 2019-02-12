#include "imageconverter.h"

#include <QPixmap>
#include <QImage>
#include <QPainter>

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
