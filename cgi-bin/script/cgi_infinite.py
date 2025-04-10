#!/usr/bin/env python3
import time

print("Content-Type: text/plain\r\n\r\n", flush=True)

while True:
    print("Bloqué...", flush=True)
    time.sleep(10)