# Make command to use for dependencies
MAKE=gmake
RM=rm
MKDIR=mkdir

OUTDIR=../../bin

# -----Begin user-editable area-----

# -----End user-editable area-----

# If no configuration is specified, "Debug" will be used
ifndef "CFG"
CFG=Debug
endif

#
# Configuration: Debug
#
ifeq "$(CFG)" "Debug"
INTERDIR=Debug
OUTFILE=$(OUTDIR)/libamd-spl_d.so
CFG_INC=-I../../include -I../../include/core/cal \
	-I../../src/core/utils -I/usr/local/atical/include 
CFG_LIB=-lamdcalrt -lamdcalcl 
CFG_OBJ=
COMMON_OBJ=$(INTERDIR)/Timer.o $(INTERDIR)/Buffer.o \
	$(INTERDIR)/BufferManager.o $(INTERDIR)/ConstBuffer.o $(INTERDIR)/Device.o \
	$(INTERDIR)/DeviceManager.o $(INTERDIR)/Event.o $(INTERDIR)/GlobalBuffer.o \
	$(INTERDIR)/LocalBuffer.o $(INTERDIR)/Program.o \
	$(INTERDIR)/ProgramManager.o $(INTERDIR)/RemoteBuffer.o \
	$(INTERDIR)/Runtime.o $(INTERDIR)/Utility.o $(INTERDIR)/SplBitonicSort.o 
OBJ=$(COMMON_OBJ) $(CFG_OBJ)
ALL_OBJ=$(INTERDIR)/Timer.o $(INTERDIR)/Buffer.o \
	$(INTERDIR)/BufferManager.o $(INTERDIR)/ConstBuffer.o $(INTERDIR)/Device.o \
	$(INTERDIR)/DeviceManager.o $(INTERDIR)/Event.o $(INTERDIR)/GlobalBuffer.o \
	$(INTERDIR)/LocalBuffer.o $(INTERDIR)/Program.o \
	$(INTERDIR)/ProgramManager.o $(INTERDIR)/RemoteBuffer.o \
	$(INTERDIR)/Runtime.o $(INTERDIR)/Utility.o $(INTERDIR)/SplBitonicSort.o

COMPILE=g++ -c -fPIC -g -o "$(INTERDIR)/$(*F).o" $(CFG_INC) "$<"
LINK=g++  -shared -fPIC -g -o "$(OUTFILE)" $(OBJ) $(CFG_LIB)

# Pattern rules
$(INTERDIR)/%.o : ../../src/core/cal/%.cpp
	$(COMPILE)

$(INTERDIR)/%.o : ../../src/sort/%.cpp
	$(COMPILE)

$(INTERDIR)/%.o : ../../src/common/%.cpp
	$(COMPILE)

$(INTERDIR)/%.o : ../../src/core/utils/%.cpp
	$(COMPILE)

# Build rules
all: $(OUTFILE)

$(OUTFILE): $(OUTDIR) $(INTERDIR)  $(OBJ)
	$(LINK)
	
$(OUTDIR): 
	$(MKDIR) -p $(OUTDIR)

$(INTERDIR):
	$(MKDIR) -p "$(INTERDIR)"

# Rebuild this project
rebuild: cleanall all

# Clean this project
clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJ)

# Clean this project and all dependencies
cleanall: clean
endif

#
# Configuration: Release
#
ifeq "$(CFG)" "Release"
INTERDIR=Release
OUTFILE=$(OUTDIR)/libamd-spl.so
CFG_INC=-I../../include -I../../include/core/cal \
	-I../../src/core/utils -I/usr/local/atical/include 
CFG_LIB=-lamdcalrt -lamdcalcl
CFG_OBJ=
COMMON_OBJ=$(INTERDIR)/Timer.o $(INTERDIR)/Buffer.o \
	$(INTERDIR)/BufferManager.o $(INTERDIR)/ConstBuffer.o $(INTERDIR)/Device.o \
	$(INTERDIR)/DeviceManager.o $(INTERDIR)/Event.o $(INTERDIR)/GlobalBuffer.o \
	$(INTERDIR)/LocalBuffer.o $(INTERDIR)/Program.o \
	$(INTERDIR)/ProgramManager.o $(INTERDIR)/RemoteBuffer.o \
	$(INTERDIR)/Runtime.o $(INTERDIR)/Utility.o $(INTERDIR)/SplBitonicSort.o 
OBJ=$(COMMON_OBJ) $(CFG_OBJ)
ALL_OBJ=$(INTERDIR)/Timer.o $(INTERDIR)/Buffer.o \
	$(INTERDIR)/BufferManager.o $(INTERDIR)/ConstBuffer.o $(INTERDIR)/Device.o \
	$(INTERDIR)/DeviceManager.o $(INTERDIR)/Event.o $(INTERDIR)/GlobalBuffer.o \
	$(INTERDIR)/LocalBuffer.o $(INTERDIR)/Program.o \
	$(INTERDIR)/ProgramManager.o $(INTERDIR)/RemoteBuffer.o \
	$(INTERDIR)/Runtime.o $(INTERDIR)/Utility.o $(INTERDIR)/SplBitonicSort.o

COMPILE=g++ -c -fPIC  -o "$(INTERDIR)/$(*F).o" $(CFG_INC) "$<"
LINK=g++  -o "$(OUTFILE)" $(OBJ) $(CFG_LIB) -shared -fPIC

# Pattern rules
$(INTERDIR)/%.o : ../../src/core/cal/%.cpp
	$(COMPILE)

$(INTERDIR)/%.o : ../../src/sort/%.cpp
	$(COMPILE)

$(INTERDIR)/%.o : ../../src/common/%.cpp
	$(COMPILE)

$(INTERDIR)/%.o : ../../src/core/utils/%.cpp
	$(COMPILE)

# Build rules
all: $(OUTFILE)

$(OUTFILE): $(OUTDIR) $(INTERDIR)  $(OBJ)
	$(LINK)
	
$(OUTDIR): 
	$(MKDIR) -p $(OUTDIR)

$(INTERDIR):
	$(MKDIR) -p "$(INTERDIR)"

# Rebuild this project
rebuild: cleanall all

# Clean this project
clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJ)

# Clean this project and all dependencies
cleanall: clean
endif
