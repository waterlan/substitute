VERSION = 1.4.3

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
tag:
	cd ..; git tag -a v$(VERSION) -m "Tagging Substitute release $(VERSION)."
	cd ..; git push origin v$(VERSION)

dist:
	cd ..; git archive --prefix=substitute-$(VERSION)/ --format tar.gz -o substitute-$(VERSION).tar.gz v$(VERSION)

disthead:
	cd ..; git archive --prefix=substitute-head/ --format tar.gz -o substitute-head.tar.gz HEAD

bin:
	cd ..; tar xaf substitute-$(VERSION).tar.gz
	cd ../substitute-$(VERSION); ./Compile
	cd ..; tar caf substitute-linux-x86_64-$(VERSION).tar.gz $(OBJ)
