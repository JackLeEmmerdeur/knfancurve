#!/usr/bin/env bash

until cd /docker/build && cmake ../src && make
do
    echo "Retrying cmake"
done