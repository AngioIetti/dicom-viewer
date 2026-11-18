#include "MainViewController.h"

#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimage/diregist.h"

#include <algorithm>
#include <cmath>

namespace view {

MainViewController::MainViewController() : main_view_(new MainView()) {
  connect(main_view_, &MainView::SignalFileSelected, this,
          &MainViewController::OnFileSelected);
  connect(main_view_, &MainView::SignalWindowChanged, this,
          &MainViewController::OnWindowChanged);
}

MainViewController::~MainViewController() {
    delete main_view_;
}

void MainViewController::Exec() { 
    main_view_->show();
}

void MainViewController::OnFileSelected(const QString &file_path) {
  ParseImage(file_path);
  ParseMetadata(file_path);
}

void MainViewController::ParseImage(const QString &file_path) {
  main_view_->HideWindowControls();

  dicom_image_ = std::make_unique<DicomImage>(file_path.toStdString().c_str());

  if (dicom_image_->getStatus() != EIS_Normal) {
    main_view_->DisplayMessage("Failed to load DICOM image");
    dicom_image_ = nullptr;
    return;
  }

  if (dicom_image_->isMonochrome()) {
    InitWindow();
  }

  if (!RenderImage()) {
    main_view_->HideWindowControls();
    main_view_->DisplayMessage("Invalid image data");
    return;
  }

  main_view_->DisplayMessage("Image loaded successfully");
}

void MainViewController::OnWindowChanged(int width, int level) {
  if (!dicom_image_ || !dicom_image_->isMonochrome()) {
    return;
  }

  dicom_image_->setWindow(level, width);
  if (!RenderImage()) {
    main_view_->DisplayMessage("Failed to render image");
  }
}

bool MainViewController::RenderImage() {
  const auto *pixels =
      static_cast<const uint8_t *>(dicom_image_->getOutputData(8));
  const auto width = dicom_image_->getWidth();
  const auto height = dicom_image_->getHeight();

  if (!pixels || width == 0 || height == 0) {
    return false;
  }

  main_view_->DisplayImage(pixels, width, height,
                           !dicom_image_->isMonochrome());
  return true;
}

void MainViewController::InitWindow() {
  dicom_image_->setMinMaxWindow();

  double min_value = 0.0;
  double max_value = 0.0;
  dicom_image_->getMinMaxValues(min_value, max_value, 0);

  double level = 0.0;
  double width = 0.0;
  dicom_image_->getWindow(level, width);

  const int level_value = static_cast<int>(std::floor(level));
  const int width_value = std::max(1, static_cast<int>(std::floor(width)));
  const int min_level = static_cast<int>(std::floor(min_value));
  const int max_level = static_cast<int>(std::ceil(max_value));
  const int max_width = width_value;

  main_view_->SetWindowControls(min_level, max_level, max_width, level_value,
                                width_value);
}

void MainViewController::ParseMetadata(const QString &file_path) {
  DcmFileFormat file_format;
  if (file_format.loadFile(file_path.toStdString().c_str()).bad()) {
    main_view_->DisplayMessage("Failed to load DICOM metadata");
    return;
  }

  DcmDataset *dataset = file_format.getDataset();
  if (!dataset) {
    main_view_->DisplayMessage("Invalid DICOM dataset");
    return;
  }

  DcmStack stack;
  while (dataset->nextObject(stack, OFTrue).good()) {
    DcmObject *obj = stack.top();
    DcmTagKey tag = obj->getTag();

    if (tag.isPrivate()) {
      continue;
    }

    if (!obj->isLeaf()) {
      continue;
    }

    DcmElement *elem = OFstatic_cast(DcmElement *, obj);
    OFString value;
    if (elem->getOFStringArray(value).good()) {
      main_view_->DisplayMetadata(DcmTag(tag).getTagName(), value.c_str());
    }
  }
}

} // namespace view