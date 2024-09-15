# Use the latest Alpine image
FROM alpine:latest

# Install required dependencies and Python
RUN apk add --no-cache g++ make cmake libstdc++ libgcc boost-dev python3 py3-pip

# Create a virtual environment for Python packages
RUN python3 -m venv /venv

# Upgrade pip and install Conan inside the virtual environment
RUN /venv/bin/pip install --upgrade pip && \
    /venv/bin/pip install conan

# Set environment variables to use the virtual environment
ENV PATH="/venv/bin:$PATH"

# Set the working directory
WORKDIR /app

# Copy the project files
COPY . .

# Create a Conan default profile
RUN conan profile detect

ENV CONAN_INSTALL=conan_install

# Install dependencies using Conan
RUN conan install . --build=missing -of=$CONAN_INSTALL

# Build the project
RUN make all

# Expose the port
EXPOSE 8080

# Run the application
CMD ["./movie_booking_service"]
