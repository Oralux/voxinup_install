#!/bin/bash
# 2016-2018, Gilles Casse <gcasse@oralux.org>
#

source conf.inc

check_distro

$check_voxin
if [ "$?" != "0" ]; then 
    echo "install Voxin >= 2.00 before running this script."
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

