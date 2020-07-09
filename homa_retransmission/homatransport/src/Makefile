#
# OMNeT++/OMNEST Makefile for homatransport
#
# This file was generated with the command:
#  opp_makemake -f --deep -X dcntopo/results -I../../inet/src -L../../inet/out/$(CONFIGNAME)/src -lINET -DTESTING=$(TESTING) -KTESTING=0 -DINET_IMPORT -KINET_PROJ=../../inet
#

# Name of target to be created (-o option)
TARGET = homatransport$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inet/src \
    -I. \
    -Iapplication \
    -Icommon \
    -Idcntopo \
    -Imocks \
    -Itransport

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inet/out/$(CONFIGNAME)/src  -lINET
LIBS += -Wl,-rpath,`abspath ../../inet/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = /src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/application/MsgSizeDistributions.o \
    $O/application/WorkloadSynthesizer.o \
    $O/common/GlobalSignalListener.o \
    $O/common/Lagger.o \
    $O/common/Util.o \
    $O/mocks/MockUdpSocket.o \
    $O/transport/HomaConfigDepot.o \
    $O/transport/HomaPkt.o \
    $O/transport/HomaTransport.o \
    $O/transport/PriorityResolver.o \
    $O/transport/PseudoIdealPriorityTransport.o \
    $O/transport/UnschedByteAllocator.o \
    $O/transport/WorkloadEstimator.o \
    $O/application/AppMessage_m.o \
    $O/transport/HomaPkt_m.o

# Message files
MSGFILES = \
    application/AppMessage.msg \
    transport/HomaPkt.msg

# Other makefile variables (-K)
TESTING=0
INET_PROJ=../../inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DTESTING=$(TESTING) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f homatransport homatransport.exe libhomatransport.so libhomatransport.a libhomatransport.dll libhomatransport.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f application/*_m.cc application/*_m.h
	$(Q)-rm -f common/*_m.cc common/*_m.h
	$(Q)-rm -f dcntopo/*_m.cc dcntopo/*_m.h
	$(Q)-rm -f mocks/*_m.cc mocks/*_m.h
	$(Q)-rm -f transport/*_m.cc transport/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc application/*.cc common/*.cc dcntopo/*.cc mocks/*.cc transport/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/application/AppMessage_m.o: application/AppMessage_m.cc \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/common/INETDefs.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/common/InitStages.h \
  application/AppMessage_m.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h
$O/application/MsgSizeDistributions.o: application/MsgSizeDistributions.cc \
  ./common/Minimal.h \
  application/MsgSizeDistributions.h
$O/application/WorkloadSynthesizer.o: application/WorkloadSynthesizer.cc \
  application/WorkloadSynthesizer.h \
  ./common/Minimal.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ./transport/HomaPkt.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ../../inet/src/inet/networklayer/common/IInterfaceTable.h \
  ../../inet/src/inet/common/NotifierConsts.h \
  ../../inet/src/inet/networklayer/common/InterfaceToken.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ./application/MsgSizeDistributions.h \
  ../../inet/src/inet/common/INETDefs.h \
  ../../inet/src/inet/networklayer/common/L3AddressResolver.h \
  ../../inet/src/inet/common/lifecycle/ILifecycle.h \
  ../../inet/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/common/InitStages.h \
  ../../inet/src/inet/networklayer/common/InterfaceTable.h \
  ../../inet/src/inet/networklayer/common/InterfaceEntry.h \
  ./application/AppMessage_m.h
$O/common/GlobalSignalListener.o: common/GlobalSignalListener.cc \
  ./application/WorkloadSynthesizer.h \
  ./common/Minimal.h \
  ./transport/WorkloadEstimator.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPSocket.h \
  ./transport/HomaPkt.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./common/Util.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/common/IInterfaceTable.h \
  ../../inet/src/inet/common/NotifierConsts.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ./transport/HomaTransport.h \
  ../../inet/src/inet/networklayer/common/InterfaceToken.h \
  ./application/MsgSizeDistributions.h \
  ../../inet/src/inet/common/INETDefs.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  common/GlobalSignalListener.h \
  ./mocks/MockUdpSocket.h \
  ../../inet/src/inet/common/Compat.h \
  ./transport/UnschedByteAllocator.h \
  ../../inet/src/inet/common/InitStages.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
  ./application/AppMessage_m.h \
  ../../inet/src/inet/networklayer/common/InterfaceEntry.h
$O/common/Lagger.o: common/Lagger.cc \
  common/Lagger.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ./common/Minimal.h \
  ../../inet/src/inet/linklayer/common/MACBase.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/linklayer/ethernet/Ethernet.h \
  ../../inet/src/inet/common/InitStages.h \
  ../../inet/src/inet/common/lifecycle/NodeStatus.h \
  ../../inet/src/inet/linklayer/ethernet/EtherMACBase.h \
  ../../inet/src/inet/common/lifecycle/ILifecycle.h \
  ../../inet/src/inet/common/queue/IPassiveQueue.h \
  ../../inet/src/inet/common/INETDefs.h
$O/common/Util.o: common/Util.cc \
  ../../inet/src/inet/networklayer/common/InterfaceEntry.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
  ./application/AppMessage_m.h \
  ./transport/UnschedByteAllocator.h \
  ../../inet/src/inet/common/InitStages.h \
  ../../inet/src/inet/common/Compat.h \
  ./mocks/MockUdpSocket.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/common/INETDefs.h \
  ../../inet/src/inet/networklayer/common/InterfaceToken.h \
  ./transport/HomaTransport.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
  ../../inet/src/inet/common/NotifierConsts.h \
  ../../inet/src/inet/networklayer/common/IInterfaceTable.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ./common/Util.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./transport/HomaPkt.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPSocket.h \
  common/Util.h \
  ./transport/WorkloadEstimator.h \
  ./common/Minimal.h
$O/mocks/MockUdpSocket.o: mocks/MockUdpSocket.cc \
  mocks/MockUdpSocket.h \
  ./common/Minimal.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./transport/HomaPkt.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/common/INETDefs.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/common/InitStages.h
$O/transport/HomaConfigDepot.o: transport/HomaConfigDepot.cc \
  ./common/Minimal.h \
  transport/HomaConfigDepot.h
$O/transport/HomaPkt.o: transport/HomaPkt.cc \
  ../../inet/src/inet/common/INETDefs.h \
  transport/HomaPkt.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ./transport/HomaTransport.h \
  ../../inet/src/inet/networklayer/common/InterfaceToken.h \
  ./mocks/MockUdpSocket.h \
  ../../inet/src/inet/common/Compat.h \
  ./transport/UnschedByteAllocator.h \
  ../../inet/src/inet/common/InitStages.h \
  ./application/AppMessage_m.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
  ../../inet/src/inet/networklayer/common/InterfaceEntry.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPSocket.h \
  ./common/Minimal.h \
  ./transport/WorkloadEstimator.h \
  ../../inet/src/inet/networklayer/common/IInterfaceTable.h \
  ../../inet/src/inet/common/NotifierConsts.h \
  ./transport/HomaPkt.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./common/Util.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h
$O/transport/HomaPkt_m.o: transport/HomaPkt_m.cc \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/common/InitStages.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/common/INETDefs.h
$O/transport/HomaTransport.o: transport/HomaTransport.cc \
  ../../inet/src/inet/common/INETDefs.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
  ../../inet/src/inet/networklayer/common/InterfaceToken.h \
  ./transport/HomaTransport.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/common/InitStages.h \
  ./transport/UnschedByteAllocator.h \
  ../../inet/src/inet/common/Compat.h \
  ./mocks/MockUdpSocket.h \
  ../../inet/src/inet/networklayer/common/InterfaceEntry.h \
  ./application/AppMessage_m.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPSocket.h \
  ./transport/PriorityResolver.h \
  transport/HomaTransport.h \
  ./common/Minimal.h \
  ./transport/WorkloadEstimator.h \
  ../../inet/src/inet/networklayer/common/IInterfaceTable.h \
  ../../inet/src/inet/common/NotifierConsts.h \
  ./common/Util.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./transport/HomaPkt.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h
$O/transport/PriorityResolver.o: transport/PriorityResolver.cc \
  ../../inet/src/inet/common/INETDefs.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/networklayer/common/InterfaceToken.h \
  ./transport/HomaTransport.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
  ./application/AppMessage_m.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
  ../../inet/src/inet/networklayer/common/InterfaceEntry.h \
  ./mocks/MockUdpSocket.h \
  ./transport/UnschedByteAllocator.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/common/InitStages.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPSocket.h \
  transport/PriorityResolver.h \
  ./transport/WorkloadEstimator.h \
  ./common/Minimal.h \
  ../../inet/src/inet/common/NotifierConsts.h \
  ../../inet/src/inet/networklayer/common/IInterfaceTable.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./transport/HomaPkt.h \
  ./common/Util.h
$O/transport/PseudoIdealPriorityTransport.o: transport/PseudoIdealPriorityTransport.cc \
  ./common/Minimal.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPSocket.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./transport/HomaPkt.h \
  transport/PseudoIdealPriorityTransport.h \
  ../../inet/src/inet/common/NotifierConsts.h \
  ../../inet/src/inet/networklayer/common/IInterfaceTable.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/networklayer/common/InterfaceToken.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
  ../../inet/src/inet/common/INETDefs.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
  ./application/AppMessage_m.h \
  ../../inet/src/inet/networklayer/common/InterfaceEntry.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/common/InitStages.h
$O/transport/UnschedByteAllocator.o: transport/UnschedByteAllocator.cc \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  ../../inet/src/inet/common/InitStages.h \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ../../inet/src/inet/common/INETDefs.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ./transport/HomaPkt.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ./common/Minimal.h \
  transport/UnschedByteAllocator.h \
  ../../inet/src/inet/networklayer/common/L3Address.h
$O/transport/WorkloadEstimator.o: transport/WorkloadEstimator.cc \
  ../../inet/src/inet/common/Compat.h \
  ../../inet/src/inet/common/InitStages.h \
  ./transport/HomaConfigDepot.h \
  ../../inet/src/inet/networklayer/common/ModuleIdAddress.h \
  transport/WorkloadEstimator.h \
  ../../inet/src/inet/common/INETDefs.h \
  ../../inet/src/inet/networklayer/contract/ipv6/IPv6Address.h \
  ./transport/HomaPkt_m.h \
  ../../inet/src/inet/networklayer/contract/ipv4/IPv4Address.h \
  ../../inet/src/inet/linklayer/common/MACAddress.h \
  ./transport/HomaPkt.h \
  ../../inet/src/inet/networklayer/common/ModulePathAddress.h \
  ../../inet/src/inet/networklayer/common/L3Address.h \
  ./common/Minimal.h
