# Default: build images and push to Docker Hub (requires `docker login`).
REGISTRY ?= docker.io/mikeodigos
TAG ?= latest

RUST_IMAGE := $(REGISTRY)/micro-sample-rust
CPP_IMAGE := $(REGISTRY)/micro-sample-cpp
GO_IMAGE := $(REGISTRY)/micro-sample-go

.PHONY: push build build-rust build-cpp build-go

.DEFAULT_GOAL := push

push: build
	docker push $(RUST_IMAGE):$(TAG)
	docker push $(CPP_IMAGE):$(TAG)
	docker push $(GO_IMAGE):$(TAG)

build: build-rust build-cpp build-go

build-rust:
	docker build -t $(RUST_IMAGE):$(TAG) ./rust-client

build-cpp:
	docker build -t $(CPP_IMAGE):$(TAG) ./cpp-relay

build-go:
	docker build -t $(GO_IMAGE):$(TAG) ./go-server
