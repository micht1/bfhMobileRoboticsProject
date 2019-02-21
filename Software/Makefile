# Yello Makefile
#
# Maintainer: gabriel.gruener@bfh.ch
#
# This file is based on the auto-generated Makefile from mbed.org.

###############################################################################
# Project settings
#
# Modify this to match project and settings

# This is the name given to the main executable file 
PROJECT := Yellow

# Path to the top directory with our C++ sources
SRC_DIR := src/ch/bfh/roboticsLab

# Path to folder where to compile and place executable file 
OBJ_DIR := build

# Path to local cross compiler
ifeq ($(shell echo $$OS),$$OS)
	# Windows 
	CROSS_COMPILER_PATH = 'C:\GNU\arm\2018-q4-major\bin'
else
	# MacOS / Linux
	CROSS_COMPILER_PATH = '/opt/arm/gcc-arm-none-eabi-8-2018-q4-major/bin/'
endif

# Project settings
###############################################################################


###
### No user-configurable options below: Please don't modify unless you know what you are doing
###


###############################################################################
# Boiler-plate

# cross-platform directory manipulation
ifeq ($(shell echo $$OS),$$OS)
    MAKEDIR = if not exist "$(1)" mkdir "$(1)"
    RM = rmdir /S /Q "$(1)"
else
    MAKEDIR = '$(SHELL)' -c "mkdir -p \"$(1)\""
    RM = '$(SHELL)' -c "rm -rf \"$(1)\""
endif

OBJDIR := $(OBJ_DIR)

# Move to the build directory
ifeq (,$(filter $(OBJDIR),$(notdir $(CURDIR))))
.SUFFIXES:
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKETARGET = '$(MAKE)' --no-print-directory -C $(OBJDIR) -f '$(mkfile_path)' 'SRCDIR=$(CURDIR)' $(MAKECMDGOALS)
.PHONY: $(OBJDIR) clean very-clean

# Default target 'all': builds everything
all:
	+@$(call MAKEDIR,$(OBJDIR))
	+@$(MAKETARGET)
$(OBJDIR): all
Makefile : ;
% :: $(OBJDIR) ; :

# 'very-clean' target: removes the 'build' directory 
very-clean :
	$(call RM,$(OBJDIR))

# 'clean' target: cleans only yellow-specific object files
clean:
	+@$(MAKETARGET)

else

# trick rules into thinking we are in the root, when we are in the bulid dir
VPATH = ..

# Boiler-plate
###############################################################################


###############################################################################
# Objects and Paths

# Stop GNU compiler from warning about mbed-os usage of defined in pre-compiler
CXX_FLAGS += -Wno-expansion-to-defined
# Stop GNU compiler from reporting depecrated declarations (TODO fix RealtimeThread usage of thread->signal_wait)
CXX_FLAGS += -Wno-deprecated-declarations
# Stop compiler from warning gcc pre 7.1 compatibility 
CXX_FLAGS += -Wno-psabi

# Recursive wildcard search
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Our C++ objects to be compiled
MY_CPP_SRCS := $(call rwildcard,$(SRCDIR)/$(SRC_DIR)/,*.cpp)
MY_CPP_OBJS := $(MY_CPP_SRCS:$(SRCDIR)/%.cpp=%.o)
OBJECTS += $(MY_CPP_OBJS)
MY_C_SRCS := $(call rwildcard,$(SRCDIR)/$(SRC_DIR)/,*.c)
MY_C_OBJS := $(MY_C_SRCS:$(SRCDIR)/%.c=%.o)
OBJECTS += $(MY_C_OBJS)

##  External libraries 
# Nano protobufs lib
NANOPB_SRC_DIR := src/fi
NANOPB_SRCS := $(call rwildcard,$(SRCDIR)/$(NANOPB_SRC_DIR)/,*.c)
NANOPB_C_OBJS := $(NANOPB_SRCS:$(SRCDIR)/%.c=%.o)
OBJECTS += $(NANOPB_C_OBJS)

# mbed-os: this list was automatically generated from the mbde-os web project
OBJECTS += src/com/mbed/mbed-os/cmsis/TARGET_CORTEX_M/TOOLCHAIN_GCC/except.o
OBJECTS += src/com/mbed/mbed-os/cmsis/TARGET_CORTEX_M/mbed_fault_handler.o
OBJECTS += src/com/mbed/mbed-os/cmsis/TARGET_CORTEX_M/mbed_tz_context.o
OBJECTS += src/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver/source/NanostackRfPhyAtmel.o
OBJECTS += src/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver/source/at24mac.o
OBJECTS += src/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver/source/MCR20Drv.o
OBJECTS += src/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver/source/NanostackRfPhyMcr20a.o
OBJECTS += src/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver/source/NanostackRfPhys2lp.o
OBJECTS += src/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver/source/rf_configuration.o
OBJECTS += src/com/mbed/mbed-os/components/wifi/esp8266-driver/ESP8266/ESP8266.o
OBJECTS += src/com/mbed/mbed-os/components/wifi/esp8266-driver/ESP8266Interface.o
OBJECTS += src/com/mbed/mbed-os/drivers/AnalogIn.o
OBJECTS += src/com/mbed/mbed-os/drivers/BusIn.o
OBJECTS += src/com/mbed/mbed-os/drivers/BusInOut.o
OBJECTS += src/com/mbed/mbed-os/drivers/BusOut.o
OBJECTS += src/com/mbed/mbed-os/drivers/CAN.o
OBJECTS += src/com/mbed/mbed-os/drivers/Ethernet.o
OBJECTS += src/com/mbed/mbed-os/drivers/FlashIAP.o
OBJECTS += src/com/mbed/mbed-os/drivers/I2C.o
OBJECTS += src/com/mbed/mbed-os/drivers/I2CSlave.o
OBJECTS += src/com/mbed/mbed-os/drivers/InterruptIn.o
OBJECTS += src/com/mbed/mbed-os/drivers/InterruptManager.o
OBJECTS += src/com/mbed/mbed-os/drivers/MbedCRC.o
OBJECTS += src/com/mbed/mbed-os/drivers/QSPI.o
OBJECTS += src/com/mbed/mbed-os/drivers/RawSerial.o
OBJECTS += src/com/mbed/mbed-os/drivers/SPI.o
OBJECTS += src/com/mbed/mbed-os/drivers/SPISlave.o
OBJECTS += src/com/mbed/mbed-os/drivers/Serial.o
OBJECTS += src/com/mbed/mbed-os/drivers/SerialBase.o
OBJECTS += src/com/mbed/mbed-os/drivers/TableCRC.o
OBJECTS += src/com/mbed/mbed-os/drivers/Ticker.o
OBJECTS += src/com/mbed/mbed-os/drivers/Timeout.o
OBJECTS += src/com/mbed/mbed-os/drivers/Timer.o
OBJECTS += src/com/mbed/mbed-os/drivers/TimerEvent.o
OBJECTS += src/com/mbed/mbed-os/drivers/UARTSerial.o
OBJECTS += src/com/mbed/mbed-os/events/EventQueue.o
OBJECTS += src/com/mbed/mbed-os/events/equeue/equeue.o
OBJECTS += src/com/mbed/mbed-os/events/equeue/equeue_mbed.o
OBJECTS += src/com/mbed/mbed-os/events/equeue/equeue_posix.o
OBJECTS += src/com/mbed/mbed-os/events/mbed_shared_queues.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/ATHandler.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/ATHandler_factory.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularBase.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularDevice.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularInformation.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularSIM.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularSMS.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/AT/AT_CellularStack.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/common/CellularLog.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/common/CellularUtil.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/device/CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/device/CellularDevice.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/device/CellularStateMachine.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO/CINTERION/GEMALTO_CINTERION.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO/CINTERION/GEMALTO_CINTERION_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO/CINTERION/GEMALTO_CINTERION_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO/CINTERION/GEMALTO_CINTERION_CellularStack.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano/PPP/SARA4_PPP.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano/PPP/SARA4_PPP_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano/PPP/SARA4_PPP_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano/PPP/SARA4_PPP_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95/QUECTEL_BC95.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95/QUECTEL_BC95_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95/QUECTEL_BC95_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95/QUECTEL_BC95_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95/QUECTEL_BC95_CellularSIM.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95/QUECTEL_BC95_CellularStack.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96/QUECTEL_BG96.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96/QUECTEL_BG96_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96/QUECTEL_BG96_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96/QUECTEL_BG96_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96/QUECTEL_BG96_CellularSIM.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96/QUECTEL_BG96_CellularStack.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26/QUECTEL_M26.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26/QUECTEL_M26_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26/QUECTEL_M26_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26/QUECTEL_M26_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26/QUECTEL_M26_CellularSIM.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26/QUECTEL_M26_CellularStack.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/UG96/QUECTEL_UG96.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/UG96/QUECTEL_UG96_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/UG96/QUECTEL_UG96_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/UG96/QUECTEL_UG96_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/TELIT/HE910/TELIT_HE910.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/TELIT/HE910/TELIT_HE910_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/TELIT/HE910/TELIT_HE910_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/TELIT/HE910/TELIT_HE910_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/AT/UBLOX_AT.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/AT/UBLOX_AT_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/AT/UBLOX_AT_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/AT/UBLOX_AT_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/AT/UBLOX_AT_CellularStack.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/PPP/UBLOX_PPP.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/PPP/UBLOX_PPP_CellularContext.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/PPP/UBLOX_PPP_CellularNetwork.o
OBJECTS += src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/PPP/UBLOX_PPP_CellularPower.o
OBJECTS += src/com/mbed/mbed-os/features/device_key/source/DeviceKey.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/greentea-client/source/greentea_metrics.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/greentea-client/source/greentea_serial.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/greentea-client/source/greentea_test_env.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/mbed-client-cli/source/ns_cmdline.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/mbed-client-randlib/source/randLIB.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/mbed-coap/source/sn_coap_builder.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/mbed-coap/source/sn_coap_header_check.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/mbed-coap/source/sn_coap_parser.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/mbed-coap/source/sn_coap_protocol.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/mbed-trace/source/mbed_trace.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/IPv6_fcf_lib/ip_fsc.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/libBits/common_functions.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/libList/ns_list.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/libip4string/ip4tos.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/libip4string/stoip4.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/libip6string/ip6tos.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/libip6string/stoip6.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/nsdynmemLIB/nsdynmemLIB.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/source/nvmHelper/ns_nvm_helper.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/unity/source/unity.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/mbed-utest-shim.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/unity_handler.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/utest_case.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/utest_default_handlers.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/utest_greentea_handlers.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/utest_harness.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/utest_shim.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/utest_stack_trace.o
OBJECTS += src/com/mbed/mbed-os/features/frameworks/utest/source/utest_types.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/LoRaWANInterface.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/LoRaWANStack.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/mac/LoRaMac.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/mac/LoRaMacChannelPlan.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/mac/LoRaMacCommand.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/mac/LoRaMacCrypto.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHY.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYAS923.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYAU915.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYCN470.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYCN779.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYEU433.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYEU868.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYIN865.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYKR920.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/lorastack/phy/LoRaPHYUS915.o
OBJECTS += src/com/mbed/mbed-os/features/lorawan/system/LoRaWANTimer.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/LWIPInterface.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/LWIPInterfaceEMAC.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/LWIPInterfaceL3IP.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/LWIPMemoryManager.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/LWIPStack.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip-sys/arch/lwip_checksum.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip-sys/arch/lwip_memcpy.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip-sys/arch/lwip_sys_arch.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip-sys/lwip_random.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip-sys/lwip_tcp_isn.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_api_lib.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_api_msg.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_err.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_netbuf.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_netdb.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_netifapi.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_sockets.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/api/lwip_tcpip.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_autoip.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_dhcp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_etharp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_icmp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_igmp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_ip4.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_ip4_addr.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv4/lwip_ip4_frag.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_dhcp6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_ethip6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_icmp6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_inet6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_ip6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_ip6_addr.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_ip6_frag.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_mld6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/ipv6/lwip_nd6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_def.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_dns.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_inet_chksum.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_init.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_ip.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_mem.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_memp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_netif.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_pbuf.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_raw.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_stats.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_sys.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_tcp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_tcp_in.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_tcp_out.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_timeouts.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/core/lwip_udp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/lwip_ethernet.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/lwip_ethernetif.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/lwip_lowpan6.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_auth.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_ccp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_chap-md5.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_chap-new.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_chap_ms.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_demand.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_eap.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_ecp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_eui64.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_fsm.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_ipcp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_ipv6cp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_lcp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_magic.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_mppe.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_multilink.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_ppp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_pppapi.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_pppcrypt.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_pppoe.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_pppol2tp.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_pppos.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_upap.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_utils.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/lwip_vj.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/polarssl/lwip_arc4.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/polarssl/lwip_des.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/polarssl/lwip_md4.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/polarssl/lwip_md5.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip/src/netif/ppp/polarssl/lwip_sha1.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/lwip_tools.o
OBJECTS += src/com/mbed/mbed-os/features/lwipstack/ppp_lwip.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/platform/src/mbed_trng.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/platform/src/platform_alt.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/aes.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/aesni.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/arc4.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/aria.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/asn1parse.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/asn1write.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/base64.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/bignum.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/blowfish.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/camellia.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ccm.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/certs.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/chacha20.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/chachapoly.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/cipher.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/cipher_wrap.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/cmac.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ctr_drbg.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/debug.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/des.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/dhm.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ecdh.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ecdsa.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ecjpake.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ecp.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ecp_curves.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/entropy.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/entropy_poll.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/error.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/gcm.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/havege.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/hkdf.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/hmac_drbg.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/md.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/md2.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/md4.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/md5.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/md_wrap.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/memory_buffer_alloc.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/net_sockets.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/nist_kw.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/oid.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/padlock.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pem.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pk.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pk_wrap.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pkcs11.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pkcs12.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pkcs5.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pkparse.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/pkwrite.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/platform.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/platform_util.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/poly1305.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ripemd160.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/rsa.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/rsa_internal.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/sha1.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/sha256.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/sha512.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ssl_cache.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ssl_ciphersuites.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ssl_cli.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ssl_cookie.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ssl_srv.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ssl_ticket.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/ssl_tls.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/threading.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/timing.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/version.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/version_features.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/x509.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/x509_create.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/x509_crl.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/x509_crt.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/x509_csr.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/x509write_crt.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/x509write_csr.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/src/xtea.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/targets/TARGET_STM/aes_alt.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/targets/TARGET_STM/md5_alt.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/targets/TARGET_STM/sha1_alt.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/targets/TARGET_STM/sha256_alt.o
OBJECTS += src/com/mbed/mbed-os/features/mbedtls/targets/hash_wrappers.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/coap-service/source/coap_connection_handler.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/coap-service/source/coap_message_handler.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/coap-service/source/coap_security_handler.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/coap-service/source/coap_service_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/CallbackHandler.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/LoWPANNDInterface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/MeshInterfaceNanostack.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/NanostackEMACInterface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/NanostackEthernetInterface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/NanostackMemoryManager.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/ThreadInterface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/WisunInterface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/ethernet_tasklet.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/mesh_system.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/nd_tasklet.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/thread_tasklet.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/wisun_tasklet.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/arm_hal_fhss_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/arm_hal_interrupt.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/arm_hal_random.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/arm_hal_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/cs_nvm/cs_nvm.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/ns_event_loop.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/ns_event_loop_mbed.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/ns_event_loop_mutex.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/ns_hal_init.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos/nvm/nvm_ram.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/nanostack-interface/Nanostack.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/source/event.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/source/minar_hal_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/source/ns_timeout.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/source/ns_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/source/system_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Bootstraps/Generic/network_lib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Bootstraps/Generic/protocol_6lowpan.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Bootstraps/Generic/protocol_6lowpan_bootstrap.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Bootstraps/Generic/protocol_6lowpan_interface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Fragmentation/cipv6_fragmenter.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/IPHC_Decode/6lowpan_iphc.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/IPHC_Decode/iphc_compress.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/IPHC_Decode/iphc_decompress.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/IPHC_Decode/lowpan_context.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC/beacon_handler.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC/mac_data_poll.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC/mac_helper.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC/mac_ie_lib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC/mac_pairwise_key.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC/mac_response_handler.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Mesh/mesh.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/ND/nd_router_object.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/NVM/nwk_nvm.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_bbr_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_beacon.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_bootstrap.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_border_router_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_commissioning_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_commissioning_if.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_common.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_dhcpv6_server.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_diagnostic.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_discovery.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_host_bootstrap.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_joiner_application.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_leader_service.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_lowpower_private_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_management_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_management_client.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_management_if.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_management_server.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_mdns.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_meshcop_lib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_mle_message_handler.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_nd.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_neighbor_class.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_net_config_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_network_data_lib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_network_data_storage.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_network_synch.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_nvm_store.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_resolution_client.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_resolution_server.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_router_bootstrap.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_routing.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread/thread_test_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/adaptation_interface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/ws/ws_empty_functions.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/BorderRouter/border_router.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/icmpv6.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/icmpv6_prefix.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/icmpv6_radv.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/ipv6.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/ipv6_flow.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/ipv6_fragmentation.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/ipv6_resolution.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/mld.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/tcp.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols/udp.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core/address.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core/buffer_dyn.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core/ns_socket.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core/sockbuf.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/DHCPv6_Server/DHCPv6_Server_service.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/DHCPv6_client/dhcpv6_client_service.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_fhss_callbacks.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_filter.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_header_helper_functions.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_indirect_data.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_mcps_sap.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_mlme.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_pd_sap.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_security_mib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/mac_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4/sw_mac.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/ethernet/ethernet_mac_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/rf_driver_storage.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/serial/serial_mac_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/virtual_rf/virtual_rf_client.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/virtual_rf/virtual_rf_driver.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MLE/mle.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MLE/mle_tlv.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MPL/mpl.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE/protocol_core.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE/protocol_core_sleep.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE/protocol_stats.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE/protocol_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_control.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_data.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_downward.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_mrhof.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_objective.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_of0.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_policy.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL/rpl_upward.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/Common/security_lib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/eap_protocol.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/pana.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/pana_avp.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/pana_client.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/pana_eap_header.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/pana_header.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/pana_relay_table.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA/pana_server.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/TLS/tls_ccm_crypt.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/TLS/tls_lib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/CCM_lib/ccm_security.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/CCM_lib/mbedOS/aes_mbedtls_adapter.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/Neighbor_cache/neighbor_cache.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/SHA256_Lib/ns_sha256.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/SHA256_Lib/shalib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/Trickle/trickle.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/blacklist/blacklist.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/etx/etx.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss/channel_list.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss/fhss.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss/fhss_channel.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss/fhss_common.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss/fhss_configuration_interface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss/fhss_statistics.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss/fhss_ws_empty_functions.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fnv_hash/fnv_hash.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/load_balance/load_balance.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mac_neighbor_table/mac_neighbor_table.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/mdns/fnet_mdns.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/poll/fnet_poll.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/stack/fnet_stdlib.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/ns_fnet_events.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/ns_fnet_port.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/ns_mdns_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mle_service/mle_service.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mle_service/mle_service_buffer.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mle_service/mle_service_frame_counter_table.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mle_service/mle_service_interface.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mle_service/mle_service_security.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/nd_proxy/nd_proxy.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/pan_blacklist/pan_blacklist.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/utils/isqrt.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/utils/ns_crc.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/utils/ns_file_system.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/whiteboard/whiteboard.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/ipv6_stack/ipv6_routing_table.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/ipv6_stack/protocol_ipv6.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libDHCPv6/dhcp_service_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libDHCPv6/libDHCPv6.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libDHCPv6/libDHCPv6_server.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/multicast_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/net_6lowpan_parameter_api.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/net_ipv6.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/net_load_balance.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/net_mle.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/net_rpl.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/net_short_address_extension.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/net_test.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/ns_net.o
OBJECTS += src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src/socket_api.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/DTLSSocket.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/DTLSSocketWrapper.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/EMACInterface.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/EthernetInterface.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/InternetSocket.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/L3IPInterface.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/NetStackMemoryManager.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/NetworkInterface.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/NetworkInterfaceDefaults.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/NetworkStack.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/SocketAddress.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/SocketStats.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/TCPServer.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/TCPSocket.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/TLSSocket.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/TLSSocketWrapper.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/UDPSocket.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/WiFiAccessPoint.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/cellular/generic_modem_driver/OnboardCellularInterface.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/cellular/generic_modem_driver/PPPCellularInterface.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/cellular/generic_modem_driver/UARTCellularInterface.o
OBJECTS += src/com/mbed/mbed-os/features/netsocket/nsapi_dns.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/acore/source/ac_buffer.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/acore/source/ac_buffer_builder.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/acore/source/ac_buffer_reader.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/acore/source/ac_stream.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/controllers/PN512Driver.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/controllers/PN512SPITransportDriver.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/controllers/PN512TransportDriver.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCController.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCControllerDriver.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCEEPROM.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCEEPROMDriver.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCNDEFCapable.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCRemoteEndpoint.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCRemoteInitiator.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/NFCTarget.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/Type4RemoteInitiator.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/MessageBuilder.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/MessageParser.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/RecordParser.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/common/Mime.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/common/SimpleMessageParser.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/common/Text.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/common/URI.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/source/nfc/ndef/common/util.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/ndef/ndef.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/platform/nfc_scheduler.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/platform/nfc_transport.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/tech/iso7816/iso7816.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/tech/iso7816/iso7816_app.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/tech/isodep/isodep_target.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/tech/type4/type4_target.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_cmd.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_hw.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_irq.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_poll.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_registers.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_rf.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_timer.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512/pn512_transceive.o
OBJECTS += src/com/mbed/mbed-os/features/nfc/stack/transceiver/transceiver.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/BufferedBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/ChainingBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/ExhaustibleBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/FlashSimBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/HeapBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/MBRBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/ObservingBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/ProfilingBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/ReadOnlyBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/blockdevice/SlicingBlockDevice.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/Dir.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/File.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/FileSystem.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/fat/ChaN/ff.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/fat/ChaN/ffunicode.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/fat/FATFileSystem.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/littlefs/LittleFileSystem.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/littlefs/littlefs/lfs.o
OBJECTS += src/com/mbed/mbed-os/features/storage/filesystem/littlefs/littlefs/lfs_util.o
OBJECTS += src/com/mbed/mbed-os/features/storage/kvstore/conf/kv_config.o
OBJECTS += src/com/mbed/mbed-os/features/storage/kvstore/direct_access_devicekey/DirectAccessDevicekey.o
OBJECTS += src/com/mbed/mbed-os/features/storage/kvstore/filesystemstore/FileSystemStore.o
OBJECTS += src/com/mbed/mbed-os/features/storage/kvstore/global_api/kvstore_global_api.o
OBJECTS += src/com/mbed/mbed-os/features/storage/kvstore/kv_map/KVMap.o
OBJECTS += src/com/mbed/mbed-os/features/storage/kvstore/securestore/SecureStore.o
OBJECTS += src/com/mbed/mbed-os/features/storage/kvstore/tdbstore/TDBStore.o
OBJECTS += src/com/mbed/mbed-os/features/storage/nvstore/source/nvstore.o
OBJECTS += src/com/mbed/mbed-os/features/storage/system_storage/SystemStorage.o
OBJECTS += src/com/mbed/mbed-os/hal/LowPowerTickerWrapper.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_critical_section_api.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_flash_api.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_gpio.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_itm_api.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_lp_ticker_api.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_lp_ticker_wrapper.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_pinmap_common.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_ticker_api.o
OBJECTS += src/com/mbed/mbed-os/hal/mbed_us_ticker_api.o
OBJECTS += src/com/mbed/mbed-os/hal/mpu/mbed_mpu_v7m.o
OBJECTS += src/com/mbed/mbed-os/hal/mpu/mbed_mpu_v8m.o
OBJECTS += src/com/mbed/mbed-os/platform/ATCmdParser.o
OBJECTS += src/com/mbed/mbed-os/platform/CThunkBase.o
OBJECTS += src/com/mbed/mbed-os/platform/CallChain.o
OBJECTS += src/com/mbed/mbed-os/platform/FileBase.o
OBJECTS += src/com/mbed/mbed-os/platform/FileHandle.o
OBJECTS += src/com/mbed/mbed-os/platform/FilePath.o
OBJECTS += src/com/mbed/mbed-os/platform/FileSystemHandle.o
OBJECTS += src/com/mbed/mbed-os/platform/LocalFileSystem.o
OBJECTS += src/com/mbed/mbed-os/platform/Stream.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_alloc_wrappers.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_application.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_assert.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_board.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_critical.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_error.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_error_hist.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_interface.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_mem_trace.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_mktime.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_mpu_mgmt.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_poll.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_retarget.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_rtc_time.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_sdk_boot.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_semihost_api.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_sleep_manager.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_stats.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_wait_api_no_rtos.o
OBJECTS += src/com/mbed/mbed-os/platform/mbed_wait_api_rtos.o
OBJECTS += src/com/mbed/mbed-os/rtos/ConditionVariable.o
OBJECTS += src/com/mbed/mbed-os/rtos/EventFlags.o
OBJECTS += src/com/mbed/mbed-os/rtos/Kernel.o
OBJECTS += src/com/mbed/mbed-os/rtos/Mutex.o
OBJECTS += src/com/mbed/mbed-os/rtos/RtosTimer.o
OBJECTS += src/com/mbed/mbed-os/rtos/Semaphore.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/SysTimer.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/TOOLCHAIN_GCC_ARM/mbed_boot_gcc_arm.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/mbed_boot.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/mbed_rtos_rtx.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/mbed_rtx_handlers.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/mbed_rtx_idle.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx4/cmsis_os1.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Config/RTX_Config.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/TOOLCHAIN_GCC/TARGET_RTOS_M4_M7/irq_cm4f.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_delay.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_evflags.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_evr.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_kernel.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_lib.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_memory.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_mempool.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_msgqueue.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_mutex.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_semaphore.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_system.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_thread.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source/rtx_timer.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/Source/os_systick.o
OBJECTS += src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/Source/os_tick_ptim.o
OBJECTS += src/com/mbed/mbed-os/rtos/ThisThread.o
OBJECTS += src/com/mbed/mbed-os/rtos/Thread.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/TARGET_NUCLEO_F446RE/PeripheralPins.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/TARGET_NUCLEO_F446RE/system_clock.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/device/TOOLCHAIN_GCC_ARM/startup_stm32f446xx.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/analogin_device.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/analogout_device.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_adc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_adc_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_can.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_can_legacy.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_cec.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_cortex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_crc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_cryp.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_cryp_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dac.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dac_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dcmi.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dcmi_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dfsdm.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dma.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dma2d.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dma_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_dsi.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_eth.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_flash.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_flash_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_flash_ramfunc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_fmpi2c.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_fmpi2c_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_gpio.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_hash.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_hash_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_hcd.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_i2c.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_i2c_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_i2s.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_i2s_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_irda.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_iwdg.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_lptim.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_ltdc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_ltdc_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_mmc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_nand.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_nor.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_pccard.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_pcd.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_pcd_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_pwr.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_pwr_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_qspi.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_rcc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_rcc_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_rng.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_rtc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_rtc_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_sai.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_sai_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_sd.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_sdram.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_smartcard.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_spdifrx.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_spi.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_sram.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_tim.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_tim_ex.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_uart.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_usart.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_hal_wwdg.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_adc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_crc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_dac.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_dma.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_dma2d.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_exti.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_fmc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_fsmc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_gpio.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_i2c.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_lptim.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_pwr.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_rcc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_rng.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_rtc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_sdmmc.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_spi.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_tim.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_usart.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_usb.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/stm32f4xx_ll_utils.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device/system_stm32f4xx.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/flash_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/gpio_irq_device.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/pwmout_device.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/serial_device.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/spi_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/analogin_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/analogout_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/can_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/gpio_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/gpio_irq_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/hal_tick_overrides.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/i2c_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/lp_ticker.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/mbed_crc_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/mbed_overrides.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/pinmap.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/port_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/pwmout_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/qspi_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/rtc_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/serial_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/sleep.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/stm_spi_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/trng_api.o
OBJECTS += src/com/mbed/mbed-os/targets/TARGET_STM/us_ticker.o

INCLUDE_PATHS += -I../.
INCLUDE_PATHS += -I../src
INCLUDE_PATHS += -I../src/com
INCLUDE_PATHS += -I../src/com/mbed
INCLUDE_PATHS += -I../src/com/mbed/mbed-os
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/cmsis
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/cmsis/TARGET_CORTEX_M
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver/atmel-rf-driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver/mcr20a-rf-driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver/stm-s2lp-rf-driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/wifi
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/wifi/esp8266-driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/components/wifi/esp8266-driver/ESP8266
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/drivers
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/events
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/events/equeue
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/API
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/AT
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/common
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/device
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO/CINTERION
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano/PPP
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/UG96
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/TELIT
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/TELIT/HE910
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/AT
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/PPP
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/device_key
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/device_key/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/greentea-client
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/greentea-client/greentea-client
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-client-cli
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-client-cli/mbed-client-cli
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-client-randlib
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-client-randlib/mbed-client-randlib
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-client-randlib/mbed-client-randlib/platform
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-coap
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-coap/mbed-coap
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-coap/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-coap/source/include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-trace
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/mbed-trace/mbed-trace
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/nanostack-libservice
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/mbed-client-libservice
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/nanostack-libservice/mbed-client-libservice/platform
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/unity
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/unity/unity
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/utest
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/frameworks/utest/utest
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lorawan
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lorawan/lorastack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lorawan/lorastack/mac
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lorawan/lorastack/phy
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lorawan/system
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip-sys
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip-sys/arch
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src/include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src/include/lwip
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src/include/lwip/priv
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src/include/lwip/prot
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src/include/netif
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src/include/netif/ppp
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/lwipstack/lwip/src/include/netif/ppp/polarssl
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/mbedtls
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/mbedtls/inc
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/mbedtls/inc/mbedtls
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/mbedtls/inc/psa
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/mbedtls/platform
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/mbedtls/platform/inc
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/mbedtls/targets/TARGET_STM
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/coap-service
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/coap-service/coap-service
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/coap-service/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/coap-service/source/include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/mbed-mesh-api
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/nanostack-interface
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/nanostack-event-loop
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/nanostack-event-loop/platform
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/nanostack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/nanostack/platform
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Bootstraps
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Fragmentation
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/IPHC_Decode
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Mesh
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/ND
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/NVM
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/ws
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/BorderRouter
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core/include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/DHCPv6_Server
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/DHCPv6_client
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/virtual_rf
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MLE
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MPL
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE/Include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/Common
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/TLS
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/Neighbor_cache
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/Trickle
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/blacklist
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/etx
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fnv_hash
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/load_balance
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mac_neighbor_table
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/port
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/port/compiler
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/port/cpu
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/dns
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/mdns
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/poll
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/serial
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/stack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mle_service
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/nd_proxy
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/pan_blacklist
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/utils
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/whiteboard
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/configs
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/configs/base
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/ipv6_stack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libDHCPv6
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/netsocket
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/netsocket/cellular
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/netsocket/cellular/generic_modem_driver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/acore
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/acore/acore
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/controllers
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/nfc
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/nfc/ndef
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/nfc/ndef/common
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/ndef
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/platform
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/tech
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/tech/iso7816
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/tech/isodep
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/tech/type4
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/transceiver
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/blockdevice
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/filesystem
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/filesystem/fat
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/filesystem/fat/ChaN
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/filesystem/littlefs
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/filesystem/littlefs/littlefs
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/conf
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/direct_access_devicekey
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/filesystemstore
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/global_api
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/kv_map
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/securestore
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/kvstore/tdbstore
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/nvstore
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/nvstore/source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/features/storage/system_storage
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/hal
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/hal/storage_abstraction
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/platform
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx4
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/Include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Config
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Include
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/targets/TARGET_STM
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/TARGET_NUCLEO_F446RE
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/device
INCLUDE_PATHS += -I../src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device
INCLUDE_PATHS += -I../src

LIBRARY_PATHS :=
LIBRARIES :=
LINKER_SCRIPT ?= ../src/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/device/TOOLCHAIN_GCC_ARM/STM32F446XE.ld

# Objects and Paths
###############################################################################
# Tools and Flags

AS      = $(CROSS_COMPILER_PATH)/arm-none-eabi-gcc
CC      = $(CROSS_COMPILER_PATH)/arm-none-eabi-gcc
CPP     = $(CROSS_COMPILER_PATH)/arm-none-eabi-g++
LD      = $(CROSS_COMPILER_PATH)/arm-none-eabi-gcc
ELF2BIN = $(CROSS_COMPILER_PATH)/arm-none-eabi-objcopy
PREPROC = $(CROSS_COMPILER_PATH)/arm-none-eabi-cpp -E -P -Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_memalign_r -Wl,--wrap,_calloc_r -Wl,--wrap,exit -Wl,--wrap,atexit -Wl,-n -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp


C_FLAGS += -std=gnu99
C_FLAGS += -include
C_FLAGS += mbed_config.h
C_FLAGS += -DDEVICE_SPI=1
C_FLAGS += -D__MBED__=1
C_FLAGS += -DDEVICE_I2CSLAVE=1
C_FLAGS += -D__FPU_PRESENT=1
C_FLAGS += -DDEVICE_PORTOUT=1
C_FLAGS += -DUSBHOST_OTHER
C_FLAGS += -DMBED_BUILD_TIMESTAMP=1549297705.4
C_FLAGS += -DTARGET_RTOS_M4_M7
C_FLAGS += -DDEVICE_RTC=1
C_FLAGS += -DDEVICE_MPU=1
C_FLAGS += -DDEVICE_SERIAL_ASYNCH=1
C_FLAGS += -DTARGET_STM32F4
C_FLAGS += -D__CMSIS_RTOS
C_FLAGS += -DTARGET_STM32F446xE
C_FLAGS += -DTOOLCHAIN_GCC
C_FLAGS += -DDEVICE_I2C_ASYNCH=1
C_FLAGS += -DTARGET_CORTEX_M
C_FLAGS += -DTARGET_LIKE_CORTEX_M4
C_FLAGS += -DDEVICE_ANALOGOUT=1
C_FLAGS += -DTARGET_M4
C_FLAGS += -DCOMPONENT_PSA_SRV_IMPL=1
C_FLAGS += -DDEVICE_SPI_ASYNCH=1
C_FLAGS += -DDEVICE_LPTICKER=1
C_FLAGS += -DDEVICE_PWMOUT=1
C_FLAGS += -DDEVICE_INTERRUPTIN=1
C_FLAGS += -DTARGET_CORTEX
C_FLAGS += -DDEVICE_I2C=1
C_FLAGS += -DTRANSACTION_QUEUE_SIZE_SPI=2
C_FLAGS += -D__CORTEX_M4
C_FLAGS += -DDEVICE_STDIO_MESSAGES=1
C_FLAGS += -DTARGET_FF_MORPHO
C_FLAGS += -DTARGET_FAMILY_STM32
C_FLAGS += -DTARGET_FF_ARDUINO
C_FLAGS += -DTARGET_STM32F446RE
C_FLAGS += -DTARGET_RELEASE
C_FLAGS += -DTARGET_STM
C_FLAGS += -DDEVICE_SERIAL_FC=1
C_FLAGS += -DCOMPONENT_PSA_SRV_EMUL=1
C_FLAGS += -DDEVICE_USTICKER=1
C_FLAGS += -DDEVICE_PORTINOUT=1
C_FLAGS += -DTARGET_LIKE_MBED
C_FLAGS += -D__MBED_CMSIS_RTOS_CM
C_FLAGS += -DDEVICE_SLEEP=1
C_FLAGS += -DTOOLCHAIN_GCC_ARM
C_FLAGS += -DDEVICE_CAN=1
C_FLAGS += -DUSB_STM_HAL
C_FLAGS += -DCOMPONENT_NSPE=1
C_FLAGS += -DTARGET_NUCLEO_F446RE
C_FLAGS += -DDEVICE_SPISLAVE=1
C_FLAGS += -DDEVICE_ANALOGIN=1
C_FLAGS += -DDEVICE_SERIAL=1
C_FLAGS += -DDEVICE_FLASH=1
C_FLAGS += -DDEVICE_PORTIN=1
C_FLAGS += -DARM_MATH_CM4
C_FLAGS += -include
C_FLAGS += mbed_config.h
C_FLAGS += -std=gnu99
C_FLAGS += -c
C_FLAGS += -Wall
C_FLAGS += -Wextra
C_FLAGS += -Wno-unused-parameter
C_FLAGS += -Wno-missing-field-initializers
C_FLAGS += -fmessage-length=0
C_FLAGS += -fno-exceptions
C_FLAGS += -fno-builtin
C_FLAGS += -ffunction-sections
C_FLAGS += -fdata-sections
C_FLAGS += -funsigned-char
C_FLAGS += -MMD
C_FLAGS += -fno-delete-null-pointer-checks
C_FLAGS += -fomit-frame-pointer
C_FLAGS += -Os
C_FLAGS += -g1
C_FLAGS += -mcpu=cortex-m4
C_FLAGS += -mthumb
C_FLAGS += -mfpu=fpv4-sp-d16
C_FLAGS += -mfloat-abi=softfp
C_FLAGS += -DMBED_ROM_START=0x8000000
C_FLAGS += -DMBED_ROM_SIZE=0x80000

CXX_FLAGS += -std=gnu++11
CXX_FLAGS += -fno-rtti
CXX_FLAGS += -Wvla
CXX_FLAGS += -include
CXX_FLAGS += mbed_config.h
CXX_FLAGS += -DDEVICE_SPI=1
CXX_FLAGS += -D__MBED__=1
CXX_FLAGS += -DDEVICE_I2CSLAVE=1
CXX_FLAGS += -D__FPU_PRESENT=1
CXX_FLAGS += -DDEVICE_PORTOUT=1
CXX_FLAGS += -DUSBHOST_OTHER
CXX_FLAGS += -DMBED_BUILD_TIMESTAMP=1549297705.4
CXX_FLAGS += -DTARGET_RTOS_M4_M7
CXX_FLAGS += -DDEVICE_RTC=1
CXX_FLAGS += -DDEVICE_MPU=1
CXX_FLAGS += -DDEVICE_SERIAL_ASYNCH=1
CXX_FLAGS += -DTARGET_STM32F4
CXX_FLAGS += -D__CMSIS_RTOS
CXX_FLAGS += -DTARGET_STM32F446xE
CXX_FLAGS += -DTOOLCHAIN_GCC
CXX_FLAGS += -DDEVICE_I2C_ASYNCH=1
CXX_FLAGS += -DTARGET_CORTEX_M
CXX_FLAGS += -DTARGET_LIKE_CORTEX_M4
CXX_FLAGS += -DDEVICE_ANALOGOUT=1
CXX_FLAGS += -DTARGET_M4
CXX_FLAGS += -DCOMPONENT_PSA_SRV_IMPL=1
CXX_FLAGS += -DDEVICE_SPI_ASYNCH=1
CXX_FLAGS += -DDEVICE_LPTICKER=1
CXX_FLAGS += -DDEVICE_PWMOUT=1
CXX_FLAGS += -DDEVICE_INTERRUPTIN=1
CXX_FLAGS += -DTARGET_CORTEX
CXX_FLAGS += -DDEVICE_I2C=1
CXX_FLAGS += -DTRANSACTION_QUEUE_SIZE_SPI=2
CXX_FLAGS += -D__CORTEX_M4
CXX_FLAGS += -DDEVICE_STDIO_MESSAGES=1
CXX_FLAGS += -DTARGET_FF_MORPHO
CXX_FLAGS += -DTARGET_FAMILY_STM32
CXX_FLAGS += -DTARGET_FF_ARDUINO
CXX_FLAGS += -DTARGET_STM32F446RE
CXX_FLAGS += -DTARGET_RELEASE
CXX_FLAGS += -DTARGET_STM
CXX_FLAGS += -DDEVICE_SERIAL_FC=1
CXX_FLAGS += -DCOMPONENT_PSA_SRV_EMUL=1
CXX_FLAGS += -DDEVICE_USTICKER=1
CXX_FLAGS += -DDEVICE_PORTINOUT=1
CXX_FLAGS += -DTARGET_LIKE_MBED
CXX_FLAGS += -D__MBED_CMSIS_RTOS_CM
CXX_FLAGS += -DDEVICE_SLEEP=1
CXX_FLAGS += -DTOOLCHAIN_GCC_ARM
CXX_FLAGS += -DDEVICE_CAN=1
CXX_FLAGS += -DUSB_STM_HAL
CXX_FLAGS += -DCOMPONENT_NSPE=1
CXX_FLAGS += -DTARGET_NUCLEO_F446RE
CXX_FLAGS += -DDEVICE_SPISLAVE=1
CXX_FLAGS += -DDEVICE_ANALOGIN=1
CXX_FLAGS += -DDEVICE_SERIAL=1
CXX_FLAGS += -DDEVICE_FLASH=1
CXX_FLAGS += -DDEVICE_PORTIN=1
CXX_FLAGS += -DARM_MATH_CM4
CXX_FLAGS += -c
CXX_FLAGS += -Wall
CXX_FLAGS += -Wextra
CXX_FLAGS += -Wno-unused-parameter
CXX_FLAGS += -Wno-missing-field-initializers
CXX_FLAGS += -fmessage-length=0
CXX_FLAGS += -fno-exceptions
CXX_FLAGS += -fno-builtin
CXX_FLAGS += -ffunction-sections
CXX_FLAGS += -fdata-sections
CXX_FLAGS += -funsigned-char
CXX_FLAGS += -MMD
CXX_FLAGS += -fno-delete-null-pointer-checks
CXX_FLAGS += -fomit-frame-pointer
CXX_FLAGS += -Os
CXX_FLAGS += -g1
CXX_FLAGS += -mcpu=cortex-m4
CXX_FLAGS += -mthumb
CXX_FLAGS += -mfpu=fpv4-sp-d16
CXX_FLAGS += -mfloat-abi=softfp
CXX_FLAGS += -DMBED_ROM_START=0x8000000
CXX_FLAGS += -DMBED_ROM_SIZE=0x80000

ASM_FLAGS += -x
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += -DTRANSACTION_QUEUE_SIZE_SPI=2
ASM_FLAGS += -D__CORTEX_M4
ASM_FLAGS += -DUSB_STM_HAL
ASM_FLAGS += -DARM_MATH_CM4
ASM_FLAGS += -D__FPU_PRESENT=1
ASM_FLAGS += -DUSBHOST_OTHER
ASM_FLAGS += -D__MBED_CMSIS_RTOS_CM
ASM_FLAGS += -D__CMSIS_RTOS
ASM_FLAGS += -I.
ASM_FLAGS += -Isrc
ASM_FLAGS += -Isrc/com
ASM_FLAGS += -Isrc/com/mbed
ASM_FLAGS += -Isrc/com/mbed/mbed-os
ASM_FLAGS += -Isrc/com/mbed/mbed-os/cmsis
ASM_FLAGS += -Isrc/com/mbed/mbed-os/cmsis/TARGET_CORTEX_M
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver/atmel-rf-driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/atmel-rf-driver/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver/mcr20a-rf-driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/mcr20a-rf-driver/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/802.15.4_RF/stm-s2lp-rf-driver/stm-s2lp-rf-driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/wifi
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/wifi/esp8266-driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/components/wifi/esp8266-driver/ESP8266
ASM_FLAGS += -Isrc/com/mbed/mbed-os/drivers
ASM_FLAGS += -Isrc/com/mbed/mbed-os/events
ASM_FLAGS += -Isrc/com/mbed/mbed-os/events/equeue
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/API
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/AT
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/common
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/device
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/GEMALTO/CINTERION
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/MultiTech/DragonflyNano/PPP
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BC95
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/BG96
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/M26
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/QUECTEL/UG96
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/TELIT
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/TELIT/HE910
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/AT
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/cellular/framework/targets/UBLOX/PPP
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/device_key
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/device_key/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/greentea-client
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/greentea-client/greentea-client
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-client-cli
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-client-cli/mbed-client-cli
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-client-randlib
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-client-randlib/mbed-client-randlib
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-client-randlib/mbed-client-randlib/platform
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-coap
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-coap/mbed-coap
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-coap/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-coap/source/include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-trace
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/mbed-trace/mbed-trace
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/nanostack-libservice
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/nanostack-libservice/mbed-client-libservice
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/nanostack-libservice/mbed-client-libservice/platform
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/unity
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/unity/unity
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/utest
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/frameworks/utest/utest
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lorawan
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lorawan/lorastack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lorawan/lorastack/mac
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lorawan/lorastack/phy
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lorawan/system
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip-sys
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip-sys/arch
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src/include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src/include/lwip
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src/include/lwip/priv
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src/include/lwip/prot
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src/include/netif
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src/include/netif/ppp
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/lwipstack/lwip/src/include/netif/ppp/polarssl
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/mbedtls
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/mbedtls/inc
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/mbedtls/inc/mbedtls
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/mbedtls/inc/psa
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/mbedtls/platform
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/mbedtls/platform/inc
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/mbedtls/targets/TARGET_STM
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/coap-service
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/coap-service/coap-service
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/coap-service/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/coap-service/source/include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/mbed-mesh-api
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/mbed-mesh-api
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/mbed-mesh-api/source/include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/nanostack-hal-mbed-cmsis-rtos
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/nanostack-interface
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/nanostack-event-loop
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/nanostack-event-loop/platform
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack-eventloop/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/nanostack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/nanostack/platform
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Bootstraps
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Fragmentation
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/IPHC_Decode
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/MAC
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Mesh
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/ND
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/NVM
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/Thread
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/6LoWPAN/ws
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/BorderRouter
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Common_Protocols
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Core/include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/DHCPv6_Server
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/DHCPv6_client
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/IEEE802_15_4
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MAC/virtual_rf
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MLE
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/MPL
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/NWK_INTERFACE/Include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/RPL
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/Common
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/PANA
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Security/TLS
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/Neighbor_cache
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/Trickle
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/blacklist
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/etx
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fhss
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/fnv_hash
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/load_balance
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mac_neighbor_table
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/port
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/port/compiler
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/port/cpu
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/dns
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/mdns
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/poll
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/services/serial
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mdns/fnet/fnet_stack/stack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/mle_service
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/nd_proxy
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/pan_blacklist
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/utils
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/Service_Libs/whiteboard
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/configs
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/configs/base
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/ipv6_stack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libDHCPv6
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nanostack/sal-stack-nanostack/source/libNET/src
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/netsocket
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/netsocket/cellular
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/netsocket/cellular/generic_modem_driver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/acore
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/acore/acore
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/controllers
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/nfc
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/nfc/ndef
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/nfc/ndef/common
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/ndef
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/platform
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/tech
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/tech/iso7816
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/tech/isodep
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/tech/type4
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/transceiver
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/nfc/stack/transceiver/pn512
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/blockdevice
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/filesystem
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/filesystem/fat
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/filesystem/fat/ChaN
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/filesystem/littlefs
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/filesystem/littlefs/littlefs
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/conf
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/direct_access_devicekey
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/filesystemstore
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/global_api
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/kv_map
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/securestore
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/kvstore/tdbstore
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/nvstore
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/nvstore/source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/features/storage/system_storage
ASM_FLAGS += -Isrc/com/mbed/mbed-os/hal
ASM_FLAGS += -Isrc/com/mbed/mbed-os/hal/storage_abstraction
ASM_FLAGS += -Isrc/com/mbed/mbed-os/platform
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx4
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/Include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Config
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Include
ASM_FLAGS += -Isrc/com/mbed/mbed-os/rtos/TARGET_CORTEX/rtx5/RTX/Source
ASM_FLAGS += -Isrc/com/mbed/mbed-os/targets/TARGET_STM
ASM_FLAGS += -Isrc/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4
ASM_FLAGS += -Isrc/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE
ASM_FLAGS += -Isrc/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/TARGET_NUCLEO_F446RE
ASM_FLAGS += -Isrc/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F446xE/device
ASM_FLAGS += -Isrc/com/mbed/mbed-os/targets/TARGET_STM/TARGET_STM32F4/device
ASM_FLAGS += -include
ASM_FLAGS += ../src/com/mbed/mbed_config.h
ASM_FLAGS += -x
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += -c
ASM_FLAGS += -Wall
ASM_FLAGS += -Wextra
ASM_FLAGS += -Wno-unused-parameter
ASM_FLAGS += -Wno-missing-field-initializers
ASM_FLAGS += -fmessage-length=0
ASM_FLAGS += -fno-exceptions
ASM_FLAGS += -fno-builtin
ASM_FLAGS += -ffunction-sections
ASM_FLAGS += -fdata-sections
ASM_FLAGS += -funsigned-char
ASM_FLAGS += -MMD
ASM_FLAGS += -fno-delete-null-pointer-checks
ASM_FLAGS += -fomit-frame-pointer
ASM_FLAGS += -Os
ASM_FLAGS += -g1
ASM_FLAGS += -mcpu=cortex-m4
ASM_FLAGS += -mthumb
ASM_FLAGS += -mfpu=fpv4-sp-d16
ASM_FLAGS += -mfloat-abi=softfp


LD_FLAGS :=-Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_memalign_r -Wl,--wrap,_calloc_r -Wl,--wrap,exit -Wl,--wrap,atexit -Wl,-n -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp 
LD_SYS_LIBS :=-Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys  -Wl,--end-group

# Tools and Flags
###############################################################################
# Rules

.PHONY: all clean lst size

all: $(PROJECT).bin size

# 'clean' target: cleans only yellow-specific object files
clean:
	$(call RM,$(SRC_DIR))

.s.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
  


.S.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
  

.c.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CC) $(C_FLAGS) $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CPP) $(CXX_FLAGS) $(INCLUDE_PATHS) -o $@ $<


$(PROJECT).link_script.ld: $(LINKER_SCRIPT)
	@$(PREPROC) $< -o $@

$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS) $(PROJECT).link_script.ld
	$(file >$@.in) $(foreach O,$(filter %.o, $^),$(file >>$@.in,$O))
	+@echo "link: $(notdir $@)"
	$(LD) $(LD_FLAGS) -T $(filter-out %.o, $^) $(LIBRARY_PATHS) --output $@ @$@.in $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf
	$(ELF2BIN) -O binary $< $@
	+@echo "===== bin file ready to flash: $(OBJDIR)/$@ =====" 

$(PROJECT).hex: $(PROJECT).elf
	$(ELF2BIN) -O ihex $< $@


# Rules
###############################################################################
# Dependencies

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)
endif

# Dependencies
###############################################################################
