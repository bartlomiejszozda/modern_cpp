#!/bin/bash
set -xeu

docker run -d \
  --network=host \
  --name=modern_cpp_container \
  --entrypoint=/usr/sbin/sshd \
  modern_cpp -D
