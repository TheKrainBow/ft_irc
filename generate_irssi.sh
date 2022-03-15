apt-get download irssi
dpkg -x irssi_*.deb extract
mv extract/usr/bin/irssi irssi
rm -rf extract irssi_*.deb