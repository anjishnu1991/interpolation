############# MACROS ##############

RC     := root-config
ifeq ($(shell which $(RC) 2>&1 | sed -ne "s@.*/$(RC)@$(RC)@p"),$(RC))
MKARCH := $(wildcard $(shell $(RC) --etcdir)/Makefile.arch)
endif
ifneq ($(MKARCH),)
include $(MKARCH)
else
ROOTSYS = ../..
include $(ROOTSYS)/etc/Makefile.arch
endif

DICT      := RooFisherDict.$(SrcSuf)
DICTH     := $(DICT:.$(SrcSuf)=.h)
DICTO     := $(DICT:.$(SrcSuf)=.$(ObjSuf))

SRCS      := $(wildcard *.$(SrcSuf))
HDRS      := $(SRCS:.$(SrcSuf)=.h) LinkDef.h
HDRS      := $(filter-out $(DICTH),$(HDRS))
INC       := /home/anjishnu/interpolation/include/Eigen                                                                               
INCDIRS   := -I$(INC)
TARGETLIB := libRooFisher.$(DllSuf)
CFLAGS    := $(CXXFLAGS) $(INCDIRS)
OBJS      := $(SRCS:.$(SrcSuf)=.$(ObjSuf))

############# RULES ###############

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CFLAGS) -c $<

############# TARGETS #############

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) $(ExeSuf) .$(DllSuf)

all:    $(TARGETLIB)

$(DICT): $(HDRS)
	@echo "Generating dictionary $@..."
	rootcint  -f $@ -c  $^
	#$(ROOTCINT) -f $@ -c RooFitPythonWrapper.h LinkDef.h

$(TARGETLIB): $(OBJS) $(DICTO)
ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS)$@ $(LDFLAGS)  $^ $(OutPutOpt) $@ $(GLIBS) -lRooFit -lRooFitCore -lPython
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(GLIBS) $(OutPutOpt)$@
endif

distclean: clean
	@rm -f $(TARGETLIB) $(DICT) $(DICTH)

clean:
	@rm -f $(OBJS) $(DICTO)
	@rm RooFisherDict.cxx RooFisherDict.h libRooFisher.so 

