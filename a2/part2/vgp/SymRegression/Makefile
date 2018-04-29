
# Will Smart  5/1/2004

vgp : ../src/allc.c ../src/allc.h ../src/node.c ../src/node.h ../src/op.c ../src/op.h ../src/rand.c ../src/rand.h ../src/main.c ../src/pop.c ../src/pop.h ../src/fit.c ../src/fit.h \
      common.h node.c fit.c pop.c
	gcc -DUse_SymRegression -O -o vgp ../src/allc.c node.c ../src/op.c ../src/rand.c ../src/main.c pop.c fit.c -lm

