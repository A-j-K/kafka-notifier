#!/bin/bash

VERSION=$(grep VERSION main/version.h | awk '{print $3}' | tr -d /\"//)

docker build \
	-t kafka-notifier:rel-v${VERSION} \
	-f Dockerfile.rel \
	.

echo "docker login"
echo "docker tag kafka-notifier:rel-v${VERSION} andykirkham/kafka-notifier:v${VERSION}"
echo "docker push andykirkham/kafka-notifier:v${VERSION}"


