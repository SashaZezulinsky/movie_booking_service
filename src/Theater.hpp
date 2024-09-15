/**
 * @file Theater.hpp
 * @brief Defines the Theater class representing a theater in the booking system.
 */

#ifndef THEATER_HPP
#define THEATER_HPP

#include <string>
#include <vector>
#include <mutex>

/**
 * @class Theater
 * @brief Class representing a theater.
 */
class Theater {
public:
    /**
     * @brief Default constructor.
     */
    Theater() = default;

    /**
     * @brief Constructor with theater name.
     * @param name The name of the theater.
     */
    Theater(const std::string& name) : name_(name), seats_(20, true) {} // Assuming 20 seats available

    /**
     * @brief Get the name of the theater.
     * @return The name of the theater.
     */
    std::string getName() const { return name_; }

    /**
     * @brief Book seats in the theater.
     * @param seatIndices A vector of seat indices to book.
     * @return True if booking is successful, false otherwise.
     */
    bool bookSeats(const std::vector<std::string>& seatIndices) {
        std::lock_guard<std::mutex> lock(seat_mutex_); // Lock the mutex for thread safety
        for (const auto& seatIndex : seatIndices) {
            unsigned int index = std::stoi(seatIndex); // Convert string index to unsigned int
            if (index >= seats_.size() || !seats_[index]) {
                return false; // Invalid index or seat already booked
            }
            seats_[index] = false; // Mark seat as booked
        }
        return true; // Booking successful
    }

private:
    std::string name_; ///< The name of the theater.
    std::vector<bool> seats_; ///< Availability of seats (true if available).
    mutable std::mutex seat_mutex_; ///< Mutex for synchronizing access to seats.
};

#endif // THEATER_HPP
