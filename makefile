# ##############################################################################
#
# Informática Gráfica (Grado Informática)
# Makefile (sirve para Linux y macOS)
#
# ##############################################################################

HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
OBJ = $(HOME)/obj
INCLUDE = $(HOME)/include
LIB = $(HOME)/lib

.SUFFIXES:
.PHONY: x

exe             := $(BIN)/pracs_exe
units_cc        := $(wildcard $(addprefix $(SRC)/, *.cc)) $(wildcard $(addprefix $(SRC)/, *.cpp))
units_o         := $(addprefix $(OBJ)/, $(addsuffix .o, $(notdir $(basename $(units_cc)))))
headers         := $(wildcard $(addprefix $(INCLUDE)/, *.h*))
uname           := $(shell uname -s)
en_macos        := $(findstring Darwin,$(uname))
en_linux        := $(findstring Linux,$(uname))
compiler        := $(if $(en_linux), g++, clang++ )
sistoper        := $(if $(en_macos), macOS, Linux )

cc_flags_common := -std=c++11 -g -I/usr/include -Iinclude
cc_flags_linux  := -DLINUX
cc_flags_macos  := -DMACOS
cc_flags        := $(cc_flags_common) $(if $(en_linux), $(cc_flags_linux), $(cc_flags_macos))

glu_flag_macos  := /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLU.dylib
ld_libs_common := -ljpeg
ld_libs_linux  := -lGLEW -lGLU -lglut -lGL
ld_libs_macos  := -framework OpenGL -framework GLUT $(glu_flag_macos)
ld_libs        := $(ld_libs_common) $(if $(en_linux), $(ld_libs_linux), $(ld_libs_macos))


x: $(exe)
	@echo Enlazando para: $(sistoper)
	$(exe)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe)  $(units_o) $(ld_libs)

$(OBJ)/%.o : src/%.cc
	$(compiler) -o $@ -c $(cc_flags) $<

$(OBJ)/%.o : src/%.cpp
	$(compiler) -o $@ -c $(cc_flags)

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	rm -rf $(OBJ)/*.o $(BIN)/*_exe
