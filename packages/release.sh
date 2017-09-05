#!/bin/bash -evx

. ./conf.inc

function install_dep() {
    dpkg -V libvoxin1-dev
    su -c "apt-get update && apt-get install debhelper devscripts dh-systemd sox"
}

function build_pkg() {
    local PN=$1
    # local ARCH=
    # if [ -n "$2" ]; then
    # 	ARCH="-a $2"
    # fi
    local BUILD_DIR=build/$PN-$PV
    rm -rf $BUILD_DIR
    mkdir -p $BUILD_DIR

    cp build/$ARCHIVE $BUILD_DIR/${PN}_$PV.orig.tar.gz
    tar -C $BUILD_DIR -zxf build/$ARCHIVE
#    mv $BUILD_DIR/$PN-$PV $BUILD_DIR/$PN-$PV
    
    cp -a debian $BUILD_DIR/$PN-$PV/debian
    pushd $BUILD_DIR/$PN-$PV
    debuild -us -uc 
    popd
    rm -rf $BUILD_DIR/$PN-$PV
    find build -name "*deb" | while read i; do echo "--> $i"; lintian -i $i; done
}

[ ! -d build ] && mkdir build
cd build
download
cd ..

install_dep

if [ "$(uname -m)" = "x86_64" ]; then
    ARCH=amd64
else
    ARCH=i386
fi

rm -rf build.$ARCH
mkdir -p build.$ARCH

build_pkg $PN
mv build/$PN-$PV/* build.$ARCH
