#!/bin/bash

# Check for the correct number of arguments
if [ "$#" -lt 3 ]; then
    echo "Usage: $0 <movieName> <theaterName> <seats...>"
    exit 1
fi

# Extract the movie name and theater name from the arguments
movieName="$1"
theaterName="$2"

# Shift the arguments to get the seats
shift 2
seats=("$@") # Array of seat identifiers

# Convert the array of seats to a JSON array format
seats_json=$(printf '"%s", ' "${seats[@]}")
seats_json="[${seats_json%, }]" # Remove trailing comma and space

# Send the booking request to the server
response=$(curl -s -X POST http://localhost:8080/movies/book_seats \
    -H "Content-Type: application/json" \
    -d "{\"movieName\": \"$movieName\", \"theaterName\": \"$theaterName\", \"seats\": $seats_json}")

# Display the response
echo "Response for '$movieName' in '$theaterName': $response"
