# syntax=docker/dockerfile:1
FROM debian:bookworm-slim AS build
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake g++ make git ca-certificates \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
ARG HTTPLIB_REF=v0.15.3
RUN git clone --depth 1 --branch "${HTTPLIB_REF}" https://github.com/yhirose/cpp-httplib.git vendor/cpp-httplib
COPY CMakeLists.txt .
COPY src ./src
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j

FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates \
    && rm -rf /var/lib/apt/lists/*
COPY --from=build /app/build/relay /usr/local/bin/relay
ENV GO_SERVICE_URL=http://micro-sample-go:8080
EXPOSE 8080
CMD ["relay"]
