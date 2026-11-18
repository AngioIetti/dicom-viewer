#ifndef STYLE_SHEETS_H
#define STYLE_SHEETS_H

namespace view {
constexpr const char *kLabelStyle = "QLabel {"
                                    "    background-color: black;"
                                    "    color: white;"
                                    "}";

constexpr const char *kButtonStyle = "QPushButton {"
                                     "    background-color: black;"
                                     "    color: white;"
                                     "    border: 1px solid #555;"
                                     "    padding: 8px 20px;"
                                     "}"
                                     "QPushButton:hover {"
                                     "    background-color: #222;"
                                     "}"
                                     "QPushButton:pressed {"
                                     "    background-color: #333;"
                                     "}";

constexpr const char *kErrorConsoleStyle = "QPlainTextEdit {"
                                           "    background-color: #000000;"
                                           "    color: #ffffff;"
                                           "    border: 1px solid #555555;"
                                           "}";

constexpr const char *kMetadataTableStyle = "QTableWidget {"
                                            "    background-color: #111111;"
                                            "    color: white;"
                                            "    gridline-color: #333333;"
                                            "    border: 1px solid #333333;"
                                            "    selection-background-color: #333333;"
                                            "    selection-color: white;"
                                            "}"
                                            "QHeaderView::section {"
                                            "    background-color: #222222;"
                                            "    color: white;"
                                            "    padding: 5px;"
                                            "    border: 1px solid #333333;"
                                            "}"
                                            "QTableWidget::item {"
                                            "    padding: 4px;"
                                            "}";

constexpr const char *kSliderStyle = "QSlider::groove:horizontal {"
                                     "    background: #333333;"
                                     "    height: 4px;"
                                     "}"
                                     "QSlider::sub-page:horizontal {"
                                     "    background: #888888;"
                                     "}"
                                     "QSlider::handle:horizontal {"
                                     "    background: white;"
                                     "    width: 12px;"
                                     "    margin: -5px 0;"
                                     "    border-radius: 6px;"
                                     "}";

} // namespace view

#endif // STYLE_SHEETS_H