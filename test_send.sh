#!/bin/bash

#!/bin/bash

# Start the server in the background
./server 2>&1 &

# Capture the server's PID using $!
server_pid=$!

echo "Server PID: $server_pid"

# Define the second argument for the clients
second_arg="TSERefwefwef weewfwef ewfgerg ergerger ergherhghrgu erjgnrneug ergerugerhgherg erg"

# Run the first client program with the captured PID and the second argument
(./client "$server_pid" "$second_arg" 2>&1) | while IFS= read -r line; do
    echo "
Client 1: $line"
done &

# Run the second client program with the captured PID and the second argument
(./client "$server_pid" "$second_arg" 2>&1) | while IFS= read -r line; do
    echo "
Client 2: $line"
done &

# Run the second client program with the captured PID and the second argument
(./client "$server_pid" "$second_arg" 2>&1) | while IFS= read -r line; do
    echo "
Client 3: $line"
done &

# Run the second client program with the captured PID and the second argument
(./client "$server_pid" "$second_arg" 2>&1) | while IFS= read -r line; do
    echo "
Client 4: $line"
done &

# Wait for all programs to finish
wait
