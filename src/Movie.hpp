/**
 * @file Movie.hpp
 * @brief Defines the Movie class representing a movie in the booking system.
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <vector>
#include <memory>

/**
 * @class Theater
 * @brief Forward declaration of Theater class.
 */
class Theater;

/**
 * @class Movie
 * @brief Class representing a movie.
 */
class Movie {
public:
    /**
     * @brief Default constructor.
     */
    Movie() = default;

    /**
     * @brief Constructor with movie name.
     * @param name The name of the movie.
     */
    Movie(const std::string& name) : name_(name) {}

    /**
     * @brief Get the name of the movie.
     * @return The name of the movie.
     */
    std::string getName() const { return name_; }

    /**
     * @brief Add theaters to the movie.
     * @param theaters A vector of shared pointers to Theater objects.
     */
    void addTheaters(const std::vector<std::shared_ptr<Theater>>& theaters) {
        theaters_.insert(theaters_.end(), theaters.begin(), theaters.end());
    }

    /**
     * @brief Get theaters for this movie.
     * @return A vector of shared pointers to Theater objects.
     */
    std::vector<std::shared_ptr<Theater>> getTheaters() const {
        return theaters_;
    }

private:
    std::string name_; ///< The name of the movie.
    std::vector<std::shared_ptr<Theater>> theaters_; ///< The theaters showing this movie.
};

#endif // MOVIE_HPP
