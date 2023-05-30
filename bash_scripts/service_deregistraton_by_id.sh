#!/bin/bash
CONSUL_NAME=services-manager
docker exec -it "${CONSUL_NAME}" consul services deregister -id="${1}"