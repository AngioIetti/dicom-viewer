# DICOM Viewer

Desktop application for opening a DICOM file and displaying its image and metadata.

- Monochrome and RGB images, including JPEG and RLE compressed files
- Window level and width adjustable with sliders
- Metadata shown in a table
- Error and success messages shown in a text box

The code follows a view/controller split: `MainView` (Qt widgets) emits signals, and `MainViewController` reads the file with DCMTK and updates the view.

## Libraries and versions

| Component | Version |
|-----------|---------|
| C++ | 20 |
| GCC | 13.3 |
| CMake | 3.28 |
| Ninja | 1.11 |
| Qt (Widgets) | 6.4.2 |
| DCMTK | 3.6.7 |

Versions are the Ubuntu 24.04 packages used by the Docker image.

## Build and run

The build output is `build/src/dicom-viewer`.

### Docker

Requires only Docker with the Compose plugin, on Linux with an X11 or Wayland desktop.

Install Docker and the Compose plugin (Ubuntu 24.04), and allow your user to run it without `sudo`:

```bash
sudo apt install docker.io docker-compose-v2
sudo usermod -aG docker $USER
```

Log out and back in (or reboot) so the group change takes effect. Check with `docker compose version`.

Then:

```bash
./scripts/build_docker.sh   # builds the image on first run, then configures and compiles
./scripts/run_docker.sh
```

Your home folder is mounted read-only inside the container, so its files can be opened from the file dialog. If the window does not appear ("could not connect to display"), run `xhost +local:` once.

### Native

Install the dependencies (Ubuntu 24.04):

```bash
sudo apt install build-essential cmake ninja-build qt6-base-dev libdcmtk-dev libnsl-dev
```

Then:

```bash
./scripts/build.sh          # configures and compiles
./scripts/run.sh
```

Both builds use the same `build/` folder. Delete it when switching between Docker and native, and use the matching run script: a binary built in Docker does not run natively.
