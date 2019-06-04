#!/bin/bash
printf "=== TESTING STANDALONES COMMANDS ==============\n"
mkdir -p outputs
mkdir -p expected_outputs
i=0
ok=0
ko=0
for cmd in command_files/*; do
	str=`cat $cmd`
	printf "\nLaunching: %-25s%s" "$str" "=>"
	bash < $cmd > expected_outputs/out_$i 2>&1
	../../42sh < $cmd > outputs/out_$i 2>&1
	diff expected_outputs/out_$i outputs/out_$i > /dev/null 2>&1
	if [ $? = 0 ]
	then
		printf "\033[1;32m[DIFF OK]\033[0m"
		ok=$(($ok + 1))
	else
		printf "\033[1;31m[DIFF KO]\033[0m"
		ko=$(($ko + 1))
	fi
	i=$(($i + 1))
done

printf "\n\n=== TEST ASSESMENT REPORT =====================\n\n"
printf "\033[1;31m%d failed test(s)\033[0m\n" $ko
printf "\033[1;32m%d successful test(s)\033[0m\n" $ok
if [ $ko = 0 ]
then
	printf "\033[1;36m[ALL UNIT TESTS PASSED]\033[0m\n"
else
	printf "\033[1;31m[UNIT TESTS FAILURE]\033[0m\n"
fi
printf "\n=== END OF REPORT =============================\n\n"