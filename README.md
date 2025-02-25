campa le iron

server webserv :: https://www.codequoi.com/programmation-reseau-via-socket-en-c/

![image](https://github.com/user-attachments/assets/643bcfe5-b4d9-49ff-a9cc-4e69a49bf567)

![image](https://github.com/user-attachments/assets/3c283bd1-7461-4fad-82a5-a8df3b029e0a)

![image](https://github.com/user-attachments/assets/66378fed-aca2-485d-a197-c5ba6c2dad1a)

Partie cgi : 

What is CGI?

CGI (Common Gateway Interface) is a standard protocol that allows a web server to execute external programs (scripts or binaries) and generate dynamic content for web pages. It acts as a bridge between the web server and external applications, enabling the server to handle requests that require dynamic processing (e.g., form submissions, database queries, etc.).

    How it works:

        A client (e.g., a browser) sends an HTTP request to the web server.

        The web server identifies that the request should be handled by a CGI program.

        The server launches the CGI program (e.g., a Python script, a C++ binary, etc.) and passes the request data (e.g., query parameters, form data) to it.

        The CGI program processes the request, generates dynamic content (e.g., HTML), and sends it back to the server.

        The server forwards the response to the client.

---------------------------------------------------------------------------------------------------------------------------
How CGI Fits into Your Web Server

In your C++ web server, CGI will allow you to handle requests that require dynamic processing. Here's how it fits into the architecture:

    Request Handling:

        When your server receives an HTTP request, it checks if the request should be handled by a CGI program (e.g., based on the URL or file extension, like .cgi or .py).

    Launching the CGI Program:

        Your server will fork a new process to execute the CGI program.

        It sets up environment variables (e.g., QUERY_STRING, REQUEST_METHOD) to pass request data to the CGI program.

        It redirects the CGI program's stdin and stdout to communicate with the server.

    Processing the Request:

        The CGI program reads the request data (e.g., from stdin or environment variables), processes it, and generates a response (e.g., HTML, JSON).

    Sending the Response:

        The CGI program writes the response to stdout.

        Your server captures this output and sends it back to the client as an HTTP response.

---------------------------------------------------------------------------------------------------------------------------


How CGI Fits into Your Web Server

In your C++ web server, CGI will allow you to handle requests that require dynamic processing. Here's how it fits into the architecture:

    Request Handling:

        When your server receives an HTTP request, it checks if the request should be handled by a CGI program (e.g., based on the URL or file extension, like .cgi or .py).

    Launching the CGI Program:

        Your server will fork a new process to execute the CGI program.

        It sets up environment variables (e.g., QUERY_STRING, REQUEST_METHOD) to pass request data to the CGI program.

        It redirects the CGI program's stdin and stdout to communicate with the server.

    Processing the Request:

        The CGI program reads the request data (e.g., from stdin or environment variables), processes it, and generates a response (e.g., HTML, JSON).

    Sending the Response:

        The CGI program writes the response to stdout.

        Your server captures this output and sends it back to the client as an HTTP response.


---------------------------------------------------------------------------------------------------------------------------

Implementing CGI in Your C++ Web Server

Here’s how you can integrate CGI into your server:

    Identify CGI Requests:

        Check if the requested URL corresponds to a CGI script (e.g., based on a specific directory like /cgi-bin/ or file extensions like .cgi).

    Set Up Environment Variables:

        Set up environment variables to pass request data to the CGI program:

            REQUEST_METHOD: The HTTP method (e.g., GET, POST).

            QUERY_STRING: The query parameters (for GET requests).

            CONTENT_LENGTH: The length of the request body (for POST requests).

            CONTENT_TYPE: The type of the request body (e.g., application/x-www-form-urlencoded).

    Fork and Execute the CGI Program:

        Use fork() to create a new process.

        Use execve() to execute the CGI program.

        Redirect stdin and stdout using dup2().

    Capture the Output:

        Read the output from the CGI program's stdout and send it back to the client.