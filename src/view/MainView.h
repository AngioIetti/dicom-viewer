#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

namespace view {

class MainView : public QWidget {
  Q_OBJECT
public:
  MainView();
  ~MainView();

  void DisplayImage(const uint8_t *pixels, int width, int height);

Q_SIGNALS:
  void SignalFileSelected(const QString &file_path);

private:
  void OnBrowseButtonClicked();
  QLabel *image_label_;
  QPushButton *browse_button_;
  QBoxLayout *layout_;
};

} // namespace view

#endif // MAIN_VIEW_H