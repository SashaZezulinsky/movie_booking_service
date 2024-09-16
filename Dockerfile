FROM alpine:latest

# Install required dependencies including Linux kernel headers and build tools
RUN apk add --no-cache g++ make cmake libstdc++ libgcc python3 py3-pip linux-headers build-base

# Set up a Python virtual environment and install Conan
RUN python3 -m venv /venv
RUN /venv/bin/pip install --upgrade pip && /venv/bin/pip install conan

# Add the virtual environment to the PATH
ENV PATH="/venv/bin:$PATH"

# Set the working directory
WORKDIR /app

# Copy the project files
COPY . .

# Detect Conan profile
RUN conan profile detect

# Install Conan dependencies
RUN conan install . --build=missing -of=conan_install

# Build the project
RUN make all

# Expose the service port
EXPOSE 8080

# Run the service
CMD ["./bin/movie_booking_service"]
