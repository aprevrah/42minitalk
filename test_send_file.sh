#!/bin/bash

# Define what server and client to use
server="./minitalk/server"
client="./minitalk/client"

# Define the message argument for the client
msg=$(cat ./Lorem_Ipsum.txt)

# Start the server in the background
$server 2>&1 &

# Capture the server's PID using $!
server_pid=$!

echo "Server PID: $server_pid"

# Run the client program with the captured PID and the message argument
($client "$server_pid" "$msg" 2>&1) | while IFS= read -r line; do
    echo "
Client: $line"
done &

# Wait for the client to finish
wait
