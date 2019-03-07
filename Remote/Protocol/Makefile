# Makefile for Yellow protobuf
# Aithor: gabriel.gruener@bfh.ch

# Our protocol definition
YELLOW_PROTO := yellow.proto

# Arm embedded output dir
ARM_DIR := ../../Software/src/ch/bfh/roboticsLab/yellow/communication

# Java output dir
JAVA_DIR := ../Java/src

# Executable of the nanopb compiler (for Arm embedded)
NANO_PROTOC := ~/Downloads/src/darwin/nanopb-0.3.9-macosx-x86/generator-bin/protoc

# Executable of the regular protoc
PROTOC = /usr/local/bin/protoc

.PHONY: all nano regular

all: nano regular

nano:
	$(NANO_PROTOC) --nanopb_out=$(ARM_DIR) $(YELLOW_PROTO)

regular:
	protoc --java_out=$(JAVA_DIR) $(YELLOW_PROTO)
