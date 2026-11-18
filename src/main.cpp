#include <QApplication>

#include "view/MainViewController.h"
#include <dcmtk/dcmjpeg/djdecode.h>

struct DcmtkCodecGuard {
  DcmtkCodecGuard() { DJDecoderRegistration::registerCodecs(); }
  ~DcmtkCodecGuard() { DJDecoderRegistration::cleanup(); }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  DcmtkCodecGuard codec_guard;
  view::MainViewController main_view;
  main_view.Exec();

  return app.exec();
}