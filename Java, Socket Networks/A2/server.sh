#!/bin/sh
if [ "$#" -ne 4 ]
then
	echo "please type in 4 arguments in order:"
	echo "<host address of the network emulator>,"
	echo "<UDP port number used by the emulator to receive data from the sender>,"
	echo "<UDP port number used by the sender to receive ACKs from the emulator>,"
	echo "<name of the file to be transferred>"
	exit 1
fi
java Sender "$1" $2 $3 "$4"
