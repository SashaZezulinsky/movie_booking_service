#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include "Theater.hpp"

/**
 * @brief Represents a Movie with a collection of theaters.
 */
class Movie {
public:
    /**
     * @brief Construct a new Movie object.
     * @param name The name of the movie.
     */
    Movie(const std::string& name) : name_(name) {}

    /**
     * @brief Add a list of theaters to the movie.
     * @param theaters Vector of shared pointers to Theater objects.
     */
    void addTheaters(const std::vector<std::shared_ptr<Theater>>& theaters) {
        for (const auto& theater : theaters) {
            theaters_[theater->getName()] = theater;
        }
    }

    /**
     * @brief Get a theater by its ID.
     * @param theaterId The ID (name) of the theater.
     * @return std::shared_ptr<Theater> Shared pointer to the Theater if found, nullptr otherwise.
     */
    std::shared_ptr<Theater> getTheaterById(const std::string& theaterId) const {
        auto it = theaters_.find(theaterId);
        return (it != theaters_.end()) ? it->second : nullptr;
    }

    /**
     * @brief Get all theaters for this movie.
     * @return const std::unordered_map<std::string, std::shared_ptr<Theater>>& Map of theaters.
     */
    const std::unordered_map<std::string, std::shared_ptr<Theater>>& getTheaters() const {
        return theaters_;
    }

    /**
     * @brief Get the movie's name (ID).
     * @return std::string Movie name.
     */
    std::string getName() const {
        return name_;
    }

private:
    std::string name_;                                            ///< Name of the movie.
    std::unordered_map<std::string, std::shared_ptr<Theater>> theaters_; ///< Theaters showing the movie.
};

#endif // MOVIE_HPP
