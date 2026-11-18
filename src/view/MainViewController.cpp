#include "MainViewController.h"

namespace view {

MainViewController::MainViewController() : main_view_(new MainView()) {
  connect(main_view_, &MainView::SignalFileSelected, this,
          &MainViewController::OnFileSelected);
}

MainViewController::~MainViewController() {
    delete main_view_;
}

void MainViewController::Exec() { 
    main_view_->show();
}

void MainViewController::OnFileSelected(const QString &file_path) {
  dicom_image_ = std::make_unique<DicomImage>(file_path.toStdString().c_str());

  if (dicom_image_->getStatus() != EIS_Normal) {
    main_view_->DisplayMessage("Failed to load DICOM image");
    return;
  }

  if (!dicom_image_->isMonochrome()) {
    main_view_->DisplayMessage("DICOM image is not monochrome");
    return;
  }

  dicom_image_->setMinMaxWindow();
  const auto *pixels =
      static_cast<const uint8_t *>(dicom_image_->getOutputData(8));
  const auto width = dicom_image_->getWidth();
  const auto height = dicom_image_->getHeight();

  if (!pixels || width == 0 || height == 0) {
    main_view_->DisplayMessage("Invalid image data");
    return;
  }

  main_view_->DisplayImage(pixels, width, height);
  main_view_->DisplayMessage("Image loaded successfully");
}

} // namespace view