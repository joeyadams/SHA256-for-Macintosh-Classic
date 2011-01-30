#   File:       sha256.make
#   Target:     sha256
#   Created:    Monday, August 27, 1956 09:30:59 PM


MAKEFILE        = sha256.make
¥MondoBuild¥    = {MAKEFILE}  # Make blank to avoid rebuilds when makefile is modified

ObjDir          = :
Includes        = 

Sym-PPC         = -sym off
Sym-68K         = -sym off

PPCCOptions     = {Includes} {Sym-PPC} -opt speed 

COptions        = {Includes} {Sym-68K} -model near -opt speed 


### Source Files ###

SrcFiles        =  ¶
				  main.c ¶
				  sha256.c


### Object Files ###

ObjFiles-PPC    =  ¶
				  "{ObjDir}main.c.x" ¶
				  "{ObjDir}sha256.c.x"

ObjFiles-68K    =  ¶
				  "{ObjDir}main.c.o" ¶
				  "{ObjDir}sha256.c.o"


### Libraries ###

LibFiles-PPC    =  ¶
				  "{PPCLibraries}PPCSIOW.o" ¶
				  "{SharedLibraries}InterfaceLib" ¶
				  "{SharedLibraries}StdCLib" ¶
				  "{SharedLibraries}MathLib" ¶
				  "{PPCLibraries}StdCRuntime.o" ¶
				  "{PPCLibraries}PPCCRuntime.o" ¶
				  "{PPCLibraries}PPCToolLibs.o"

LibFiles-68K    =  ¶
				  "{Libraries}MathLib.o" ¶
				  "{CLibraries}StdCLib.o" ¶
				  "{Libraries}SIOW.o" ¶
				  "{Libraries}MacRuntime.o" ¶
				  "{Libraries}IntEnv.o" ¶
				  "{Libraries}ToolLibs.o" ¶
				  "{Libraries}Interface.o"


### Default Rules ###

.c.x  Ä  .c  {¥MondoBuild¥}
	{PPCC} {depDir}{default}.c -o {targDir}{default}.c.x {PPCCOptions}

.c.o  Ä  .c  {¥MondoBuild¥}
	{C} {depDir}{default}.c -o {targDir}{default}.c.o {COptions}


### Build Rules ###

sha256  ÄÄ  {ObjFiles-PPC} {LibFiles-PPC} {¥MondoBuild¥}
	PPCLink ¶
		-o {Targ} ¶
		{ObjFiles-PPC} ¶
		{LibFiles-PPC} ¶
		{Sym-PPC} ¶
		-mf -d ¶
		-t 'APPL' ¶
		-c 'siow'


sha256  ÄÄ  {ObjFiles-68K} {LibFiles-68K} {¥MondoBuild¥}
	ILink ¶
		-o {Targ} ¶
		{ObjFiles-68K} ¶
		{LibFiles-68K} ¶
		{Sym-68K} ¶
		-mf -d ¶
		-t 'APPL' ¶
		-c 'siow' ¶
		-model near ¶
		-state rewrite ¶
		-compact -pad 0
	If "{Sym-68K}" =~ /-sym Å[nNuU]Å/
		ILinkToSYM {Targ}.NJ -mf -sym 3.2 -c 'sade'
	End


sha256  ÄÄ  "{RIncludes}"SIOW.r {¥MondoBuild¥}
	Rez "{RIncludes}"SIOW.r -o {Targ} -append


### Required Dependencies ###

"{ObjDir}main.c.x" "{ObjDir}main.c.o"  Ä  main.c
"{ObjDir}sha256.c.x" "{ObjDir}sha256.c.o"  Ä  sha256.c


### Optional Dependencies ###
### Build this target to generate "include file" dependencies. ###

Dependencies  Ä  $OutOfDate
	MakeDepend ¶
		-append {MAKEFILE} ¶
		-ignore "{CIncludes}" ¶
		-objdir "{ObjDir}" ¶
		-objext .x ¶
		-objext .o ¶
		{Includes} ¶
		{SrcFiles}


