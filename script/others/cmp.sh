sh $1 > test1;
cat test1;
echo "{===============^=SH=^======================v=42sh=v===================}";
../42sh $1 > test2
cat test2;
#echo {=======================================================================};
#diff test1 test2
