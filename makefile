# ---------------------------------------------------------------------------
# Имя проекта

ifeq ($(OS),Windows_NT)
	DEL := del
	CAT := type
else
	DEL := rm -f
	CAT := cat
endif

NAME	= anim_led

# Настройки компилятора и линкера

CC      = sdcc
CFLAGS  = -I./INCLUDE -c --stack-auto
LFLAGS  = --code-loc 0x2100 --xram-loc 0x6000 --stack-auto --stack-loc 0x80

# Настройки системы автоинкремента версии сборки

PROJECT  = $(shell $(CAT) PROJECT)
VERSION  = $(shell $(CAT) VERSION)
BUILD    = $(shell $(CAT) BUILD)
TYPE     = $(shell $(CAT) TYPE)

PROJNAME = ${PROJECT}-${VERSION}-${BUILD}-${TYPE}
TARBALL  = ${PROJNAME}.tar

# Настройки M3P

M3P		 = m3p
COMPORT	 = com1
COMLOG	 = $(COMPORT)_log.txt
BAUD	 = 9600

# Каталоги с исходными текстами

SRC_DIR 	= SRC
# ---------------------------------------------------------------------------

all: $(NAME)

clean:
	$(DEL) $(NAME).hex
	$(DEL) $(NAME).bin
	$(DEL) $(NAME).map
	$(DEL) $(NAME).mem
	$(DEL) $(NAME).lnk
	$(DEL) pm3p_*.txt
	$(DEL) com?_log.txt

	$(DEL) $(TARBALL).gz
	$(DEL) $(SRC_DIR)/*.asm
	$(DEL) $(SRC_DIR)/*.rel
	$(DEL) $(SRC_DIR)/*.rst
	$(DEL) $(SRC_DIR)/*.sym
	$(DEL) $(SRC_DIR)/*.lst

load:
	$(M3P) lfile load.m3p

dist:
	tar -cvf $(TARBALL) --exclude=*.tar .
	gzip $(TARBALL)

term:
	$(M3P) echo $(COMLOG) $(BAUD)  openchannel $(COMPORT) +echo 6 term -echo bye

LIST_SRC = \
$(SRC_DIR)/led.c \
$(SRC_DIR)/max.c \
$(SRC_DIR)/timer.c \
$(SRC_DIR)/common.c \
$(SRC_DIR)/counter.c \
$(SRC_DIR)/main.c

LIST_OBJ = $(LIST_SRC:.c=.rel)

anim_led : $(LIST_OBJ) makefile
	$(CC) $(LIST_OBJ) -o anim_led.hex $(LFLAGS)
	$(M3P) hb166 anim_led.hex anim_led.bin bye


$(LIST_OBJ) : %.rel : %.c makefile
	$(CC) -c $(CFLAGS) $< -o $@
