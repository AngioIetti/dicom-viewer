file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "*.cpp"
    "*.h"
)

qt_add_executable(dicom-viewer
    ${SOURCES}
)

target_link_libraries(dicom-viewer
    PRIVATE Qt6::Widgets
    DCMTK::DCMTK
)