# syntax=docker/dockerfile:1
FROM golang:1.22-bookworm AS build
WORKDIR /src
COPY go.mod main.go ./
RUN CGO_ENABLED=0 GOOS=linux go build -trimpath -ldflags="-s -w" -o /server .

FROM gcr.io/distroless/static-debian12:nonroot
WORKDIR /
COPY --from=build /server /server
EXPOSE 8080
USER nonroot:nonroot
ENTRYPOINT ["/server"]
