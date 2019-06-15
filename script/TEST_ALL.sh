#!/bin/bash
if [ "$#" -lt 1 ]
then
	printf "One argument or more expected (Shell To Test's PATH)\nGOT: $#"
	exit 1
fi
if [ -n $TERM ]
then
	# Ansi excape color sequences
	RED="\033[1;31m"
	GREEN="\033[0;32m"
	BGREEN="\033[1;32m"
	BLUE="\033[0;34m"
	YELLOW="\033[0;33m"
	PURPLE="\033[0;35m"
	CYAN="\033[0;36m"
	GREY="\033[0;37m"

	# When printed reset the color
	COLRESET="\033[0m"

	# Move the cursor at the begining of the line
	MOVELINE="\033[1A"
	# Erase current line
	CLEARLINE="\033[K"
fi
categories=0
printf "=================================================\n"
printf "============== CORRECTION TESTS =================\n"
printf "=================================================\n\n"
printf "=== MINISHELL'S PREREQUISITES =================== > "
bash --posix correction/minishell_tests/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
fi
printf "=== 21SH'S PREREQUISITES ======================== > "
bash --posix correction/21sh_tests/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
fi
printf "=== BUILTINS TESTS ============================== > "
bash --posix correction/builtins/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
fi
printf "=== ENVIRONNEMENT MANAGEMENT ==================== > "
bash --posix correction/environnement/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
fi
printf "=== LOGICAL OPERATORS =========================== > "
bash --posix correction/logical_operators/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d\n"$COLRESET $ok $(($ko+$ok))
fi

#####################################################################
if [ $categories = 0 ]
then
	printf $BGREEN"[ALL UNIT TESTS PASSED]\n"$COLRESET
else
	printf $RED"[%d CATEGORIE(S) FAILED]\n"$COLRESET $categories
fi
#####################################################################

printf "\n=================================================\n"
printf "========== END OF CORRECTION TESTS ==============\n"
printf "=================================================\n\n"
categories=0


printf "=== TESTING STANDALONE COMMANDS ================= > "
bash --posix standalone_commands/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d"$COLRESET $ok $(($ko+$ok))
fi
if [ -e /tmp/standalone_memory_report ]
then
	printf " < "$RED"[MEMORY ERRORS! REPORT AVAILABLE IN /tmp/standalone_memory_report]\n"$COLRESET
else
	printf " < "$BGREEN"[ALL HEAP BLOCKS WERE FREED -- NO LEAKS ARE POSSIBLE]\n"$COLRESET
fi


printf "=== TESTING MISC COMMANDS ======================= > "
bash --posix misc/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d"$COLRESET $ok $(($ko+$ok))
fi
if [ -e /tmp/misc_memory_report ]
then
	printf " < "$RED"[MEMORY ERRORS! REPORT AVAILABLE IN /tmp/misc_memory_report]\n"$COLRESET
else
	printf " < "$BGREEN"[ALL HEAP BLOCKS WERE FREED -- NO LEAKS ARE POSSIBLE]\n"$COLRESET
fi


printf "=== TESTING 'TEST' BUILTIN UTILITY ============== > "
bash --posix builtin_test/wrapper.sh "$1" "$2" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d"$COLRESET $ok $(($ko+$ok))
fi
if [ -e /tmp/builtin_test_memory_report ]
then
	printf " < "$RED"[MEMORY ERRORS! REPORT AVAILABLE IN /tmp/builtin_test_memory_report]\n"$COLRESET
else
	printf " < "$BGREEN"[ALL HEAP BLOCKS WERE FREED -- NO LEAKS ARE POSSIBLE]\n"$COLRESET
fi


printf "=== TESTING ARITHMETIC EXPANSION ================ > "
bash --posix arithmetic/wrapper.sh "$1" "$2" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d"$COLRESET $ok $(($ko+$ok))
fi
if [ -e /tmp/arithmetic_memory_report ]
then
	printf " < "$RED"[MEMORY ERRORS! REPORT AVAILABLE IN /tmp/arithmetic_memory_report]\n"$COLRESET
else
	printf " < "$BGREEN"[ALL HEAP BLOCKS WERE FREED -- NO LEAKS ARE POSSIBLE]\n"$COLRESET
fi


printf "=== TESTING PATTERN MATCHING ==================== > "
bash --posix pattern_matching/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d"$COLRESET $ok $(($ko+$ok))
fi
if [ -e /tmp/pattern_memory_report ]
then
	printf " < "$RED"[MEMORY ERRORS! REPORT AVAILABLE IN /tmp/pattern_memory_report]\n"$COLRESET
else
	printf " < "$BGREEN"[ALL HEAP BLOCKS WERE FREED -- NO LEAKS ARE POSSIBLE]\n"$COLRESET
fi


printf "=== TESTING HISTORY IMPLEMENTATION ============== > "
bash --posix history/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d"$COLRESET $ok $(($ko+$ok))
fi
if [ -e /tmp/pattern_memory_report ]
then
	printf " < "$RED"[MEMORY ERRORS! REPORT AVAILABLE IN /tmp/history_memory_report]\n"$COLRESET
else
	printf " < "$BGREEN"[ALL HEAP BLOCKS WERE FREED -- NO LEAKS ARE POSSIBLE]\n"$COLRESET
fi

printf "=== TESTING HASH TABLE IMPLEMENTATION =========== > "
bash --posix hash/wrapper.sh "$1" 1>/tmp/unit_out 2>&1
ok=`cat /tmp/unit_out | grep "DIFF OK" | wc -l`
ko=`cat /tmp/unit_out | grep "DIFF KO" | wc -l`
if [ $ko = 0 ]
then
	printf $BLUE"%02d/%02d"$COLRESET $ok $(($ko+$ok))
else
	categories=$(($categories+1))
	printf $RED"%02d/%02d"$COLRESET $ok $(($ko+$ok))
fi
if [ -e /tmp/pattern_memory_report ]
then
	printf " < "$RED"[MEMORY ERRORS! REPORT AVAILABLE IN /tmp/hash_table_memory_report]\n"$COLRESET
else
	printf " < "$BGREEN"[ALL HEAP BLOCKS WERE FREED -- NO LEAKS ARE POSSIBLE]\n"$COLRESET
fi

#####################################################################
if [ $categories = 0 ]
then
	printf $BGREEN"[ALL UNIT TESTS PASSED]\n"$COLRESET
else
	printf $RED"[%d CATEGORIE(S) FAILED]\n"$COLRESET $categories
fi
#####################################################################
rm -rf fifo out error_logs
rm -rf MAKE_log VLA_log \[c\] aa ab auteur checker-279/ empty/ emptyfile  exec fifo MAKE_log VLA_log noexec noread notempty notfifo nowrite one/ read write
