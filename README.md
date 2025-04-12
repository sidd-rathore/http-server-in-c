# 🧠 Simple HTTP Server in C

A minimal HTTP server written from scratch using low-level socket programming in C.

Built as part of a learning journey to understand how networking and HTTP work at a fundamental level - no frameworks, just raw sockets!

---

## 🚀 Features

- ✅ Manual socket creation with `AF_INET` and `SOCK_STREAM`
- ✅ Port binding, listening, and accepting client connections
- ✅ Basic HTTP response handling
- ✅ Server reads from and writes to clients

---

## 📚 Learning Objectives

- Understand how `socket()`, `bind()`, `listen()`, and `accept()` work in C
- Handle simple HTTP requests manually
- Build a foundation for deeper networking projects (e.g., chat server, REST APIs)

---

## 🛠️ Usage

### Compile
```
bash
gcc main.c -o server
./server
```
- Then open your browser and visit: http://localhost:8080
- Or use curl, telnet or np to connect to the server

---

## 📂 Project Structure
```
.
├── main.c         # Server source code
├── README.md      # You're here!
└── .gitignore     # Git ignore rules

```
---

##🧵 Follow the Journey
- This project is part of a public learning journey I'm sharing on Twitter — follow along and see each step as it's built and improved!
- 📲 Twitter: @SidharRathore
- #100DaysOfCode #CProgramming #Networking
