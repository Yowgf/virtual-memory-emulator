# virtual-memory-emulator project Makefile
# General global variables custom definitions
# ==============================================================================
# Things included here are aren't specific to a single build, but rather touch
#   on all of them.
# ------------------------------------------------------------------------------

# Compiler command and flags
CXX   := 
COMPILE_FLAGS := -std=c++14 -Wall -DBOOST_LOG_DYN_LINK
LINKING_FLAGS := -std=c++14 -Wall -lboost_log -lpthread

# Source directory
SOURCE := lib

# Directory of compiled files
BUILD := build

# Project's modules
MODULES := Alg Interface Memory Utils

# Files extensions
HEADER_EXTENSION     := 
APP_EXTENSION        := 
OBJECT_EXTENSION     := 
EXECUTABLE_EXTENSION := 
