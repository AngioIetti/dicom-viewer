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

} // namespace view

#endif // STYLE_SHEETS_H