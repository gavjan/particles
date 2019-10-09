#!/bin/bash
PROG=$1
DIR=$2
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
FILES=$DIR/*.in

for f in $FILES
do
out=${f::-2}
out="${out}out"

err=${f::-2}
err="${err}err"
valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q ./$PROG -g <$f >$PROG.out 2>$PROG.err



DIFF1=$(diff $out $PROG.out)
DIFF2=$(diff $err $PROG.err)
if [ "$DIFF1" ] || [ "$DIFF2" ]; then
	echo -e "${RED} ${f} didn't pass ${NC}"
else
	echo -e "${GREEN} ${f} passed${NC}"
fi

done
rm $PROG.out
rm $PROG.err
