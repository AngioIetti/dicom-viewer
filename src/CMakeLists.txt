qt_add_executable(dicom-viewer
    main.cpp
)

target_link_libraries(dicom-viewer
    PRIVATE Qt6::Widgets
)