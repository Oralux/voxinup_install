# voxinup program version
MAJ=2
MIN=2
REV=1

PN=voxinup
PV=$MAJ.$MIN.$REV

# packages version
PKG=1

# github url + sha256sum
ARCHIVE=$MAJ.$MIN.$REV.tar.gz
URL=https://github.com/Oralux/$PN/archive/$ARCHIVE
SHA256=069f8e29ed5a372ee4773c39c1f40e21db915f704ba679d44dd8b25676d0195e

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
