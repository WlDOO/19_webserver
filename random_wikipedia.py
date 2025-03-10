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

# Generate the HTML content
html_content = f"""
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

# Write the HTML content to a file
file_path = "/home/armitite/Cursus/19_webserver/random_wikipedia.html"  # Chemin où le fichier sera sauvegardé
with open(file_path, "w") as file:
    file.write(html_content)

# Send a response to the client
print(f"<p>HTML file created at <a href='/random_wikipedia.html'>/random_wikipedia.html</a></p>")