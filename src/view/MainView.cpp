#include "MainView.h"

#include <QFileDialog>
#include <QFormLayout>
#include <QHeaderView>
#include <QPalette>
#include <QSignalBlocker>

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

  // Window width / level sliders
  window_width_label_ = new QLabel();
  window_level_label_ = new QLabel();
  window_width_label_->setStyleSheet(view::kLabelStyle);
  window_level_label_->setStyleSheet(view::kLabelStyle);
  window_width_slider_ = CreateWindowSlider();
  window_level_slider_ = CreateWindowSlider();

  window_controls_ = new QWidget();
  auto *sliders_layout = new QFormLayout(window_controls_);
  sliders_layout->setContentsMargins(0, 0, 0, 0);
  sliders_layout->addRow(window_width_label_, window_width_slider_);
  sliders_layout->addRow(window_level_label_, window_level_slider_);
  window_controls_->hide();

  // Left side: image, window sliders, browse button and message console
  auto *left_layout = new QVBoxLayout();
  left_layout->addWidget(image_label_, 1);
  left_layout->addWidget(window_controls_);
  left_layout->addWidget(browse_button_);
  left_layout->addWidget(message_box_);

  // Main layout: left side + metadata
  layout_ = new QHBoxLayout(this);
  layout_->addLayout(left_layout, 2);
  layout_->addWidget(metadata_table_, 1);
}

MainView::~MainView() {}

void MainView::DisplayImage(const uint8_t *pixels, int width, int height,
                            bool is_color) {
  const QImage image =
      is_color
          ? QImage(pixels, width, height, 3 * width, QImage::Format_RGB888)
          : QImage(pixels, width, height, width, QImage::Format_Grayscale8);
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

QSlider *MainView::CreateWindowSlider() {
  auto *slider = new QSlider(Qt::Horizontal);
  slider->setStyleSheet(view::kSliderStyle);
  connect(slider, &QSlider::valueChanged, this,
          &MainView::OnWindowSliderChanged);
  return slider;
}

void MainView::SetWindowControls(int min_level, int max_level, int max_width,
                                 int level, int width) {
  const QSignalBlocker width_blocker(window_width_slider_);
  const QSignalBlocker level_blocker(window_level_slider_);
  window_width_slider_->setRange(1, max_width);
  window_width_slider_->setValue(width);
  window_level_slider_->setRange(min_level, max_level);
  window_level_slider_->setValue(level);
  UpdateWindowLabels();
  window_controls_->show();
}

void MainView::HideWindowControls() { 
  window_controls_->hide();
}

void MainView::OnWindowSliderChanged() {
  UpdateWindowLabels();
  SignalWindowChanged(window_width_slider_->value(),
                      window_level_slider_->value());
}

void MainView::UpdateWindowLabels() {
  window_width_label_->setText(
      QString("Width: %1").arg(window_width_slider_->value()));
  window_level_label_->setText(
      QString("Level: %1").arg(window_level_slider_->value()));
}

} // namespace view