#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/zrecord.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/zquery.o \
	${OBJECTDIR}/zconnection.o \
	${OBJECTDIR}/zoptions.o \
	${OBJECTDIR}/zresultset.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lyaz -lboost_python

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libyaz4python.so

dist/Release/GNU-Linux-x86/libyaz4python.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libyaz4python.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/zrecord.o: zrecord.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/python2.6 -I/usr/include/boost -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zrecord.o zrecord.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/python2.6 -I/usr/include/boost -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/zquery.o: zquery.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/python2.6 -I/usr/include/boost -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zquery.o zquery.cpp

${OBJECTDIR}/zconnection.o: zconnection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/python2.6 -I/usr/include/boost -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zconnection.o zconnection.cpp

${OBJECTDIR}/zoptions.o: zoptions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/python2.6 -I/usr/include/boost -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zoptions.o zoptions.cpp

${OBJECTDIR}/zresultset.o: zresultset.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/python2.6 -I/usr/include/boost -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zresultset.o zresultset.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libyaz4python.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
