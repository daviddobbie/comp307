
# Will Smart  5/1/2004

all : vgpcntrl addplan ext resetsem exttab removesem removeexp showexp

vgpcntrl : toolcode/maincntrl.c toolcode/files.c toolcode/files.h
	g++ -o vgpcntrl toolcode/maincntrl.c toolcode/files.c

addplan : toolcode/addplan.c toolcode/files.c toolcode/files.h
	g++ -o addplan toolcode/addplan.c toolcode/files.c

ext : toolcode/extractdata.c toolcode/files.c toolcode/files.h
	g++ -o ext toolcode/extractdata.c toolcode/files.c

exttab : toolcode/extracttab.c toolcode/files.c toolcode/files.h
	g++ -o exttab toolcode/extracttab.c toolcode/files.c

showexp : toolcode/showexp.c toolcode/files.c toolcode/files.h
	g++ -o showexp toolcode/showexp.c toolcode/files.c

removeexp : toolcode/removeexp.c toolcode/files.c toolcode/files.h
	g++ -o removeexp toolcode/removeexp.c toolcode/files.c

resetsem : toolcode/resetsem.c toolcode/files.c toolcode/files.h
	g++ -o resetsem toolcode/resetsem.c toolcode/files.c

removesem : toolcode/removesem.c
	g++ -o removesem toolcode/removesem.c

