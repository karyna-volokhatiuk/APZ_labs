#!/bin/bash
CONSUL_NAME=services-manager

#https://developer.hashicorp.com/consul/tutorials/day-0/docker-container-agents
docker run \
    -p 8500:8500 \
    -p 8600:8600/udp \
    --name="${CONSUL_NAME}" \
    consul agent -server -ui -node=server-1 -bootstrap-expect=1 -client=0.0.0.0