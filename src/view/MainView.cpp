#include "MainView.h"

#include <QFileDialog>
#include <QHeaderView>
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

  // Image
  image_label_ = new QLabel("Open a DICOM image");
  image_label_->setAlignment(Qt::AlignCenter);
  image_label_->setMinimumSize(400, 300);
  image_label_->setStyleSheet(view::kLabelStyle);

  // Metadata
  metadata_table_ = new QTableWidget(0, 2);
  metadata_table_->setHorizontalHeaderLabels({"Tag", "Value"});
  metadata_table_->horizontalHeader()->setStretchLastSection(true);
  metadata_table_->verticalHeader()->setVisible(false);
  metadata_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  metadata_table_->setSelectionBehavior(QAbstractItemView::SelectRows);
  metadata_table_->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Interactive);
  metadata_table_->setStyleSheet(view::kMetadataTableStyle);

  // Browse button
  browse_button_ = new QPushButton("Browse...");
  browse_button_->setStyleSheet(view::kButtonStyle);
  connect(browse_button_, &QPushButton::clicked, this,
          &MainView::OnBrowseButtonClicked);

  // Message console
  message_box_ = new QPlainTextEdit();
  message_box_->setReadOnly(true);
  message_box_->setPlaceholderText("No messages");
  message_box_->setMaximumHeight(100);
  message_box_->setStyleSheet(view::kErrorConsoleStyle);

  // Left side: image, browse button and message console
  auto *left_layout = new QVBoxLayout();
  left_layout->addWidget(image_label_, 1);
  left_layout->addWidget(browse_button_);
  left_layout->addWidget(message_box_);

  // Main layout: left side + metadata
  layout_ = new QHBoxLayout(this);
  layout_->addLayout(left_layout, 2);
  layout_->addWidget(metadata_table_, 1);
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

void MainView::DisplayMetadata(const QString &tag, const QString &value) {
  int row = metadata_table_->rowCount();
  metadata_table_->insertRow(row);
  metadata_table_->setItem(row, 0, new QTableWidgetItem(tag));
  metadata_table_->setItem(row, 1, new QTableWidgetItem(value));
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