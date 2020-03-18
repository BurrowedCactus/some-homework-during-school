#!/bin/sh
if [ "$#" -ne 3 ]
then
	echo "please type in 4 arguments in order:"
	echo "<the address of the tracker>,"
	echo "<the port number of the tracker>,"
	echo "<the minimum alive time in seconds>,"
	exit 1
fi
java -cp code Peer "$1" $2 $3
