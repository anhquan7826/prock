FLUTTER = flutter
KVERSION = $(shell uname -r)
OBJDIR = build

all: module app

module:
	$(MAKE) -C /lib/modules/$(KVERSION)/build M=$(PWD) O=$(OBJDIR) modules

app:
	cd app/; \
	$(FLUTTER) build linux --release

clean: module_clean app_clean

app_clean:
	cd app/; $(FLUTTER) clean; rm -rf build/

module_clean:
	$(MAKE) -C /lib/modules/$(KVERSION)/build M=$(PWD) O=$(OBJDIR) clean