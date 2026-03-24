# syntax=docker/dockerfile:1
FROM rust:1.85-bookworm AS build
WORKDIR /app
COPY Cargo.toml Cargo.lock ./
COPY src ./src
RUN cargo build --release

FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates \
    && rm -rf /var/lib/apt/lists/*
COPY --from=build /app/target/release/micro_rust /usr/local/bin/micro_rust
ENV CPP_SERVICE_URL=http://micro-sample-cpp:8080
CMD ["micro_rust"]
