#!/bin/bash
printf "=== TESTING ARITHMETIC EXPANSION =========================================================\n"
mkdir -p outputs
mkdir -p expected_outputs
i=0
ok=0
ko=0
rm -rf error_logs
for cmd in command_files/*; do
	str=`cat $cmd`
	printf "\n%2d: Launching: %-65s%s" $i "$str" "=>"
	bash < $cmd > expected_outputs/out_$i 2>&1
	../../42sh < $cmd > outputs/out_$i 2>&1
	sed -i 's/42sh/bash/g' outputs/out_$i
	diff expected_outputs/out_$i outputs/out_$i > /tmp/diff_log 2>&1
	if [ $? = 0 ]
	then
		printf "\033[1;32m[DIFF OK]\033[0m"
		ok=$(($ok + 1))
	else
		printf "\033[1;31m[DIFF KO]\033[0m"
		ko=$(($ko + 1))
		mkdir -p error_logs
		cp /tmp/diff_log error_logs/err_`printf "%02d" $i`
	fi
	i=$(($i + 1))
done

printf "\n\n=== TEST ASSESMENT REPORT =================================================================\n\n"
printf "\033[1;31m%d failed test(s)\033[0m\n" $ko
printf "\033[1;32m%d successful test(s)\033[0m\n" $ok
if [ $ko = 0 ]
then
	printf "\033[1;36m[ALL UNIT TESTS PASSED]\033[0m\n"
else
	printf "\033[1;31m[UNIT TESTS FAILURE]\033[0m\n"
fi
printf "\n=== END OF REPORT =========================================================================\n\n"