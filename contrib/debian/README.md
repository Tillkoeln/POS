
Debian
====================
This directory contains files used to package erexd/erex-qt
for Debian-based Linux systems. If you compile erexd/erex-qt yourself, there are some useful files here.

## erex: URI support ##


erex-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install erex-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your erexqt binary to `/usr/bin`
and the `../../share/pixmaps/erex128.png` to `/usr/share/pixmaps`

erex-qt.protocol (KDE)

