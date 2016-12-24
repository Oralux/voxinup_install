ARCH=$(uname -m)

###
check_distro()
{
    local status=1

    # Check if this is an arch linux based distro
    if [ -e "/etc/pacman.conf" ]; then
	check_speakup=arch_check_speakup
	check_libvoxin=arch_check_libvoxin
	install_connector=arch_install_connector
	uninstall_connector=arch_uninstall_connector
	status=0
    else
	# Check if this is a debian based distro
	type dpkg &> /dev/null
	if [ "$?" = "0" ]; then
	    check_speakup=debian_check_speakup
	    check_libvoxin=debian_check_libvoxin
	    install_connector=debian_install_connector
	    uninstall_connector=debian_uninstall_connector
	    status=0
	    if [ "$ARCH" = "x86_64" ]; then
		ARCH=amd64
	    else	
		ARCH=i386
	    fi
	fi
    fi
    return $status
}

# arch linux based commands
arch_check_speakup() {
    lsmod | grep -q speakup
}

arch_check_libvoxin() {
    pacman -Q libvoxin &> /dev/null    
}

arch_install_connector() {
    local e=0
    pacman -U build/archlinux/voxinup-*-$ARCH.pkg.tar.xz
    if [ "$?" != "0" ]; then
	return 1
    fi

    pacman -Q espeakup &> /dev/null    
    if [ "$?" = "0" ]; then
	e=1
	systemctl disable espeakup
    fi
    
    systemctl enable voxinup

    if [ "$e" = "1" ]; then
	echo "Trying to stop espeakup"
	systemctl stop espeakup
    fi
    systemctl start voxinup
}

arch_uninstall_connector() {
    systemctl disable voxinup
    systemctl stop voxinup
    pacman -Q espeakup &> /dev/null    
    if [ "$?" = "0" ]; then
	systemctl enable espeakup
	systemctl start espeakup
    fi
    pacman -R voxinup
}

# debian based specific commands
debian_check_speakup() {
    lsmod | grep -q speakup
}

debian_check_libvoxin() {
    dpkg -l "libvoxin*" &> /dev/null    
}

debian_install_connector() {
    # apt-get install -y lib32gcc1 libc6-i386 libasound2:i386
    apt-get remove -y espeakup
    dpkg -i build/debian/voxinup_*_$ARCH.deb
}

debian_uninstall_connector() {
    echo TODO
    apt-get remove -y voxinup
    apt-get install -y espeakup
}

