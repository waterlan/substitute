# MinGW needs libgnurx for regular expressions.
# pacman -S mingw-w64-x86_64-libgnurx


all:
	make EXTRA_LIBRARIES=-lgnurx
