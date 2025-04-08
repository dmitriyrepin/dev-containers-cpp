# Build a developer's image:
#   docker build -f Dockerfile.cpp --target build -t simple-cpp:dev .
# Run developer's image (Windows):
#   docker run -it --rm -p 8080:8080 --name simple-cpp-dev simple-cpp:dev /bin/bash
#   docker run -it --rm -p 8080:8080 --name simple-cpp-dev -v $pwd/app:/home/ubuntu/app simple-cpp:dev /bin/bash
FROM ubuntu:24.04 AS build

# Install tools
RUN apt update && apt install -y \
    ca-certificates \
    curl \
    wget \
    jq \
    git \
    build-essential \
    gdb \
    cmake
COPY --chmod=755 automation/install_from_github.sh /usr/local/bin/install_from_github.sh

RUN git config --global user.name "Dmitriy Repin" && \
    git config --global user.email "drepin@hotmail.com"

# Install libraries
RUN apt update && apt install -y \
    libfmt-dev

# Install libraries from github
RUN install_from_github.sh "yhirose/cpp-httplib"

# Copy source code
COPY --chown=ubuntu:ubuntu app/ /home/ubuntu/app/
WORKDIR /home/ubuntu/app
RUN cmake --preset=GCC-13.3 && cmake --build /home/ubuntu/out/build/GCC-13.3

USER 1000
EXPOSE 8080

# Build a production image:
#   docker build -f Dockerfile.cpp -t simple-cpp .
# Run the production image (Windows):
#   docker run -d --rm -p 8080:8080 --name simple-cpp simple-cpp
# Debug the production image:
#  docker exec -it simple-cpp /bin/bash
FROM ubuntu:24.04

WORKDIR /home/ubuntu/app
COPY --from=build --chown=ubuntu:ubuntu /home/ubuntu/out/build/GCC-13.3/simple /home/ubuntu/app/simple

USER 1000
EXPOSE 8080

CMD ["/home/ubuntu/app/simple"]