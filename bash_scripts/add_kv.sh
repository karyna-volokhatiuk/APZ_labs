#!/bin/bash
CONSUL_NAME=services-manager

MSG_QUEUE_KEY="msg_queue_name"
MSG_QUEUE_VALUE="my-distributed-key"
docker exec -it "${CONSUL_NAME}" consul kv put "${MSG_QUEUE_KEY}" "${MSG_QUEUE_VALUE}"

MAP_KEY="map_name"
MAP_VALUE="my-distributed-map"
docker exec -it "${CONSUL_NAME}" consul kv put "${MAP_KEY}" "${MAP_VALUE}"