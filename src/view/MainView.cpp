#include "MainView.h"

#include <QFileDialog>
#include <QPalette>

#include "StyleSheets.h"

namespace view {

MainView::MainView() {
  setWindowTitle("Main View");
  resize(1000, 800);
  setAutoFillBackground(true);
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::black);
  setPalette(palette);

  image_label_ = new QLabel("Open a DICOM image");
  image_label_->setAlignment(Qt::AlignCenter);
  image_label_->setMinimumSize(400, 300);
  image_label_->setStyleSheet(view::kLabelStyle);

  browse_button_ = new QPushButton("Browse...");
  browse_button_->setStyleSheet(view::kButtonStyle);
  connect(browse_button_, &QPushButton::clicked, this,
          &MainView::OnBrowseButtonClicked);

  message_box_ = new QPlainTextEdit();
  message_box_->setReadOnly(true);
  message_box_->setPlaceholderText("No messages");
  message_box_->setMaximumHeight(100);
  message_box_->setStyleSheet(view::kErrorConsoleStyle);

  layout_ = new QVBoxLayout(this);
  layout_->addWidget(image_label_, 1);
  layout_->addWidget(browse_button_);
  layout_->addWidget(message_box_);
}

MainView::~MainView() {}

void MainView::DisplayImage(const uint8_t *pixels, int width, int height) {
  QImage image(pixels, width, height, width, QImage::Format_Grayscale8);
  image_label_->setPixmap(QPixmap::fromImage(image).scaled(
      image_label_->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainView::DisplayMessage(const QString &message) {
  message_box_->appendPlainText(message);
}

void MainView::OnBrowseButtonClicked() {
  QString file_path =
      QFileDialog::getOpenFileName(this, "Open DICOM file", QDir::homePath(),
                                   "DICOM files (*.dcm);;All files (*)");
  if (!file_path.isEmpty()) {
    SignalFileSelected(file_path);
  }
}

} // namespace view