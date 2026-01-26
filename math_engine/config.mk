ifndef ROOT_DIR
  $(error ROOT_DIR not set. Please run from master Makefile)
endif

PROJECT     := math_engine

# Directory structure
SRC_DIR     := $(ROOT_DIR)/src
INCLUDE_DIR := $(ROOT_DIR)/include
INCLUDE_MINIRT_DIR := $(MINIRT_DIR)/include
BUILD_DIR   := $(ROOT_DIR)/build
LIB_DIR     := $(BUILD_DIR)/lib
OBJ_DIR     := $(BUILD_DIR)/obj
BIN_DIR     := $(BUILD_DIR)/bin

CC          := gcc
# compile with -ffast-math and -march=native to get max math speed
CFLAGS      := -Wall -Wextra -Werror -pedantic -std=c99 -O2 -g -march=native -ffast-math
INCLUDES    := -I$(INCLUDE_DIR) -I$(INCLUDE_MINIRT_DIR)
AR          := ar
ARFLAGS     := rcs