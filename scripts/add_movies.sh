#!/bin/bash

# Define the endpoint URL
URL="http://localhost:8080/add_movie"

# Array of top 20 movies
MOVIES=("The Shawshank Redemption" \
        "The Godfather" \
        "The Dark Knight" \
        "The Godfather: Part II" \
        "12 Angry Men" \
        "Schindler's List" \
        "The Lord of the Rings: The Return of the King" \
        "Pulp Fiction" \
        "The Good, the Bad and the Ugly" \
        "Fight Club" \
        "Forrest Gump" \
        "Inception" \
        "The Lord of the Rings: The Fellowship of the Ring" \
        "Star Wars: Episode V - The Empire Strikes Back" \
        "The Matrix" \
        "Goodfellas" \
        "One Flew Over the Cuckoo's Nest" \
        "Seven Samurai" \
        "Se7en" \
        "The Silence of the Lambs")

# Loop through the movies and send POST requests
for MOVIE in "${MOVIES[@]}"; do
    echo "Adding movie: $MOVIE"
    
    # Send POST request and capture full response
    RESPONSE=$(curl -s -X POST "$URL" -H "Content-Type: application/json" \
        -d "{\"movieName\": \"$MOVIE\"}")

    # Echo the full response
    echo "Response: $RESPONSE"
    echo "------------------------------------"
done
