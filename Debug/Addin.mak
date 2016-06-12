################################################
# Make file for CASIO fx-9860G SDK Addin
#
############################
# Directory defines
TCDIR = G:\Casio SDK\OS\SH
OSDIR = G:\Casio SDK\OS
APPDIR = G:\Casio SDK\Projekte\Speed
OUTDIR = G:\Casio SDK\Projekte\Speed\Debug

################
# Main Defines
SH_EXEDIR=$(TCDIR)\bin

# Hitachi SH C/C++ Compiler02 phase
SHCC02_EXE=shc.exe
SHCC02_DEP="$(OSDIR)\FX\include\fxlib.h" 

# Hitachi SH Assembler03 phase
SHASM03_EXE=asmsh.exe

# Hitachi OptLinker04 phase
SHLINK04_EXE=Optlnk.exe
SHLINK04_DEP="$(OSDIR)\FX\lib\fx9860G_library.lib"
SHLINK04_DEP2="$(OSDIR)\FX\lib\setup.obj"
EPSILON="$(OSDIR)\FX\lib\revolution.lib"
#######################
# Files to build
FILE0=Speed
FILESRC0="$(APPDIR)\$(FILE0).c"
FILEOBJ0="$(OUTDIR)\$(FILE0).obj"
FILE1=change_freq
FILESRC1="$(APPDIR)\$(FILE1).src"
FILEOBJ1="$(OUTDIR)\$(FILE1).obj"
FILE2=change_iclk
FILESRC2="$(APPDIR)\$(FILE2).src"
FILEOBJ2="$(OUTDIR)\$(FILE2).obj"
FILE3=change_pclk
FILESRC3="$(APPDIR)\$(FILE3).src"
FILEOBJ3="$(OUTDIR)\$(FILE3).obj"
FILE4=change_bclk
FILESRC4="$(APPDIR)\$(FILE4).src"
FILEOBJ4="$(OUTDIR)\$(FILE4).obj"
FILE5=change_sclk
FILESRC5="$(APPDIR)\$(FILE5).src"
FILEOBJ5="$(OUTDIR)\$(FILE5).obj"
RFILE=FXADDINror
USERALLOBJ=$(FILEOBJ0) $(FILEOBJ1) $(FILEOBJ2) $(FILEOBJ3) $(FILEOBJ4) $(FILEOBJ5)

#######################
# nmake "all" statement

ALL:  SH_ENV \
	$(USERALLOBJ) \
	$(OUTDIR)\$(RFILE).bin \

####################
# Description blocks

!MESSAGE %3#C$z`&'0?
!MESSAGE
!MESSAGE Executing Hitachi SH C/C++ Compiler/Assembler phase
!MESSAGE

SH_ENV : 
	set SHC_INC=$(TCDIR)\include
	set PATH=$(TCDIR)\bin
	set SHC_LIB=$(TCDIR)\bin
	set SHC_TMP=$(OUTDIR)

$(FILEOBJ0) : $(FILESRC0) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ0)
-show=source
-listfile="$(OUTDIR)\$(FILE0).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC0)
-lang=c
-nologo
-debug
<<

$(FILEOBJ1) : $(FILESRC1)
	"$(SH_EXEDIR)\$(SHASM03_EXE)" -subcommand=<<
$(FILESRC1)
-cpu=sh3
-endian=big
-round=zero
-denormalize=off
-include="$(APPDIR)"
-include="$(OSDIR)\FX\include"
-debug
-object=$(FILEOBJ1)
-literal=pool,branch,jump,return
-nologo
-chgincpath
-errorpath
<<

$(FILEOBJ2) : $(FILESRC2)
	"$(SH_EXEDIR)\$(SHASM03_EXE)" -subcommand=<<
$(FILESRC2)
-cpu=sh3
-endian=big
-round=zero
-denormalize=off
-include="$(APPDIR)"
-include="$(OSDIR)\FX\include"
-debug
-object=$(FILEOBJ2)
-literal=pool,branch,jump,return
-nologo
-chgincpath
-errorpath
<<

$(FILEOBJ3) : $(FILESRC3)
	"$(SH_EXEDIR)\$(SHASM03_EXE)" -subcommand=<<
$(FILESRC3)
-cpu=sh3
-endian=big
-round=zero
-denormalize=off
-include="$(APPDIR)"
-include="$(OSDIR)\FX\include"
-debug
-object=$(FILEOBJ3)
-literal=pool,branch,jump,return
-nologo
-chgincpath
-errorpath
<<

$(FILEOBJ4) : $(FILESRC4)
	"$(SH_EXEDIR)\$(SHASM03_EXE)" -subcommand=<<
$(FILESRC4)
-cpu=sh3
-endian=big
-round=zero
-denormalize=off
-include="$(APPDIR)"
-include="$(OSDIR)\FX\include"
-debug
-object=$(FILEOBJ4)
-literal=pool,branch,jump,return
-nologo
-chgincpath
-errorpath
<<

$(FILEOBJ5) : $(FILESRC5)
	"$(SH_EXEDIR)\$(SHASM03_EXE)" -subcommand=<<
$(FILESRC5)
-cpu=sh3
-endian=big
-round=zero
-denormalize=off
-include="$(APPDIR)"
-include="$(OSDIR)\FX\include"
-debug
-object=$(FILEOBJ5)
-literal=pool,branch,jump,return
-nologo
-chgincpath
-errorpath
<<

!MESSAGE
!MESSAGE Executing Hitachi OptLinker04 phase
!MESSAGE

"$(OUTDIR)\$(RFILE).bin" : $(USERALLOBJ) $(SHLINK04_DEP2) $(SHLINK04_DEP)
	"$(SH_EXEDIR)\$(SHLINK04_EXE)" -subcommand=<<
noprelink
sdebug
rom D=R
nomessage 
list "$(OUTDIR)\$(RFILE).map"
show symbol
nooptimize
start P_TOP,P,C,D,C$VTBL,C$INIT/0300200,B_BR_Size,B,R/08100000
fsymbol P
nologo
input $(USERALLOBJ)
input $(SHLINK04_DEP2)
library $(SHLINK04_DEP)
library $(EPSILON)
output "$(OUTDIR)\$(RFILE).abs"
-nomessage=1100
end
input "$(OUTDIR)\$(RFILE).abs"
form binary
output "$(OUTDIR)\$(RFILE).bin"
exit
<<

