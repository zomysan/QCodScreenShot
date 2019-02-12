#ifndef PNGALPHA_H
#define PNGALPHA_H

class QPixmap;
class QImage;

// This prevent the image from conversion(png to jpg) by Twitter.
class ImageConverter
{
public:
  ImageConverter();
  static QPixmap convertToAlphaSecretly(const QPixmap &image);
  static QImage convertToAlphaSecretly(const QImage &image);
};

#endif // PNGALPHA_H
