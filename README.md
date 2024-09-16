# Movie Booking Service

The **Movie Booking Service** is a REST API designed to handle movie booking operations for theaters. It allows users to add movies, associate them with theaters, view available seats, and book seats for a movie in a specific theater. The project is built using C++ with the Crow framework and utilizes Conan for dependency management. The API exposes multiple endpoints to manage movie-related operations, such as adding movies, listing available theaters, checking seat availability, and booking seats.

## Key Features

- Add movies to the system.
- Associate theaters with movies.
- Check seat availability for specific theaters.
- Book seats for movies.
- Expose a RESTful API for each operation.

## Requirements

- **Conan** for dependency management.
- **C++17** for building the project.
- **Crow** (a modern C++ web framework).
- **Make** for building the project.
- **Docker** (Optional) for running service in a container.

## Project Structure

- `src/` - Contains the main source code for the application.
- `scripts/` - Contains bash scripts for testing the endpoints by simulating various operations such as adding movies, booking seats, etc.
- `conanfile.txt` - Conan file for managing external dependencies like Crow.

## Install Project Dependencies using Conan

To install the project dependencies using Conan, follow these steps:

### Install Conan
   ```bash
   python3 -m pip install --upgrade pip
   python3 -m pip install conan
   conan profile detect
   ```

### Build the Project
   ```bash
    make all
   ```

## Running the Service
Once built, you can run the service using:
```bash
./bin/movie_booking_service
```
or
```
make run
```

The service will start and listen on port 8080.

## Running with Docker
**Build the Docker Image**
   ```bash
   docker build -t movie_booking_service:latest .
   ```
**Run the Docker Container**
   ```bash
   docker run -p 8080:8080 movie_booking_service
   ```
**Run the Docker Container from the Hub**
   ```bash
   docker run -p 8080:8080 zezulinsky/movie_booking_service:latest
   ```

## Testing with Bash Scripts
The `scripts/` folder contains multiple bash scripts to test the API endpoints.

You can use these to interact with the movie booking service.
* `add_movies.sh`: Adds movies to the service.
* `get_movies.sh`: Lists added movies.
* `add_theaters.sh`: Add theaters for movies.
* `get_theaters.sh`: Lists theaters showing a movie.
* `show_available_seats.sh`: Shows available seats for a movie in a theater.
* `book_seats.sh`: Books seats for a movie in a theater.

## Testing API Endpoints
### Add Movies
Use the `add_movies.sh` script to add movies to the service.

This script sends a POST request to the `/add_movie` endpoint to add multiple movies.
   ```bash
    ./scripts/add_movies.sh
   ```

### Get Movies
Use the `get_movies.sh` script to list all the added movies.

This script sends a GET request to the `/movies` endpoint.
   ```bash
    ./scripts/get_movies.sh
   ```

### Add Theaters to Movies
Use the `add_theaters.sh` script to associate theaters with movies.

This script sends a POST request to the `/add_theaters_to_movie` endpoint for each movie.
   ```bash
    ./scripts/add_theaters.sh
   ```

### Get Theaters for a Movie
Use the `get_theaters.sh` script to list all theaters playing a particular movie.

This script sends a POST request to the `/movies/theaters` endpoint.
   ```bash
    ./scripts/get_theaters.sh
   ```

### Show Available Seats
To check available seats in a theater for a specific movie, use the `show_available_seats.sh` script.

It interacts with the `/movies/seats` endpoint
   ```bash
    ./scripts/show_available_seats.sh "Fight Club" "The Rebel Cinema"
   ```

Output:
```bash
Response for 'Fight Club' in 'The Rebel Cinema'
[
  "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10",
  "a11", "a12", "a13", "a14", "a15", "a16", "a17", "a18", "a19", "a20"
]
```

### Book Seats
To book one or more seats for a movie in a particular theater, use the `book_seats.sh` script.

The script sends a POST request to the `/movies/book_seats` endpoint.
   ```bash
   ./scripts/book_seats.sh "Fight Club" "The Rebel Cinema" "a17" "a18"
   ```

Output:
```bash
Response for 'Fight Club' in 'The Rebel Cinema': Seats booked successfully.
```

### Check Available Seats Again
After booking, you can run the `show_available_seats.sh` script again to confirm the booking:

```bash
./scripts/show_available_seats.sh "Fight Club" "The Rebel Cinema"
```

Output:
```bash
Response for 'Fight Club' in 'The Rebel Cinema'
[
  "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10",
  "a11", "a12", "a13", "a14", "a15", "a16", "a19", "a20"
]
```
