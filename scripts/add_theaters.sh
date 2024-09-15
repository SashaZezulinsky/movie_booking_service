#!/bin/bash

# Base URL for the movie booking service
BASE_URL="http://localhost:8080"

# Movies and their corresponding theaters
declare -A movie_theaters=(
    ["The Silence of the Lambs"]="Cineplex, Regal Cinemas, AMC Theatres"
    ["Se7en"]="Cinemark, Landmark Theatres, Alamo Drafthouse"
    ["Seven Samurai"]="ArcLight, Landmark Theatres, AMC Theatres"
    ["One Flew Over the Cuckoo's Nest"]="Regal Cinemas, Cineworld, Cineplex"
    ["The Matrix"]="Cinemark, AMC Theatres, Alamo Drafthouse"
    ["The Shawshank Redemption"]="Regal Cinemas, Landmark Theatres, AMC Theatres"
    ["12 Angry Men"]="Cineplex, Cineworld, Regal Cinemas"
    ["The Godfather: Part II"]="AMC Theatres, Alamo Drafthouse, Landmark Theatres"
    ["Goodfellas"]="Cinemark, Cineworld, Regal Cinemas"
    ["Forrest Gump"]="Regal Cinemas, AMC Theatres, Cineworld"
    ["Star Wars: Episode V - The Empire Strikes Back"]="Cineworld, AMC Theatres, Alamo Drafthouse"
    ["The Dark Knight"]="Cinemark, Regal Cinemas, Landmark Theatres"
    ["Schindler's List"]="AMC Theatres, Alamo Drafthouse, Cineplex"
    ["The Lord of the Rings: The Fellowship of the Ring"]="Cineworld, Regal Cinemas, AMC Theatres"
    ["The Lord of the Rings: The Return of the King"]="Regal Cinemas, Landmark Theatres, Alamo Drafthouse"
    ["The Godfather"]="Cinemark, AMC Theatres, Cineplex"
    ["Pulp Fiction"]="Cineworld, Alamo Drafthouse, Regal Cinemas"
    ["Inception"]="AMC Theatres, Cineplex, Landmark Theatres"
    ["The Good, the Bad and the Ugly"]="Regal Cinemas, Cineworld, Alamo Drafthouse"
    ["Fight Club"]="Cinemark, AMC Theatres, Landmark Theatres"
)

# Iterate through the movies and their corresponding theaters
for movie in "${!movie_theaters[@]}"; do
    theaters="${movie_theaters[$movie]}"
    
    # Create a JSON payload for the theaters
    json_theaters=$(echo "$theaters" | jq -R -s 'split(", ") | map({theaterName: .})')
    
    # Send the POST request to add theaters to the movie
    echo "Adding theaters to movie: $movie"
    response=$(curl -s -X POST "$BASE_URL/add_theaters_to_movie" \
        -H "Content-Type: application/json" \
        -d "{\"movieName\":\"$movie\", \"theaters\":$json_theaters}")
    
    echo "Response: $response"
done
