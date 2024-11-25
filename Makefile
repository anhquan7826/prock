MODULE_NAME 			:= mod_prock

SRC 					+= src/prock.c
SRC 					+= src/module.c

KDIR 					:= /lib/modules/$(shell uname -r)/build
BUILD_DIR 				:= $(PWD)/build
BUILD_DIR_MAKEFILE 		:= $(BUILD_DIR)/Makefile

obj-m 					:= $(MODULE_NAME).o
$(MODULE_NAME)-y	 	:= $(SRC:.c=.o)

EXTRA_CFLAGS := -I$(PWD)/include

all: $(BUILD_DIR_MAKEFILE)
	$(MAKE) -C $(KDIR) M=$(BUILD_DIR) src=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(BUILD_DIR) src=$(PWD) clean

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	touch "$@"

$(BUILD_DIR):
	mkdir -p "$@"