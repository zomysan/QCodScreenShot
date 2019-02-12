#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>

class Settings
{
public:
  QString path_;
  QString language_;
  QString filename_;
  QString filetype_;
  QRect geometry_;
  bool openDialog_;
  bool overwriteConfirm_;
  bool aggressivePngCompress_;
  bool forcePngAlpha_;
  bool stayOnTop_;
  int delaySecs_;
  int quality_;

public:
  // singleton
  static Settings &getInstance(void);

  // getter/setter
  void setPath(const QString &path) { path_ = path; }
  void setLanguage(const QString &language) { language_ = language; }
  void setFiletype(const QString &filetype) { filetype_ = filetype; }
  void setFilename(const QString &filename) { filename_ = filename; }
  void setGeometry(const QRect &geometry) { geometry_ = geometry; }
  void setOpenDialog(const bool &openDialog) { openDialog_ = openDialog; }
  void setOverwriteConfirm(const bool &overwriteConfirm) { overwriteConfirm_ = overwriteConfirm; }
  void setAggressivePngCompress(const bool &aggressivePngCompress) { aggressivePngCompress_ = aggressivePngCompress; }
  void setForcePngAlpha(const bool &forcePngAlpha) { forcePngAlpha_ = forcePngAlpha;}
  void setStayOnTop(const bool &stayOnTop) { stayOnTop_ = stayOnTop;}
  void setDelaySecs(int delaySecs) { delaySecs_ = delaySecs; }
  void setQuality(int quality) { quality_ = quality; }
  QString path(void){ return path_; }
  QString language(void){ return language_; }
  QString filetype(void){ return filetype_; }
  QString filename(void){ return filename_; }
  QRect geometry() const { return geometry_; }
  bool openDialog() const { return openDialog_; }
  bool overwriteConfirm() const { return overwriteConfirm_; }
  bool aggressivePngCompress() const { return aggressivePngCompress_; }
  bool forcePngAlpha() const { return forcePngAlpha_; }
  bool stayOnTop() const { return stayOnTop_; }
  int delaySecs() const { return delaySecs_; }
  int quality() const { return quality_; }

public slots:
  void writeData();

private:
  // singleton
  Settings();
  Settings(const Settings &){}
  Settings &operator=(const Settings &){}

  void readData();

  ~Settings();

};

#endif // SETTINGS_H
