# Make command to use for dependencies
MAKE=gmake
RM=rm
MKDIR=mkdir
CP=cp

OUTDIR=../../bin
INSTDIR = /usr/lib64

# -----Begin user-editable area-----

# -----End user-editable area-----

INTERDIR=InterDir
OUTFILENAME=libamd-spl.so
OUTFILE=$(OUTDIR)/$(OUTFILENAME)

CFG_INC=-I../../include -I../../include/core/cal \
	-I../../src/core/utils -I/usr/local/atical/include 
CFG_LIB=-laticalrt -laticalcl
CFG_OBJ=
COMMON_OBJ=$(INTERDIR)/Timer.o $(INTERDIR)/Runtime.o \
	$(INTERDIR)/BufferManager.o $(INTERDIR)/Buffer.o $(INTERDIR)/ConstBuffer.o $(INTERDIR)/LocalBuffer.o $(INTERDIR)/RemoteBuffer.o $(INTERDIR)/PinnedBuffer.o \
	$(INTERDIR)/ProgramManager.o $(INTERDIR)/Program.o $(INTERDIR)/GeneralProgram.o $(INTERDIR)/ComputeProgram.o \
	$(INTERDIR)/CounterManager.o $(INTERDIR)/PerfCounter.o \
	$(INTERDIR)/DeviceManager.o $(INTERDIR)/Device.o $(INTERDIR)/Event.o \
	$(INTERDIR)/Utility.o $(INTERDIR)/SplBitonicSort.o \
	 
OBJ=$(COMMON_OBJ) $(CFG_OBJ)

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

# Install the so file to lib directory
install: all
	$(CP) -t $(INSTDIR) $(OUTFILE)
	
uninstall:
	$(RM) -f $(INSTDIR)/$(OUTFILENAME)
  
# Clean this project
clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJ)

# Clean this project and all dependencies
cleanall: clean
