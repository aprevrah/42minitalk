#!/bin/bash


# Define what server and client to use
server="./minitalk/server"
client="./minitalk/client"

# Define the message argument for the clients
msg="This is a test message"

# Start the server in the background
$server 2>&1 &

# Capture the server's PID using $!
server_pid=$!

echo "Server PID: $server_pid"

# Run the first client program with the captured PID and the message argument
($client "$server_pid" "$msg" 2>&1) | while IFS= read -r line; do
    echo "
Client 1: $line"
done &

#Comment the next line out for multi send, not working consistently with my implementation sadly
: <<'END'

($client "$server_pid" "$msg" 2>&1) | while IFS= read -r line; do
    echo "
Client 2: $line"
done &

($client "$server_pid" "$msg" 2>&1) | while IFS= read -r line; do
    echo "
Client 3: $line"
done &

($client "$server_pid" "$msg" 2>&1) | while IFS= read -r line; do
    echo "
Client 4: $line"
done &

#Comment the next line out for multi send
END

# Wait for all clients to finish
wait