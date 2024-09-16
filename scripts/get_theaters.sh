#!/bin/bash

# Base URL for the movie booking service
BASE_URL="http://localhost:8080"

# Array of movie names
movies=(
    "The Silence of the Lambs"
    "Se7en"
    "Seven Samurai"
    "One Flew Over the Cuckoo's Nest"
    "The Matrix"
    "The Shawshank Redemption"
    "12 Angry Men"
    "The Godfather: Part II"
    "Goodfellas"
    "Forrest Gump"
    "Star Wars: Episode V - The Empire Strikes Back"
    "The Dark Knight"
    "Schindler's List"
    "The Lord of the Rings: The Fellowship of the Ring"
    "The Lord of the Rings: The Return of the King"
    "The Godfather"
    "Pulp Fiction"
    "Inception"
    "The Good, the Bad and the Ugly"
    "Fight Club"
)

# Iterate through the movies to get their theaters
for movie in "${movies[@]}"; do
    # Create a JSON payload for the movie
    json_payload=$(jq -n --arg movieName "$movie" '{"movieName": $movieName}')

    # Send the POST request to get theaters for the movie
    response=$(curl -s -X POST "$BASE_URL/movies/theaters" \
        -H "Content-Type: application/json" \
        -d "$json_payload")

    # Print the formatted response
    echo "$movie"
    echo "$response" | jq '.'
done
