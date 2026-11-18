#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSlider>
#include <QTableWidget>
#include <QWidget>

namespace view {

class MainView : public QWidget {
  Q_OBJECT
public:
  MainView();
  ~MainView();

  void DisplayImage(const uint8_t *pixels, int width, int height);
  void DisplayMessage(const QString &message);
  void DisplayMetadata(const QString &tag, const QString &value);
  void SetWindowControls(int min_level, int max_level, int max_width, int level,
                         int width);

Q_SIGNALS:
  void SignalFileSelected(const QString &file_path);
  void SignalWindowChanged(int width, int level);

private:
  void OnBrowseButtonClicked();
  void OnWindowSliderChanged();
  void UpdateWindowLabels();
  QSlider *CreateWindowSlider();

  QLabel *image_label_;
  QPushButton *browse_button_;
  QBoxLayout *layout_;
  QPlainTextEdit *message_box_;
  QTableWidget *metadata_table_;

  QWidget *window_controls_;
  QSlider *window_width_slider_;
  QSlider *window_level_slider_;
  QLabel *window_width_label_;
  QLabel *window_level_label_;
};

} // namespace view

#endif // MAIN_VIEW_H