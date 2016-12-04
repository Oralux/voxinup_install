#!/bin/bash
# 2016, Gilles Casse <gcasse@oralux.org>
#

source conf.inc

check_distro

if [ "$(id -u)" != "0" ]; then
    echo "Please run this installer as root."
    exit 0
fi  

$uninstall_connector
