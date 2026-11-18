#include "MainViewController.h"

#include "dcmtk/dcmdata/dctk.h"

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
  ParseImage(file_path);
  ParseMetadata(file_path);
}

void MainViewController::ParseImage(const QString &file_path) {
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