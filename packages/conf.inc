# voxinup program version
MAJ=2
MIN=3
REV=3

PN=voxinup
PV=$MAJ.$MIN.$REV

# packages version
PKG=1

# github url + sha256sum
ARCHIVE=$MAJ.$MIN.$REV.tar.gz
URL=https://github.com/Oralux/$PN/archive/$ARCHIVE
SHA256=510cbf8072ad5764ec611ba993ccb8208e62af3daace416e8327e7bda4e189f0

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
