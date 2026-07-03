# 🛰️ UDP Client-Server Interface for Motion System

This project implements a **bidirectional UDP communication interface** for a motion simulator system using **C socket programming and multithreading**. It is designed to send control packets and receive motion system status packets simultaneously.

## 📦 Features

- ✅ Full-duplex communication using **UDP sockets**
- ✅ Separate `client` and `server` modules
- ✅ **Checksum validation** for data integrity
- ✅ **POSIX threads (pthreads)** for concurrent send/receive operation
- ✅ Custom message structures
- ✅ Loopback/local testing support (`127.0.0.1`)

## 📁 Project Structure
```
.
├── include
│   ├── client
│   │   └── client.h
│   ├── common
│   │   ├── motion_system_messages.h
│   │   ├── process_message.h
│   │   └── UDP.h
│   ├── manager
│   │   └── msm.h
│   └── server
│       └── server.h
├── src
│   ├── client
│   │   └── client.c
│   ├── common
│   │   ├── processMessage.c
│   │   └── UDP.c
│   ├── manager
│   │   └── msm.c
│   ├── server
│   │   └── server.c
│   └── main.c
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## 🧪 How It Works

- The **client** sends `MessageToMotionSystem` packets to the motion system (or simulator).
- The **server** receives `MessageFromMotionSystem` packets and verifies them using a checksum.
- Communication is conducted over **loopback** for local testing using:
  - Client → `127.0.0.1:5000`
  - Server ← `127.0.0.1:5001`
- Threads are used to enable **asynchronous operation** of the client and server.

-
## 🛠️ Build & Run
if VScode build and run doesn't work, use:

in the project directory run:

mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
.\manager\motion_system_manager.exe

### 🧰 Prerequisites

- C compiler (e.g., `gcc`)
- POSIX threads support
- Winsock2 (Windows)

### 🧪 Setup Two Communicating Applications

You can compile the project twice with different roles and ports to create two independent executables (`client.exe` and `server.exe`) that exchange UDP messages over `localhost`.

#### 1️⃣ Build Client Application

In `main.c`, make sure the following configuration is set (default):

```c
#define send_IP "127.0.0.1"
#define send_PORT 5000
#define listen_IP "127.0.0.1"
#define listen_PORT 5001
```

Then build the client

#### 2️⃣ Build Server Application

Now, **edit `main.c`** to swap the ports so the second app listens and sends to the complementary ports:

```c
#define send_IP "127.0.0.1"
#define send_PORT 5001
#define listen_IP "127.0.0.1"
#define listen_PORT 5000
```

Then build the server

### ▶️ Run the Applications

In two separate terminals, run:

```bash
./client.exe
```

```bash
./server.exe
```

They should communicate over UDP, exchanging messages. This setup enables bidirectional, real-time communication between two independently compiled applications.







Copy-Item "C:\Windows\System32\inetsrv\config\applicationHost.config" "C:\Windows\System32\inetsrv\config\applicationHost.config.bak"
notepad "C:\Windows\System32\inetsrv\config\applicationHost.config"
