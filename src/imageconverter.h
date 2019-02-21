#ifndef PNGALPHA_H
#define PNGALPHA_H

class QPixmap;
class QImage;
class QPoint;

// This prevent the image from conversion(png to jpg) by Twitter.
class ImageConverter
{
private:
  static QPoint ARROW_IMAGE_OFFSET;
public:
  ImageConverter();
  static QPixmap convertToAlphaSecretly(const QPixmap &image);
  static QImage convertToAlphaSecretly(const QImage &image);
  static QPixmap addArrow(const QPixmap &image, const QPoint point);
};

#endif // PNGALPHA_H
