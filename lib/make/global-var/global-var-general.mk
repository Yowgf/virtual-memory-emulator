# virtual-memory-emulator project Makefile
# General global variables custom definitions
# ==============================================================================
# Things included here are aren't specific to a single build, but rather touch
#   on all of them.
# ------------------------------------------------------------------------------

# Compiler command and flags
CXX   := 
FLAGS := -std=c++14 -Wall

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
