#!/bin/bash

./depth < data > save
./triangulate < save > new
./mode < new
