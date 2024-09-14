#ifndef THEATER_HPP
#define THEATER_HPP

#include <string>
#include <vector>
#include <mutex>

/**
 * @brief Represents a Theater with a set of seats.
 */
class Theater {
public:
    /**
     * @brief Construct a new Theater object.
     * @param name The name of the theater.
     */
    Theater(const std::string& name) : name_(name), seats_(20, true) {}

    // Delete copy constructor and copy assignment operator
    Theater(const Theater&) = delete;
    Theater& operator=(const Theater&) = delete;

    // Implement move constructor and move assignment operator
    /**
     * @brief Move constructor for Theater object.
     * @param other The Theater to move.
     */
    Theater(Theater&& other) noexcept : name_(std::move(other.name_)), seats_(std::move(other.seats_)) {}

    /**
     * @brief Move assignment operator for Theater object.
     * @param other The Theater to move.
     * @return Theater& Reference to this Theater object.
     */
    Theater& operator=(Theater&& other) noexcept {
        if (this != &other) {
            std::lock_guard<std::mutex> lock(seat_mutex_);
            name_ = std::move(other.name_);
            seats_ = std::move(other.seats_);
        }
        return *this;
    }

    /**
     * @brief Get the name of the theater.
     * @return std::string Name of the theater.
     */
    std::string getName() const {
        return name_;
    }

    /**
     * @brief Get a list of available seats.
     * @return std::vector<std::string> List of available seat names.
     */
    std::vector<std::string> getAvailableSeats() const {
        std::vector<std::string> availableSeats;
        for (size_t i = 0; i < seats_.size(); ++i) {
            if (seats_[i]) {
                availableSeats.push_back("A" + std::to_string(i + 1));
            }
        }
        return availableSeats;
    }

    /**
     * @brief Book a set of seats.
     * @param seatNumbers The seats to book.
     * @return true if booking was successful, false otherwise.
     */
    bool bookSeats(const std::vector<std::string>& seatNumbers) {
        std::lock_guard<std::mutex> lock(seat_mutex_);
        for (const auto& seat : seatNumbers) {
            int seatIndex = std::stoi(seat.substr(1)) - 1;
            if (seatIndex < 0 || static_cast<size_t>(seatIndex) >= seats_.size() || !seats_[seatIndex]) {
                return false; // Seat is already booked or invalid
            }
            seats_[seatIndex] = false; // Mark seat as booked
        }
        return true;
    }

private:
    std::string name_;                ///< Name of the theater.
    std::vector<bool> seats_;         ///< Vector representing available seats.
    mutable std::mutex seat_mutex_;   ///< Mutex to protect seat booking operations.
};

#endif // THEATER_HPP
