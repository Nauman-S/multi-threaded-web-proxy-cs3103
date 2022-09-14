#! /bin/sh
echo "AutoTester Script has begun"
AUTOTESTER_FILE=../Code34/Debug/AutoTester.exe

if test -f "$AUTOTESTER_FILE"; then
    echo "AutoTester.exe found"
else
    echo "AutoTester.exe not found"
	exit 1
fi

for DIRECTORY in */; 
do 
	if test -n "SOURCE_FILE"; then
		unset SOURCE_FILE
	fi
	
	if test -n "QUERY_FILE"; then
		unset QUERY_FILE
	fi
	
	for FILE in $DIRECTORY*
	do
		if [[ $FILE == *queries.txt ]]; then
			QUERY_FILE=$FILE
		elif [[ $FILE == *source.txt ]]; then
			SOURCE_FILE=$FILE
		fi
	done
		
	if test -n "SOURCE_FILE" && test -n "QUERY_FILE"; then
		echo "RUNNING ${SOURCE_FILE}, ${QUERY_FILE} IN ${DIRECTORY}"

		$AUTOTESTER_FILE "$SOURCE_FILE" "$QUERY_FILE" "$DIRECTORY\\out.xml"
	else 
		echo "Query/Source File Not found"
	fi
	
	printf "\n\n\n\n\n"
	
done

echo "AutoTester Script has completed"
#EOF - Donot add anything after this