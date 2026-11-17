#include <QApplication>
#include <QWidget>

#include <dcmtk/dcmdata/dctk.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DcmFileFormat file;
    OFCondition status = file.loadFile("anonymized_mamo.dcm");
    if (status.bad()) {
        throw std::runtime_error("Failed to load DICOM file");
    }

    DcmDataset *dataset = file.getDataset();
    OFString patientName;
    if (dataset->findAndGetOFString(DCM_PatientName, patientName).good()) {
        std::cout << "Patient Name: " << patientName.c_str() << std::endl;
    }

    QWidget window;
    window.resize(320, 240);
    window.setWindowTitle(
        QApplication::translate("toplevel", "DICOM Viewer"));
    window.show();

    return app.exec();
}