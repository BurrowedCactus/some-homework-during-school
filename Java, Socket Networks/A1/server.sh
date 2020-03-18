#!/bin/sh
if [ "$#" -ne 1 ]
then
	echo "please type in seq_code as the only one argument. "
	exit 1
fi
java Server $1
