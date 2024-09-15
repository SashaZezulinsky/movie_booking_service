#include <vector>
#include <string>
#include <iostream>
#include <mutex>

/**
 * @class Theater
 * @brief Represents a theater with a set of seats.
 */
class Theater {
public:
    /**
     * @brief Constructor for Theater.
     * @param name The name of the theater.
     */
    Theater(const std::string& name) : name_(name), seats_(20, true) {} // Initialize with 20 available seats

    /**
     * @brief Get the name of the theater.
     * @return The name of the theater.
     */
    std::string getName() const { return name_; }

    /**
     * @brief Book specified seats in the theater.
     * @param seatsToBook A vector of seat identifiers to book.
     */
    bool bookSeats(const std::vector<std::string>& seatsToBook) {
        std::lock_guard<std::mutex> lock(seat_mutex_); // Lock the mutex for thread safety
        for (const auto& seat : seatsToBook) {
            int index = seat[1] - '1'; // Convert seat name (e.g., "a1") to index (0-19)
            if (index >= 0 && index < seats_.size()) {
                seats_[index] = false; // Mark seat as booked
            } else {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Get a list of available seats in the theater.
     * @return A vector of available seat identifiers.
     */
    std::vector<std::string> getAvailableSeats() const {
        std::lock_guard<std::mutex> lock(seat_mutex_); // Lock the mutex for thread safety
        std::vector<std::string> availableSeats;
        for (size_t i = 0; i < seats_.size(); ++i) {
            if (seats_[i]) {
                // Create a seat identifier (e.g., "a1", "a2", etc.)
                char row = 'a'; // Assume all seats are in row 'a'
                availableSeats.push_back(std::string(1, row) + std::to_string(i + 1));
            }
        }
        return availableSeats;
    }

private:
    std::string name_;                ///< The name of the theater
    std::vector<bool> seats_;         ///< Vector to represent seat availability
    mutable std::mutex seat_mutex_;   ///< Mutex for thread safety on seat operations
};
