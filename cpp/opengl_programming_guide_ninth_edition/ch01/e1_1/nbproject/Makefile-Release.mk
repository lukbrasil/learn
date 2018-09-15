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
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/35c7d54d/gl3w.o \
	${OBJECTDIR}/e1_1.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/utils.o


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
LDLIBSOPTIONS=../../../../../glfw-build/src/libglfw3.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e1_1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e1_1: ../../../../../glfw-build/src/libglfw3.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e1_1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e1_1 ${OBJECTFILES} ${LDLIBSOPTIONS} -ldl -lX11 -lXxf86vm -lXrandr -lXinerama -lXcursor -lpthread

${OBJECTDIR}/_ext/35c7d54d/gl3w.o: ../../../../../gl3w/src/gl3w.c
	${MKDIR} -p ${OBJECTDIR}/_ext/35c7d54d
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../gl3w/include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/35c7d54d/gl3w.o ../../../../../gl3w/src/gl3w.c

${OBJECTDIR}/e1_1.o: e1_1.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../../gl3w/include -I../../../../../glfw/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/e1_1.o e1_1.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../../gl3w/include -I../../../../../glfw/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/utils.o: utils.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../../gl3w/include -I../../../../../glfw/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils.o utils.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
