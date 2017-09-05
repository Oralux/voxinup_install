# voxinup program version
MAJ=2
MIN=3
REV=1

PN=voxinup
PV=$MAJ.$MIN.$REV

# packages version
PKG=1

# github url + sha256sum
ARCHIVE=$MAJ.$MIN.$REV.tar.gz
URL=https://github.com/Oralux/$PN/archive/$ARCHIVE
SHA256=2db806befa534af275ad8566d7a618dac5f20f5e8ffb7018413a3af1b1c81c8a

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
