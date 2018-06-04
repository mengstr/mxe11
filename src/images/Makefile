DEV		= dev/rk2!b0:2 dev/tty0!c0:1 
ROOT		= mx
LIB		= lib/libc.a
SRC1		= usr/src/ usr/src/gethex.c usr/src/addr.c usr/src/hanoi.c usr/src/halt.c usr/src/sh.c
SRC2		= usr/src/df.c usr/src/date.c usr/src/mips.c usr/src/em1.c usr/src/em2.c
CLIB		= usr/clib/ usr/clib/ctime.c usr/clib/ctrun
SYS		= usr/sys/mxsys/alloc.c usr/sys/dev/kl.c usr/sys/run 
BIN1		= bin/halt bin/date bin/df bin/dump bin/ln bin/ls bin/sh
BIN2		= bin/mail bin/pr bin/df bin/restor bin/who usr/bin/bench2 usr/bin/hanoi usr/bin/mips
USR		= usr/c/ usr/c/c0 usr/c/c1 usr/mxe/ etc/passwd
D2		= s1/update1 s2/update2
FSUTIL		= u6-fsutil
DSK1		= disk1.bin
DSK2		= disk2.bin


default:	
		echo "usage make insert"

insert:		
		cp _mini-unix/tape1.bin disk1.bin
		cp _mini-unix/tape2.bin disk2.bin
		cp _mini-unix/tape3.bin disk3.bin
		$(FSUTIL) -F -a $(DSK1) $(DEV)
		$(FSUTIL) -F -a $(DSK1) $(ROOT)
		$(FSUTIL) -F -a $(DSK1) $(SRC1)
		$(FSUTIL) -F -a $(DSK1) $(SRC2)
		$(FSUTIL) -F -a $(DSK1) $(BIN1)
		$(FSUTIL) -F -a $(DSK1) $(BIN2)
		$(FSUTIL) -F -a $(DSK1) $(CLIB)
		$(FSUTIL) -F -a $(DSK1) $(SYS)
		$(FSUTIL) -F -a $(DSK1) $(USR)
		$(FSUTIL) -F -c $(DSK1)
		$(FSUTIL) -F -a $(DSK2) $(D2)
		$(FSUTIL) -F -c $(DSK2)



