#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <movieName> <theaterName>"
  exit 1
fi

MOVIE_NAME="$1"
THEATER_NAME="$2"

# Send a request to get available seats
response=$(curl -s -X POST http://localhost:8080/movies/seats \
  -H "Content-Type: application/json" \
  -d "{\"movieName\": \"$MOVIE_NAME\", \"theaterName\": \"$THEATER_NAME\"}")

# Display the response
echo "Response for '$MOVIE_NAME' in '$THEATER_NAME'"
echo "$response" | jq '.'
