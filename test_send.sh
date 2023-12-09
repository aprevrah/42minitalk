#!/bin/bash

#!/bin/bash

# Start the server in the background
./server 2>&1 &

# Capture the server's PID using $!
server_pid=$!

echo "Server PID: $server_pid"

# Define the second argument for the clients
second_arg="TEST awfkw regj kergkore erkgrwejhgueh rejgrhej regkjreg jkregjer kjgjreg krejgkre erjgkerj regkerj ergker jergk erj"

# Run the first client program with the captured PID and the second argument
(./client "$server_pid" "$second_arg" 2>&1) | while IFS= read -r line; do
    echo "
Client 1: $line"
done &

#: <<'END'
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

#END
# Wait for all programs to finish
wait
