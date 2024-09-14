#ifndef BOOKINGSYSTEM_HPP
#define BOOKINGSYSTEM_HPP

#include <vector>
#include <string>
#include "Movie.hpp"

/**
 * @brief Booking system to manage movies and theaters.
 */
class BookingSystem {
public:
    /**
     * @brief Add a movie to the system.
     * @param movie The Movie object.
     */
    void addMovie(const Movie& movie) {
        movies_.push_back(movie);
    }

    /**
     * @brief Add theaters to a specific movie.
     * @param movieId The ID of the movie.
     * @param theaterNames A list of theater names to add to the movie.
     */
    void addTheatersToMovie(const std::string& movieId, const std::vector<std::string>& theaterNames) {
        auto movie = getMovieById(movieId);
        if (movie) {
            std::vector<std::shared_ptr<Theater>> theaters;
            for (const auto& name : theaterNames) {
                theaters.push_back(std::make_shared<Theater>(name));
            }
            movie->addTheaters(theaters);
        }
    }

    /**
     * @brief Get all movies in the system.
     * @return std::vector<Movie> List of movies.
     */
    std::vector<Movie> getMovies() const {
        return movies_;
    }

    /**
     * @brief Get a list of theaters for a specific movie.
     * @param movieId The ID of the movie.
     * @return std::vector<std::shared_ptr<Theater>> List of theaters showing the movie.
     */
    std::vector<std::shared_ptr<Theater>> getTheatersForMovie(const std::string& movieId) const {
        auto movie = getMovieById(movieId);
        if (movie) {
            std::vector<std::shared_ptr<Theater>> theaters;
            for (const auto& [name, theater] : movie->getTheaters()) {
                theaters.push_back(theater);
            }
            return theaters;
        }
        return {};
    }

    /**
     * @brief Get available seats for a specific theater of a movie.
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     * @return std::vector<std::string> List of available seat names.
     */
    std::vector<std::string> getAvailableSeats(const std::string& movieId, const std::string& theaterId) const {
        auto movie = getMovieById(movieId);
        if (movie) {
            auto theater = movie->getTheaterById(theaterId);
            if (theater) {
                return theater->getAvailableSeats();
            }
        }
        return {};
    }

    /**
     * @brief Book seats for a specific movie and theater.
     * @param movieId The ID of the movie.
     * @param theaterId The ID of the theater.
     * @param seatNumbers The seats to book.
     * @return true if the booking was successful, false otherwise.
     */
    bool bookSeats(const std::string& movieId, const std::string& theaterId, const std::vector<std::string>& seatNumbers) {
        auto movie = getMovieById(movieId);
        if (movie) {
            auto theater = movie->getTheaterById(theaterId);
            if (theater) {
                return theater->bookSeats(seatNumbers);
            }
        }
        return false;
    }

private:
    /**
     * @brief Find a movie by its ID.
     * @param movieId The ID of the movie.
     * @return Movie* Pointer to the movie, or nullptr if not found.
     */
    Movie* getMovieById(const std::string& movieId) {
        for (auto& movie : movies_) {
            if (movie.getName() == movieId) {
                return &movie;
            }
        }
        return nullptr;
    }

    /**
     * @brief Find a movie by its ID (const version).
     * @param movieId The ID of the movie.
     * @return const Movie* Pointer to the movie, or nullptr if not found.
     */
    const Movie* getMovieById(const std::string& movieId) const {
        for (const auto& movie : movies_) {
            if (movie.getName() == movieId) {
                return &movie;
            }
        }
        return nullptr;
    }

    std::vector<Movie> movies_; ///< List of movies in the booking system.
};

#endif // BOOKINGSYSTEM_HPP
