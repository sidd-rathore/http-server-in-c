# 🧠 Simple HTTP Server in C

A minimal HTTP server written from scratch using low-level socket programming in C.

Built as part of a learning journey to understand how networking and HTTP work at a fundamental level - no frameworks, just raw sockets!

---

## 🚀 Features

- ✅ Manual socket creation using `AF_INET` and `SOCK_STREAM`
- ✅ Port binding, listening, and accepting multiple client connections
- ✅ Basic HTTP request parsing and response handling
- ✅ Serves static files from the server directory
- ✅ **Directory listing for folders** with clickable HTML links
- ✅ Custom 404 Not Found handling for invalid paths

---

## 📚 Learning Objectives

- Understand core socket functions: `socket()`, `bind()`, `listen()`, `accept()`
- Learn how HTTP requests are structured and parsed manually
- Practice sending valid HTTP responses with headers and body
- Build a stepping stone for future projects like chat apps, REST APIs, or full web servers

---

## 🛠️ Usage

### 🧱 Compile & Run

To compile and run the server:

- Run: `gcc main.c -o server`
- Then: `./server`

### 🌐 Access the Server

You can test the server in a few different ways:

- Open your browser and go to: [http://localhost:8080](http://localhost:8080)
- Or use command-line tools:
  - `curl http://localhost:8080`
  - `telnet localhost 8080`

### 📥 Server Behavior

- Returns **file contents** when a file is requested
- Shows an **HTML directory listing** when a folder is requested
- Responds with **404 Not Found** for unknown or unsupported paths

---

## 🧵 Follow the Journey

- This project is part of a public learning journey I'm sharing on Twitter — follow along and see each step as it's built and improved!
- 📲 Twitter: @SidharRathore
- #100DaysOfCode #CProgramming #Networking this was my readme duing the first commit can you revise this reame
