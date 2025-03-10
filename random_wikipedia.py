#!/usr/bin/env python3
import cgi
import cgitb
import requests

# Enable debugging for CGI scripts (useful for troubleshooting)
cgitb.enable()

# Function to fetch a random Wikipedia page URL
def get_random_wikipedia_url():
    response = requests.get("https://en.wikipedia.org/wiki/Special:Random")
    return response.url

# CGI script logic
print("Content-Type: text/html")  # Set the response type to HTML
print()  # Blank line to indicate end of headers

# Get the random Wikipedia URL
random_url = get_random_wikipedia_url()

# Generate the HTML response
html_response = f"""
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
    <p><a href="/cgi-bin/random_wikipedia.py">Get another random page</a></p>
</body>
</html>
"""

# Send the HTML response to the client
print(html_response)