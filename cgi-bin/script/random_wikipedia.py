#!/usr/bin/env python3
import os
import requests

# Enable debugging for CGI scripts (useful for troubleshooting)
import cgitb
cgitb.enable()

# Function to fetch a random Wikipedia page URL
def get_random_wikipedia_url():
    response = requests.get("https://en.wikipedia.org/wiki/Special:Random")
    return response.url

# Path where the HTML files will be saved (update to your VSCode workspace directory)
save_path = "/home/armitite/Cursus/19_webserver/cgi-bin/"

# Ensure the save path exists
os.makedirs(save_path, exist_ok=True)

# Determine the HTTP method (GET or POST)
request_method = os.environ.get("REQUEST_METHOD", "GET")

# Prepare response header
print("Content-Type: text/html")
print()  # Blank line to indicate end of headers

# Handle GET request - Save random Wikipedia page to a file
if request_method == "GET":
    random_url = get_random_wikipedia_url()
    get_html_content = f"""
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

    # Save GET page to your VSCode directory
    with open(os.path.join(save_path, "random_wikipedia.html"), "w") as f:
        f.write(get_html_content)

    print(f"<h1>GET page saved to random_wikipedia.html in your VSCode workspace.</h1>")

# Handle POST request - Read data from environment variables
elif request_method == "POST":
    # Retrieve form data from environment variables
    first_name = os.environ.get("FIRST_NAME", "Unknown")
    last_name = os.environ.get("LAST_NAME", "Unknown")

    post_html_content = f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Greeting Page</title>
    </head>
    <body>
        <h1>Hello {last_name}, {first_name}, how are you?</h1>
        <p><a href="/cgi-bin/random_wikipedia.py">Back to Random Page</a></p>
    </body>
    </html>
    """

    # Save POST page to your VSCode directory
    with open(os.path.join(save_path, "greeting_page.html"), "w") as f:
        f.write(post_html_content)

    print(f"<h1>POST page saved to greeting_page.html in your VSCode workspace.</h1>")

else:
    print("<h1>405 Method Not Allowed</h1>")
