#include "BookingSystem.hpp"  // Include the main BookingSystem class
#include <gtest/gtest.h>
#include <memory>  // For std::shared_ptr
#include <vector>
#include <string>

// Test fixture for BookingSystem
class BookingSystemTest : public ::testing::Test {
protected:
    BookingSystem system;  // The system under test

    void SetUp() override {
        // Add some movies to the system
        system.addMovie(Movie("Inception"));
        system.addMovie(Movie("The Matrix"));

        // Add theaters for testing
        std::vector<std::shared_ptr<Theater>> theaters;
        theaters.push_back(std::make_shared<Theater>("Theater 1"));
        theaters.push_back(std::make_shared<Theater>("Theater 2"));

        system.addTheatersToMovie("Inception", theaters);
    }
};

// Test case for adding theaters to a movie
TEST_F(BookingSystemTest, AddTheatersToMovie) {
    auto theaters = system.getTheatersForMovie("Inception");
    ASSERT_EQ(theaters.size(), 2);
    EXPECT_EQ(theaters[0]->getName(), "Theater 1");
    EXPECT_EQ(theaters[1]->getName(), "Theater 2");
}

// Test case for booking available seats
TEST_F(BookingSystemTest, BookAvailableSeats) {
    std::vector<std::string> seatsToBook = {"a1", "a2"};
    bool success = system.bookSeats("Inception", "Theater 1", seatsToBook);
    EXPECT_TRUE(success);

    // Check that the seats are now booked and unavailable
    auto availableSeats = system.getAvailableSeats("Inception", "Theater 1");
    EXPECT_EQ(availableSeats.size(), 18);  // Assuming total 20 seats
    EXPECT_EQ(std::find(availableSeats.begin(), availableSeats.end(), "a1"), availableSeats.end());
    EXPECT_EQ(std::find(availableSeats.begin(), availableSeats.end(), "a2"), availableSeats.end());
}

// Test case for booking already booked seats
TEST_F(BookingSystemTest, BookAlreadyBookedSeats) {
    std::vector<std::string> seatsToBook = {"a1", "a2"};
    system.bookSeats("Inception", "Theater 1", seatsToBook);

    // Try to book the same seats again
    bool success = system.bookSeats("Inception", "Theater 1", seatsToBook);
    EXPECT_FALSE(success);
}

// Test case for handling invalid seat bookings
TEST_F(BookingSystemTest, BookInvalidSeats) {
    std::vector<std::string> seatsToBook = {"a21"};  // Invalid seat, out of bounds
    bool success = system.bookSeats("Inception", "Theater 1", seatsToBook);
    EXPECT_FALSE(success);
}

// Test case for getting available seats
TEST_F(BookingSystemTest, GetAvailableSeats) {
    auto availableSeats = system.getAvailableSeats("Inception", "Theater 1");
    EXPECT_EQ(availableSeats.size(), 20);  // Assuming total 20 seats

    std::vector<std::string> seatsToBook = {"a1", "a2"};
    system.bookSeats("Inception", "Theater 1", seatsToBook);

    availableSeats = system.getAvailableSeats("Inception", "Theater 1");
    EXPECT_EQ(availableSeats.size(), 18);  // Two seats should now be unavailable
}

// Test case for getting available seats for a movie with no theaters
TEST_F(BookingSystemTest, GetAvailableSeatsNoTheaters) {
    auto availableSeats = system.getAvailableSeats("The Matrix", "Nonexistent Theater");
    EXPECT_TRUE(availableSeats.empty());
}

// Test case for handling invalid inputs
TEST_F(BookingSystemTest, HandleInvalidInput) {
    std::vector<std::shared_ptr<Theater>> emptyTheaters;
    bool result = system.addTheatersToMovie("Nonexistent Movie", emptyTheaters);
    EXPECT_FALSE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
