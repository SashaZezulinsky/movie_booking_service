# Movie Booking Service

## Overview

This project is a simple movie booking service built using C++ and [Crow](https://crowcpp.org/), a lightweight web framework for C++. It allows users to add movies, theaters, book seats, and check seat availability.

## Requirements

- **Conan**: For managing C++ dependencies.
- **G++**: A C++ compiler.
- **Make**: A build tool.
- **Docker** (Optional): For running the service in a container.

## Installation

1. **Install Conan**: 

   ```bash
   python3 -m pip install --upgrade pip
   python3 -m pip install conan
   ```
2. **Build the Project**:

   ```bash
    make all
   ```

## Running the Service
Once built, you can run the service using:

   ```bash
    ./bin/movie_booking_service
   ```

    or

   ```bash
   make run
   ```
The service will start and listen on port 8080.

## API Endpoints
1. **Add Movies**
Use the add_movies.sh script to add movies to the service.
This script sends a POST request to the /add_movie endpoint to add multiple movies.
   ```bash
    ./scripts/add_movies.sh
   ```

2. **Get Movies**
Use the get_movies.sh script to list all the added movies. This script sends a GET request to the /movies endpoint.
   ```bash
    ./scripts/get_movies.sh
   ```

3. **Add Theaters to Movies**
Use the add_theaters.sh script to associate theaters with movies. This script sends a POST request to the /add_theaters_to_movie endpoint for each movie.
   ```bash
    ./scripts/add_theaters.sh
   ```

4. **Get Theaters for a Movie**
Use the get_theaters.sh script to list all theaters playing a particular movie. This script sends a POST request to the /movies/theaters endpoint.
   ```bash
    ./scripts/get_theaters.sh
   ```

5. **Show Available Seats**
To check available seats in a theater for a specific movie, use the show_available_seats.sh script.
   ```bash
    ./scripts/show_available_seats.sh "Fight Club" "The Rebel Cinema"
   ```

*Example Response*:
```bash
Response for 'Fight Club' in 'The Rebel Cinema'
[
  "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10",
  "a11", "a12", "a13", "a14", "a15", "a16", "a17", "a18", "a19", "a20"
]
```

6. **Book Seats**
To book one or more seats for a movie in a particular theater, use the book_seats.sh script. The script sends a POST request to the /movies/book_seats endpoint.

   ```bash
   ./scripts/book_seats.sh "Fight Club" "The Rebel Cinema" "a17" "a18"
   ```

*Example Response*:

```bash
Response for 'Fight Club' in 'The Rebel Cinema': Seats booked successfully.
```

7. **Check Available Seats Again**
After booking, you can run the show_available_seats.sh script again to confirm the booking:

```bash
./scripts/show_available_seats.sh "Fight Club" "The Rebel Cinema"
```

*Example Response*:

```bash
Response for 'Fight Club' in 'The Rebel Cinema'
[
  "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10",
  "a11", "a12", "a13", "a14", "a15", "a16", "a19", "a20"
]
```

## Running with Docker
**Build the Docker Image**
   ```bash
    docker build -t movie_booking_service:latest .
   ```

**Run the Docker Container**
   ```bash
docker run -p 8080:8080 movie_booking_service
   ```

*Running a docker container from Docker Hub*
   ```bash
docker run -p 8080:8080 zezulinsky/movie_booking_service:latest
   ```

## Testing with Bash Scripts
The ```scripts/``` folder contains multiple bash scripts to test the API endpoints. You can use these to interact with the movie booking service.
+```add_movies.sh```: Adds movies to the service.
+```get_movies.sh```: Lists added movies.
+```add_theaters.sh```: Populates theaters for movies.
+```get_theaters.sh```: Lists theaters showing a movie.
+```show_available_seats.sh```: Shows available seats for a movie in a theater.
+```book_seats.sh```: Books seats for a movie in a theater.
