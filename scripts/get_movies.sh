#!/bin/bash

# URL of the movie booking service
URL="http://localhost:8080/movies"

# Send a GET request to the /movies endpoint
response=$(curl -s -X GET "$URL")

# Check if the response is not empty
if [ -z "$response" ]; then
    echo "No movies found or there was an error in the request."
else
    # Print the formatted JSON response
    echo "Response from the server:"
    echo "$response" | jq '.'  # Format the JSON response with jq
fi
