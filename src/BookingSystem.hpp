/**
 * @file BookingSystem.hpp
 * @brief Defines the BookingSystem class for managing movies and theaters.
 */

#ifndef BOOKING_SYSTEM_HPP
#define BOOKING_SYSTEM_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <mutex>
#include "Movie.hpp"
#include "Theater.hpp"

/**
 * @class BookingSystem
 * @brief Class managing the movie booking system.
 */
class BookingSystem {
public:
    /**
     * @brief Add a movie to the system.
     * @param movie The movie to add.
     */
    void addMovie(const Movie& movie) {
        std::lock_guard<std::mutex> lock(movies_mutex_); // Lock the mutex for thread safety
        movies_[movie.getName()] = std::make_shared<Movie>(movie);
    }

    /**
     * @brief Add theaters to a specific movie.
     * @param movieName The name of the movie.
     * @param theaters A vector of shared pointers to Theater objects.
     */
    bool addTheatersToMovie(const std::string& movieName, const std::vector<std::shared_ptr<Theater>>& theaters) {
        std::lock_guard<std::mutex> lock(movies_mutex_); // Lock the mutex for thread safety
        auto it = movies_.find(movieName);
        if (it != movies_.end()) {
            it->second->addTheaters(theaters);
            return true;
        }
        return false;
    }

    /**
     * @brief Get all movies.
     * @return A vector of shared pointers to all movies.
     */
    std::vector<std::shared_ptr<Movie>> getMovies() const {
        std::lock_guard<std::mutex> lock(movies_mutex_); // Lock the mutex for thread safety
        std::vector<std::shared_ptr<Movie>> allMovies;
        for (const auto& pair : movies_) {
            allMovies.push_back(pair.second);
        }
        return allMovies;
    }

    /**
     * @brief Get theaters showing a specific movie.
     * @param movieName The name of the movie.
     * @return A vector of shared pointers to theaters showing the movie.
     */
    std::vector<std::shared_ptr<Theater>> getTheatersForMovie(const std::string& movieName) const {
        std::lock_guard<std::mutex> lock(movies_mutex_); // Lock the mutex for thread safety
        auto it = movies_.find(movieName);
        if (it != movies_.end()) {
            return it->second->getTheaters();
        }
        return {}; // Return empty vector if movie not found
    }

    /**
     * @brief Book seats for a specific movie and theater.
     * @param movieName The name of the movie.
     * @param theaterName The name of the theater.
     * @param seatsToBook A vector of seat indices to book.
     * @return True if seats are successfully booked, false otherwise.
     */
    bool bookSeats(const std::string& movieName, const std::string& theaterName, const std::vector<std::string>& seatsToBook) {
        auto theaters = getTheatersForMovie(movieName);
        std::lock_guard<std::mutex> lock(movies_mutex_); // Lock the mutex for thread safety
        for (const auto& theater : theaters) {
            if (theater->getName() == theaterName) {
                return theater->bookSeats(seatsToBook);
            }
        }
        return false; // Theater not found
    }

    /**
     * @brief Retrieves a list of available seats for a given movie and theater.
     * 
     * @param movieName The name of the movie.
     * @param theaterName The name of the theater.
     * 
     * @return A vector of available seat identifiers. Returns an empty vector if the movie or theater is not found.
     */
    std::vector<std::string> getAvailableSeats(const std::string& movieName, const std::string& theaterName) const {
        auto theaters = getTheatersForMovie(movieName);
        std::lock_guard<std::mutex> lock(movies_mutex_); // Lock the mutex for thread safety
        for (const auto& theater : theaters) {
            if (theater->getName() == theaterName) {
                return theater->getAvailableSeats();
            }
        }
        return {};
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Movie>> movies_; ///< Map of movies by name.
    mutable std::mutex movies_mutex_; ///< Mutex for synchronizing access to movies.
};

#endif // BOOKING_SYSTEM_HPP
