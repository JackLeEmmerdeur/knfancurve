#!/usr/bin/env bash

# Courtesy by Daniel M
# https://stackoverflow.com/a/37102013/3469861

until cd /docker/build && cmake ../src && make
do
    echo "Retrying cmake"
done
