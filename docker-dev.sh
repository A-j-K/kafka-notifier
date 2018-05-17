#!/bin/bash

docker build \
	-t kafka-notifier:dev \
	-f Dockerfile.dev \
	.

