#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

std::string read_html_file(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return content;
    } else {
        return "Error 404";
    }
}

int main() {
    io_service io;

// Change the port to 8081
tcp::endpoint endpoint(tcp::v4(), 8081);


    // Create an acceptor to listen for incoming connections
    tcp::acceptor acceptor(io, endpoint);

    while (true) {
        // Create a socket to represent the incoming connection
        tcp::socket socket(io);

        // Wait for and accept an incoming connection
        acceptor.accept(socket);

        // Read the content of your HTML file (replace "your_html_file.html" with your file path)
        std::string html_content = read_html_file("your_html_file.html");

        // Generate an HTTP response with the HTML content
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Connection: close\r\n";
        response += "\r\n";
        response += html_content;

        // Send the response to the client
        boost::system::error_code ignored_error;
        write(socket, buffer(response), ignored_error);
    }

    return 0;
}
