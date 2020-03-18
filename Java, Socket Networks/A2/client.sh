#!/bin/sh
if [ "$#" -ne 4 ]
then
	echo "please type in 4 arguments in order:"
	echo "<hostname for the network emulator>,"
	echo "<UDP port number used by the link emulator to receive ACKs from the receiver>,"
	echo "<UDP port number used by the receiver to receive data from the emulator>,"
	echo "<name of the file into which the received data is written>"
	exit 1
fi
java Receiver "$1" $2 $3 "$4"
