# RashDecisionMakerService
A C++ Implementation of Rash Decision Maker RESTful Service

## Background
Many people believe it's very difficult to create a RESTful service in C++. As a C++ hobby, I decided to create one.
There are a few rocks need to be smashed:

1. Deal with the HTTP protocol
2. Deal with query
3. Deal with Json

### Deal with HTTP protocol
After searching the web for a long time, I found mongoose (https://github.com/cesanta/mongoose) by chance.
Though it's a very tiny library (two files!), it's very powerful and easy to use. By using it, I can easily create
a self-contained web server.

### Deal with query
Currently I'm working with path query only, so no big deal, just string processing.

### Deal with Json
Most of the RESTful service outputs Json. I'm not using too much Json this moment, so I created a tree based Json generator.

## How to run
The source code was created by using Visual C++ 2010 Express.
Just open the .sln file, and build the solution. Run the generated executable to start the service.
The service will listen to port 8000. Accessing http://localhost:8000 will print the help message.
