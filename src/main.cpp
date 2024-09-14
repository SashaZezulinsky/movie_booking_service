#include <crow.h>
#include "BookingSystem.hpp"

int main() {
    BookingSystem system;
    crow::SimpleApp app;

    // Endpoint to add a movie
    CROW_ROUTE(app, "/add_movie").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || body["movieName"].t() != crow::json::type::String) {
            return crow::response(400, "Invalid request format");
        }

        Movie movie(body["movieName"].s());
        system.addMovie(movie);

        crow::json::wvalue response;
        response["movieId"] = movie.getName();
        response["movieName"] = movie.getName();

        return crow::response(response);
    });

    // Endpoint to add theaters to a movie
    CROW_ROUTE(app, "/add_theaters_to_movie").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || body["movieId"].t() != crow::json::type::String || body["theaters"].t() != crow::json::type::List) {
            return crow::response(400, "Invalid request format");
        }

        std::string movieId = body["movieId"].s();
        std::vector<std::string> theaterNames;
        for (const auto& theaterJson : body["theaters"]) {
            if (theaterJson.t() == crow::json::type::String) {
                theaterNames.push_back(theaterJson.s());
            }
        }

        system.addTheatersToMovie(movieId, theaterNames);
        return crow::response(200, "Theaters added to movie.");
    });

    // View all playing movies
    CROW_ROUTE(app, "/movies")
    ([&system]() {
        crow::json::wvalue movies_json;
        auto movies = system.getMovies();
        int idx = 0;
        for (const auto& movie : movies) {
            crow::json::wvalue movie_info;
            movie_info["movieId"] = movie.getName();
            movie_info["movieName"] = movie.getName();
            movies_json["movies"][idx++] = std::move(movie_info);
        }
        return crow::response(movies_json);
    });

    // Get all theaters showing the selected movie
    CROW_ROUTE(app, "/movies/theaters").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        crow::json::rvalue body = crow::json::load(req.body);
        if (!body || body["movieId"].t() != crow::json::type::String) {
            return crow::response(400, "Invalid request format");
        }

        std::string movieId = body["movieId"].s();
        auto theaters = system.getTheatersForMovie(movieId);

        crow::json::wvalue theaters_json;
        int idx = 0;
        for (const auto& theater : theaters) {
            crow::json::wvalue theater_info;
            theater_info["theaterId"] = theater->getName();
            theater_info["theaterName"] = theater->getName();
            theaters_json["theaters"][idx++] = std::move(theater_info);
        }
        return crow::response(theaters_json);
    });

    // Get available seats for the selected theater and movie
    CROW_ROUTE(app, "/movies/seats").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        crow::json::rvalue body = crow::json::load(req.body);
        if (!body || body["movieId"].t() != crow::json::type::String || body["theaterId"].t() != crow::json::type::String) {
            return crow::response(400, "Invalid request format");
        }

        std::string movieId = body["movieId"].s();
        std::string theaterId = body["theaterId"].s();
        auto availableSeats = system.getAvailableSeats(movieId, theaterId);

        crow::json::wvalue response_json;
        response_json["availableSeats"] = availableSeats;

        return crow::response(response_json);
    });

    // Book one or more available seats for the selected theater and movie
    CROW_ROUTE(app, "/movies/book_seats").methods(crow::HTTPMethod::POST)
    ([&system](const crow::request& req) {
        crow::json::rvalue body = crow::json::load(req.body);
        if (!body || body["movieId"].t() != crow::json::type::String || body["theaterId"].t() != crow::json::type::String || body["seats"].t() != crow::json::type::List) {
            return crow::response(400, "Invalid request format");
        }

        std::string movieId = body["movieId"].s();
        std::string theaterId = body["theaterId"].s();
        std::vector<std::string> seatsToBook;
        for (const auto& seat : body["seats"]) {
            if (seat.t() == crow::json::type::String) {
                seatsToBook.push_back(seat.s());
            }
        }

        bool success = system.bookSeats(movieId, theaterId, seatsToBook);
        if (success) {
            return crow::response(200, "Seats booked successfully.");
        } else {
            return crow::response(400, "Failed to book seats.");
        }
    });

    app.port(8080).multithreaded().run();
}

