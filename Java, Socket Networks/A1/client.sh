#!/bin/sh
if [ "$#" -ne 4 ]
then
	echo "please type in 4 arguments <server_address> <n_port> <req_code> <msg> in order."
	exit 1
fi
java Client $1 $2 $3 "$4"
