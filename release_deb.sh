#!/bin/bash

# Define variables
DEB_VERSION="0.0.0" # Modify to the desired default CMake version
DEB_PKG_NAME="osg3bg"
DEB_PKG_VERSION="${DEB_VERSION}-1"
JOBS=$(nproc)
TOP_DIR=$(dirname "$(readlink -f "$0")")

DEST_DEB_NAME=""

usage() {
    echo "Usage: $0 -v <deb_pkg_version> -o <deb_output_name>"
}


while getopts "hv:o:" opt; do
    case ${opt} in
        h)
            usage
            exit 1
            ;;
        v)
            DEB_PKG_VERSION="$OPTARG"
            ;;
        o)
            DEST_DEB_NAME="$OPTARG"
            ;;
        \?)
            echo "Invalid option: -$OPTARG"
            usage
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument."
            usage
            exit 1
            ;;
    esac
done

if [[ -n "${DEST_DEB_NAME}" && "${DEST_DEB_NAME}" != *.deb ]]; then
    echo "You provided dest deb name[${DEST_DEB_NAME}] but not ending with .deb"
    exit
fi


if [ -f /etc/lsb-release ]; then

    eval $(cat /etc/lsb-release)

    if [ "Ubuntu" == "${DISTRIB_ID}" ]; then
        DEB_DEPENDENCE="libc6, openscenegraph (= 3.4.0), osgearth (= 2.8)"
    fi

    if [ "Kylin" == "${DISTRIB_ID}" ]; then
        # kylin v10
        if [ "V10" == "${DISTRIB_RELEASE}" ]; then
            DEB_DEPENDENCE="libc6"
        fi

        # kylin v4
        if [[ "V4" == "${DISTRIB_RELEASE}" || "4.0.2" == "${DISTRIB_RELEASE}" ]]; then
            DEB_DEPENDENCE="libc6"
        fi
    fi

    if [ "uos" == "${DISTRIB_ID}" ]; then
        if [ "20" == "${DISTRIB_RELEASE}" ]; then
            DEB_DEPENDENCE="libc6"
        fi
    fi

fi


ARCH=$(dpkg --print-architecture) # Get the system architecture

# Create Debian package directory structure
DEB_DIR="${TOP_DIR}/${DEB_PKG_NAME}_${DEB_PKG_VERSION}"
mkdir -p "$DEB_DIR/DEBIAN"

# Compile
cmake -B build \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/usr \
    2>&1 | tee cmake.log &&
cmake --build build -- install DESTDIR="${DEB_DIR}/" -j `nproc` V=s 2>&1 | tee make.log


# Create control file
cat << EOF > "$DEB_DIR/DEBIAN/control"
Package: $DEB_PKG_NAME
Priority: optional
Section: devel
Version: $DEB_PKG_VERSION
Architecture: $ARCH
Depends: $DEB_DEPENDENCE
Maintainer: support <support@sietium.com>
Description: osg(3.6.5) beginner guide demos
EOF

# Build the Debian package
dpkg-deb --build "$DEB_DIR"

# Move the package to a desired location
if [ -n "${DEST_DEB_NAME}" ]; then
    mv "${DEB_DIR}.deb" ${DEST_DEB_NAME}
else
    mv "${DEB_DIR}.deb" .
fi


echo "CMake Debian package has been created."
