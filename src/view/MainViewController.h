#ifndef MAIN_VIEW_CONTROLLER_H
#define MAIN_VIEW_CONTROLLER_H

#include "MainView.h"

#include <QObject>

#include <memory>

#include <dcmtk/dcmimgle/dcmimage.h>

namespace view {

class MainViewController : public QObject {
  Q_OBJECT
public:
  MainViewController();
  ~MainViewController();

  void Exec();

private:
  void OnFileSelected(const QString &file_path);

  void ParseImage(const QString &file_path);
  void ParseMetadata(const QString &file_path);

  MainView *main_view_;
  std::unique_ptr<DicomImage> dicom_image_;
};

} // namespace view

#endif // MAIN_VIEW_CONTROLLER_H