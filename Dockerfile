FROM alpine:latest

# Install required dependencies
RUN apk add --no-cache g++ make cmake libstdc++ libgcc boost-dev

# Install Conan
RUN apk add --no-cache python3 py3-pip && pip3 install conan

WORKDIR /app

# Copy the project files
COPY . .

# Install dependencies using Conan
RUN conan install . --build=missing

# Build the project
RUN make all

# Expose the port
EXPOSE 8080

# Run the application
CMD ["./movie_booking_service"]
