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
     * @brief Books one or more seats for the theater.
     * 
     * This function attempts to book the specified seats. It verifies that each seat 
     * is in the correct format (e.g., "a1", "a2", ..., "a20") and checks that the 
     * seat is available for booking. The function locks the seat mutex to ensure 
     * thread safety during the booking process.
     *
     * @param seats A vector of strings representing the seat names to be booked.
     *              Each seat name must be in the format of "aX", where X is a 
     *              number from 1 to 20.
     *
     * @return true if all specified seats were successfully booked; false if any 
     *         seat is invalid, already booked, or out of bounds.
     */
    bool bookSeats(const std::vector<std::string>& seats) {
        std::lock_guard<std::mutex> lock(seat_mutex_); // Lock the mutex to prevent race conditions

        for (const auto& seat : seats) {
            // Ensure the seat name is in the correct format (e.g., "a1", "a2", ..., "a20")
            if (seat.size() < 2 || seat[0] != 'a') {
                return false; // Invalid seat name
            }

            // Convert the remaining characters to a number
            size_t seatIndex = std::stoi(seat.substr(1)); // Convert the substring starting from index 1

            // Validate the seat index (1 to 20)
            if (seatIndex < 1 || seatIndex > 20) {
                return false; // Seat index is out of bounds
            }

            // Convert to zero-based index for booking
            seatIndex -= 1;

            // Check if the seat is already booked
            if (!seats_[seatIndex]) {
                return false; // Seat is already booked
            }

            seats_[seatIndex] = false; // Book the seat
        }
        return true; // Successfully booked all seats
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
