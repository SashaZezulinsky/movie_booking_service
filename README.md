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

## Install Dependencies

To install the project dependencies using Conan, follow these steps:

### Install Conan
   ```bash
   python3 -m pip install --upgrade pip
   python3 -m pip install conan
   conan profile detect
   ```

## Building the Project

### Command to build a service
   ```bash
    make all
   ```

## Running the Service

### Run binary
```bash
./bin/movie_booking_service
```

### Run Makefile
```
make run
```

The service will start and listen on port 8080.

## Running with Docker
### Build the image
   ```bash
   docker build -t movie_booking_service:latest .
   ```
### Run the container
   ```bash
   docker run -p 8080:8080 movie_booking_service
   ```
### Run the container from the Docker Hub
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

## How can I test a service?
### Add Movies
Use the `add_movies.sh` script to add movies to the service.

This script sends a POST request to the `/add_movie` endpoint to add multiple movies.

#### Example
   ```bash
    ./scripts/add_movies.sh
   ```

#### Output
```bash
Adding movie: The Godfather
Response: {"movieName":"The Godfather"}
------------------------------------
Adding movie: Schindler's List
Response: {"movieName":"Schindler's List"}
------------------------------------
Adding movie: Pulp Fiction
Response: {"movieName":"Pulp Fiction"}
------------------------------------
Adding movie: Fight Club
Response: {"movieName":"Fight Club"}
------------------------------------
```

### Get Movies
Use the `get_movies.sh` script to list all the added movies.

This script sends a GET request to the `/movies` endpoint.

#### Example
   ```bash
    ./scripts/get_movies.sh
   ```

#### Output
```json
[
  {
    "movieName": "The Godfather"
  },
  {
    "movieName": "Schindler's List"
  },
  {
    "movieName": "Pulp Fiction"
  },
  {
    "movieName": "Fight Club"
  }
]
```

### Add Theaters to Movies
Use the `add_theaters.sh` script to associate theaters with movies.

This script sends a POST request to the `/add_theaters_to_movie` endpoint for each movie.

#### Example
   ```bash
    ./scripts/add_theaters.sh
   ```

#### Output
```bash
Adding theaters to movie: Fight Club
Response: Theaters added for a movie
Adding theaters to movie: The Godfather
Response: Theaters added for a movie
Adding theaters to movie: Schindler List
Response: Theaters added for a movie
Adding theaters to movie: Pulp Fiction
Response: Theaters added for a movie
```

### Get Theaters for a Movie
Use the `get_theaters.sh` script to list all theaters playing a particular movie.

This script sends a POST request to the `/movies/theaters` endpoint.

#### Example
   ```bash
    ./scripts/get_theaters.sh
   ```

#### Output
```bash
Schindler's List
[]
The Godfather
[
  {
    "theaterName": "The Vito Corleone Theater"
  },
  {
    "theaterName": "The Family Cinema"
  }
]
Pulp Fiction
[
  {
    "theaterName": "The Reservoir Dogs Theater"
  },
  {
    "theaterName": "The Fiction Lounge"
  }
]
Fight Club
[
  {
    "theaterName": "The Underground Theater"
  },
  {
    "theaterName": "The Rebel Cinema"
  }
]
```

### Show Available Seats
To check available seats in a theater for a specific movie, use the `show_available_seats.sh` script.

It interacts with the `/movies/seats` endpoint
   
#### Example
   ```bash
    ./scripts/show_available_seats.sh "Fight Club" "The Rebel Cinema"
   ```

#### Output
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
   
#### Example
   ```bash
   ./scripts/book_seats.sh "Fight Club" "The Rebel Cinema" "a17" "a18"
   ```

#### Output
```bash
Response for 'Fight Club' in 'The Rebel Cinema': Seats booked successfully.
```

### Check Available Seats Again
After booking, you can run the `show_available_seats.sh` script again to confirm the booking:

#### Example
```bash
./scripts/show_available_seats.sh "Fight Club" "The Rebel Cinema"
```

#### Output
```bash
Response for 'Fight Club' in 'The Rebel Cinema'
[
  "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10",
  "a11", "a12", "a13", "a14", "a15", "a16", "a19", "a20"
]
```

## Available Endpoints
### 1. Add a Movie
- **Endpoint:** `/add_movie`
- **Method:** `POST`
- **Request:**
  ```json
  { "movieName": "The Matrix" }
  ```
- **Response:**
  ```json
  { "movieName": "The Matrix" }
  ```
### 2. List All Movies
- **Endpoint**: `/movies`
- **Method**: GET
- **Description**: Retrieves a list of all movies available in the system.
- **Response**:
  ```json
  [
    { "movieName": "The Matrix" },
    { "movieName": "Inception" }
  ]
  ```

### 3. Add Theaters to a Movie
**Endpoint**: `/add_theaters_to_movie`
**Method**: POST
**Description**: Adds one or more theaters to a specified movie.
**Request body**: 
  ```json
  {
    "movieName": "The Matrix",
    "theaters": ["Theater 1", "Theater 2", "Theater 3"]
  }
  ```
**Response**:
  ```json
  {
    "movieName": "The Matrix",
    "theaters": [
      {
        "theaterName": "Theater 1"
      },
      {
        "theaterName": "Theater 2"
      },
      {
        "theaterName": "Theater 3"
      }
    ]
  }
  ```

