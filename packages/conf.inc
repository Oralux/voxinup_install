# voxinup program version
MAJ=2
MIN=3
REV=2

PN=voxinup
PV=$MAJ.$MIN.$REV

# packages version
PKG=1

# github url + sha256sum
ARCHIVE=$MAJ.$MIN.$REV.tar.gz
URL=https://github.com/Oralux/$PN/archive/$ARCHIVE
SHA256=952c936a686107044937386c22713545243acd79b328f7c8309f60fd17f4ad39

# gnupg key used to sign packages
SIGNING_KEY=AED093E5


download()
{
    if [ ! -e "$ARCHIVE" ]; then
	wget $URL
    fi
    a=$(sha256sum "$ARCHIVE" | cut -f1 -d" ")
    if [ "$a" != "$SHA256" ]; then
	echo "$ARCHIVE: sha256 mismatch !"
	exit 1
    fi
}

extract()
{
    tar -zxf "$ARCHIVE"
}
