#
# Defines the part type that this project uses.
#
#define DEBUG
PART=LM3S2965

#
# Set the processor variant.
#
VARIANT=cm3

#
# The base directory
#
ROOT=../

#
# Current working directory
#
PWD=`pwd`

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=../drivers
VPATH+=../utils

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=..
IPATH+=../lwip-1.3.2/apps
IPATH+=../lwip-1.3.2/ports/stellaris/include
IPATH+=../lwip-1.3.2/src/include
IPATH+=../lwip-1.3.2/src/include/ipv4

#
# The default rule, which causes the project to be built.
#
all: ${COMPILER}
all: ${COMPILER}/can_ethernet.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# Install - OpenOCD has to be running for this to work, use included ekc-lm3s8962.cfg file
# run OpenOCD with command "openocd -f ekc-lm3s8962.cfg" in one terminal
# and then in another "make install"
#
install:
	@echo "flash_load ${PWD}/gcc/can_ethernet.bin" | telnet localhost 4444

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the project
#
${COMPILER}/can_ethernet.axf: ${COMPILER}/c2e_main.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/c2e_can.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/c2e_eth.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/c2e_events.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/c2e_udp.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/c2e_utils.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/rit128x96x4.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/lwiplib.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/ringbuf.o
${COMPILER}/can_ethernet.axf: ${COMPILER}/ustdlib.o
${COMPILER}/can_ethernet.axf: ${ROOT}/driverlib/${COMPILER}-cm3/libdriver-cm3.a
${COMPILER}/can_ethernet.axf: c2e_linker.ld
SCATTERgcc_can_ethernet=c2e_linker.ld
ENTRY_can_ethernet=RESET_handler

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
