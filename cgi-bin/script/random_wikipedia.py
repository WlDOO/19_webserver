#!/usr/bin/env python3
import os
import requests

# Enable debugging for CGI scripts
import cgitb
cgitb.enable()

# Function to fetch a random Wikipedia page URL'
def get_random_wikipedia_url():
    response = requests.get("https://en.wikipedia.org/wiki/Special:Random")
    return response.url

# Determine the HTTP method (GET or POST)
request_method = os.environ.get("REQUEST_METHOD", "GET")

# Prepare response header
print("Content-Type: text/html\r\n", end="")  # Explicitly add `\r\n`
print("\r\n", end="")  # Blank line to indicate end of headers

# Handle GET request - Directly print HTML response
if request_method == "GET":
    random_url = get_random_wikipedia_url()
    print(f"""\
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Random Wikipedia Page</title>
    </head>
    <body>
        <h1>Here's a random Wikipedia page for you:</h1>
        <p><a href="{random_url}">{random_url}</a></p>
        <p><a href="/cgi-bin/script/random_wikipedia.py">Get another random page</a></p>
    </body>
    </html>
    """)

# Handle POST request - Directly print HTML response
elif request_method == "POST":
    first_name = os.environ.get("FIRST_NAME", "Unknown")
    last_name = os.environ.get("LAST_NAME", "Unknown")
    print(f"""\
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Greeting Page</title>
    </head>
    <body>
        <h1>Hello {last_name}, {first_name}, how are you?</h1>
    </body>
    </html>
    """)

else:
    print("<h1>405 Method Not Allowed</h1>")