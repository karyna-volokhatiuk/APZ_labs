#!/bin/bash
CONSUL_NAME=services-manager
docker stop "${CONSUL_NAME}"
docker rm "${CONSUL_NAME}"