TARGET = update.exe
LDFLAGS = -mwindows
LIBS_PATH = ../libs
LIBS_NAME = IPHLPAPI wsock32 winmm mapi32 imm32 winspool comctl32 comdlg32 gdi32 ole32 user32 uuid getPcMsgApi wininet
SRC_PATH = ../util .
C_PATH = $(SRC_PATH)
CPP_PATH = $(SRC_PATH)

include ../include.mk
