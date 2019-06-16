#!/bin/bash
printf "=== TESTING LOGICAL OPERATORS COMMANDS =============================================================================\n"
bkp_pwd=`pwd`
cd correction/builtins 1>/dev/null 2>&1
rm -rf /tmp/outputs
rm -rf /tmp/expected_outputs
mkdir -p /tmp/outputs
mkdir -p /tmp/expected_outputs
rm -rf error_logs
i=0
ok=0
ko=0
system=`uname`
rm -rf error_logs
for cmd in command_files/*; do
	str=`cat $cmd | head -n1`
	printf "\n%2d: Launching: %-90s%s" $i "$str" "=>"
	bash < $cmd > /tmp/expected_outputs/out_$i 2>&1
	if [ "$#" -eq 1 ]
	then
		../../"$1" < $cmd > /tmp/outputs/out_$i 2>&1
	else
		../../../42sh < $cmd > /tmp/outputs/out_$i 2>&1
	fi
	if [ $system != 'Linux' ]
	then
		sed -i '' "/SIGPIPE/d" /tmp/outputs/out_$i
		sed -i '' "s/Yes/No/g" /tmp/outputs/out_$i
		sed -i '' "s/42sh:/bash:/g" /tmp/outputs/out_$i
		sed -i '' "s/line [0-9]*: //g" /tmp/expected_outputs/out_$i
	else
		sed -i "/SIGPIPE/d" /tmp/outputs/out_$i
		sed -i "s/Yes/No/g" /tmp/outputs/out_$i
		sed -i "s/42sh:/bash:/g" /tmp/outputs/out_$i
		sed -i "s/line [0-9]*: //g" /tmp/expected_outputs/out_$i
	fi
	diff /tmp/expected_outputs/out_$i /tmp/outputs/out_$i > /tmp/diff_log 2>&1
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

printf "\n\n=== TEST ASSESMENT REPORT ==========================================================================================\n\n"
printf "\033[1;31m%d failed test(s)\033[0m\n" $ko
printf "\033[1;32m%d successful test(s)\033[0m\n" $ok
if [ $ko = 0 ]
then
	printf "\033[1;36m[ALL UNIT TESTS PASSED]\033[0m\n"
else
	printf "\033[1;31m[UNIT TESTS FAILURE]\033[0m\n"
fi
printf "\n=== END OF REPORT ==================================================================================================\n\n"
rm -rf dup_fd err fifo out redir_one_to_all test_file /tmp/diff_log #/tmp/expected_outputs /tmp/outputs
cd $bkp_pwd
