#!/bin/bash
# 2016-2018, Gilles Casse <gcasse@oralux.org>
#

source conf.inc

check_distro

if [ "$ARCH" != amd64 ]; then
    echo "Sorry, this build is only for a 64 bits CPU. Send an email to contact@oralux.org if 32 bits support is still required."
    exit 0    
fi

$check_libvoxin
if [ "$?" != "0" ]; then 
    echo "install Voxin >= 1.00 before running this script."
    exit 0
fi

if [ "$(id -u)" != "0" ]; then
    echo "please run this script as root."
    exit 0
fi  

$check_speakup
if [ "$?" != "0" ]; then
    echo "install speakup before running this script."
    exit 0    
fi

echo "initialization; please wait... "
$install_connector

