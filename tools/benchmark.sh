#!/bin/sh
#
# Write a file with the mean of 200 `time COMMAND` results.
#  Uses AWK to collect and mean the results

COMMAND=$@

echo "#BENCHMARK RESULTS FOR: " "$COMMAND" > benchmark.result.txt

for i in {1..200}; do
	(time -p $COMMAND ) 2>&1 |tail -n3 >> benchmark.result.txt
done

awk -- "/^real.*/{ rlt += \$2; rltn++;}/^user.*/{ ust += \$2; ustn++;}/^sys.*/{ syt += \$2; sytn++;} END{ print \"real\", rlt/rltn, \"[\" rltn \"]\";print \"user\", ust/ustn, \"[\" ustn \"]\"; print \"sys\", syt/sytn, \"[\" sytn \"]\";}" < benchmark.result.txt


