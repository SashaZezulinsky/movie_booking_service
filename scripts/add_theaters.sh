#!/bin/bash

# List of movies and associated theaters
declare -A movies_and_theaters
movies_and_theaters=(
  ["The Silence of the Lambs"]='["The Grand Theater", "Cinema Paradiso", "The Regal"]'
  ["Se7en"]='["The Fox Theater", "Cineplex", "The Landmark"]'
  ["Seven Samurai"]='["The Village East", "The Alamo Drafthouse"]'
  ["One Flew Over the Cuckoo's Nest"]='["The State Theatre", "The Old Town"]'
  ["The Matrix"]='["IMAX Theater", "The Dolby"]'
  ["The Shawshank Redemption"]='["The Modern Art", "The Bijou"]'
  ["12 Angry Men"]='["The People Cinema", "The Old School"]'
  ["The Godfather: Part II"]='["The Ambassador", "The Picture House"]'
  ["Goodfellas"]='["The Silver Screen", "The Dream Theater"]'
  ["Forrest Gump"]='["The Main Street Cinema", "The Loft"]'
  ["Star Wars: Episode V - The Empire Strikes Back"]='["The Galaxy Theater", "Starlight Cinema"]'
  ["The Dark Knight"]='["The Batcave Cinema", "The Cinematic Experience"]'
  ["Schindler List"]='["The Art House", "The History Theater"]'
  ["The Lord of the Rings: The Fellowship of the Ring"]='["The Middle-Earth Cinema", "The Elven Theater"]'
  ["The Lord of the Rings: The Return of the King"]='["The Hobbiton Theater", "The Shire Cinema"]'
  ["The Godfather"]='["The Vito Corleone Theater", "The Family Cinema"]'
  ["Pulp Fiction"]='["The Reservoir Dogs Theater", "The Fiction Lounge"]'
  ["Inception"]='["The Dreamscape Theater", "The Mind Bender"]'
  ["The Good, the Bad and the Ugly"]='["The Wild West Theater", "The Cowboy Cinema"]'
  ["Fight Club"]='["The Underground Theater", "The Rebel Cinema"]'
)

# Loop through each movie and send a request to add theaters
for movie in "${!movies_and_theaters[@]}"; do
  theaters="${movies_and_theaters[$movie]}"
  response=$(curl -s -X POST http://localhost:8080/add_theaters_to_movie \
    -H "Content-Type: application/json" \
    -d "{\"movieName\": \"$movie\", \"theaters\": $theaters}")
  echo "Adding theaters to movie: $movie"
  echo "Response: $response"
done

