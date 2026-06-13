VERSION = 1.5-beta
MACHINE := $(shell uname -m)
KERNELNAME := $(shell uname -s)

OBJ = \
 substitute-$(VERSION)/S \
 substitute-$(VERSION)/ChangeLog.txt \
 substitute-$(VERSION)/COPYING.txt \
 substitute-$(VERSION)/README.md

all:
	@echo "tag:        tag archive"
	@echo "dist:       create source tar ball of tag"
	@echo "disthead:   create source tar ball of current HEAD"
	@echo "bin:        create binary package"
	@echo "zip:        create binary zip package for Windows"
tag:
	cd ..; git tag -a v$(VERSION) -m "Tagging Substitute release $(VERSION)."
	cd ..; git push origin v$(VERSION)

dist:
	cd ..; git archive --prefix=substitute-$(VERSION)/ --format tar.gz -o substitute-$(VERSION).tar.gz v$(VERSION)

disthead:
	cd ..; git archive --prefix=substitute-head/ --format tar.gz -o substitute-head.tar.gz HEAD

bin:
	rm -rf ../substitute-$(VERSION)
	cd ..; tar xaf substitute-$(VERSION).tar.gz
	cd ../substitute-$(VERSION); rm -rf build
	cd ../substitute-$(VERSION); cmake -B build
	cd ../substitute-$(VERSION); cmake --build build
	cd ../substitute-$(VERSION); cp build/src/S .
	cd ..; tar caf substitute-$(VERSION)-$(KERNELNAME)-$(MACHINE).tar.gz $(OBJ)

zip:
	rm -rf ../substitute-$(VERSION)
	cd ..; tar xaf substitute-$(VERSION).tar.gz
	cd ../substitute-$(VERSION); make clean
	cd ../substitute-$(VERSION); make -f mingw.mak
	cp /mingw64/bin/libgnurx-0.dll ../substitute-$(VERSION)
	cd ..; zip substitute-$(VERSION)-$(KERNELNAME)-$(MACHINE).zip $(OBJ) substitute-$(VERSION)/S.exe substitute-$(VERSION)/libgnurx-0.dll
