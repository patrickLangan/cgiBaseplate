#!/bin/bash
spawn-fcgi -p 8000 -n post &
spawn-fcgi -p 8001 -n upload &

