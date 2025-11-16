CC := gcc
CFLAGS := -Wall -Werror
SRC := main.c
TARGET := bio

ifeq ($(OS),Windows_NT)
	EXE := .exe
	RUN_CMD := $(TARGET)$(EXE)
	RM_CMD := del /Q
	NULLDEV := NUL
else
	EXE :=
	RUN_CMD := ./$(TARGET)
	RM_CMD := rm -f
	NULLDEV := /dev/null
endif

.PHONY: build run clean

build:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)$(EXE)

run: build
	$(RUN_CMD)

clean:
ifeq ($(OS),Windows_NT)
	-$(RM_CMD) $(TARGET)$(EXE) 2>$(NULLDEV)
	-$(RM_CMD) adn.txt 2>$(NULLDEV)
else
	-$(RM_CMD) $(TARGET)$(EXE) adn.txt
endif
