#include <crow.h>
#include "BookingSystem.hpp"

/**
 * @file main.cpp
 * @brief Main entry point for the movie booking service.
 */

int main() {
    BookingSystem system; ///< The booking system instance.
    crow::SimpleApp app;  ///< The Crow application instance.

    // Endpoint to add a movie
    CROW_ROUTE(app, "/add_movie").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || body["movieName"].s() == "") { // Check if movieName exists and is non-empty
            return crow::response(400, "Invalid request format");
        }

        Movie movie(body["movieName"].s()); // Create a movie object
        system.addMovie(movie); // Add movie to the booking system

        crow::json::wvalue response;
        response["movieName"] = movie.getName(); // Respond with the movie name

        return crow::response(response);
    });

    // Endpoint to add theaters to a movie
    CROW_ROUTE(app, "/add_theaters_to_movie").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || body["movieName"].s() == "" || body["theaters"].t() != crow::json::type::List) {
            return crow::response(400, "Invalid request format");
        }

        std::string movieName = body["movieName"].s();
        std::vector<std::shared_ptr<Theater>> theaters; // Changed to store shared pointers
        for (const auto& theaterJson : body["theaters"]) {
            if (theaterJson.t() == crow::json::type::String) {
                // Create a new Theater object and store it as a shared pointer
                theaters.push_back(std::make_shared<Theater>(theaterJson.s()));
            }
        }

        system.addTheatersToMovie(movieName, theaters);

        // Prepare the response
        crow::json::wvalue response;
        response["movieName"] = movieName; // Respond with the movie name
        response["theaters"] = crow::json::wvalue::list(); // Create a JSON array for theaters

        size_t index = 0; // Index for the JSON array
        for (const auto& theater : theaters) {
            response["theaters"][index++] = theater->getName(); // Use array indexing to add theater names
        }

        return crow::response(response); // Respond with the movie name and array of theaters
    });

    // View all playing movies
    CROW_ROUTE(app, "/movies")
    ([&system]() {
        crow::json::wvalue movies_json = crow::json::wvalue::list(); // Create a JSON array for movies
        auto movies = system.getMovies();
        size_t index = 0; // Index for the JSON array
        for (const auto& movie : movies) {
            crow::json::wvalue movie_info;
            movie_info["movieName"] = movie->getName(); // Respond with the movie name
            movies_json[index++] = std::move(movie_info); // Use array indexing to add movie_info to movies_json
        }
        return crow::response(movies_json); // Respond with the list of movies as an array
    });

    // Get all theaters showing the selected movie
    CROW_ROUTE(app, "/movies/theaters").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        crow::json::rvalue body = crow::json::load(req.body);
        if (!body || body["movieName"].s() == "") {
            return crow::response(400, "Invalid request format");
        }

        std::string movieName = body["movieName"].s();
        auto theaters = system.getTheatersForMovie(movieName);

        crow::json::wvalue theaters_json = crow::json::wvalue::list(); // Create a JSON array for theaters
        size_t index = 0; // Index for the JSON array
        for (const auto& theater : theaters) {
            crow::json::wvalue theater_info;
            theater_info["theaterName"] = theater->getName(); // Respond with the theater name
            theaters_json[index++] = std::move(theater_info); // Use array indexing to add theater_info to theaters_json
        }
        return crow::response(theaters_json); // Respond with the list of theaters
    });

    // Get available seats for the selected theater and movie
    CROW_ROUTE(app, "/movies/seats").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        crow::json::rvalue body = crow::json::load(req.body);
        if (!body || body["movieName"].s() == "" || body["theaterName"].s() == "") {
            return crow::response(400, "Invalid request format");
        }

        std::string movieName = body["movieName"].s();
        std::string theaterName = body["theaterName"].s();
        // Placeholder for getting available seats logic
        // This should ideally be implemented in the Theater class.
        crow::json::wvalue response_json;
        response_json["availableSeats"] = {}; // Replace with actual available seats

        return crow::response(response_json); // Respond with available seats
    });

    // Book one or more available seats for the selected theater and movie
    CROW_ROUTE(app, "/movies/book_seats").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        crow::json::rvalue body = crow::json::load(req.body);
        if (!body || body["movieName"].s() == "" || body["theaterName"].s() == "" || body["seats"].t() != crow::json::type::List) {
            return crow::response(400, "Invalid request format");
        }

        std::string movieName = body["movieName"].s();
        std::string theaterName = body["theaterName"].s();
        std::vector<std::string> seatsToBook;
        for (const auto& seat : body["seats"]) {
            if (seat.t() == crow::json::type::String) {
                seatsToBook.push_back(seat.s());
            }
        }

        bool success = system.bookSeats(movieName, theaterName, seatsToBook); // Attempt to book seats
        if (success) {
            return crow::response(200, "Seats booked successfully.");
        } else {
            return crow::response(400, "Failed to book seats.");
        }
    });

    app.port(8080).multithreaded().run(); // Start the server
}
