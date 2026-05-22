# Good mindset. Let me give you a prioritized list — most important first.

## Priority 1 — Make it actually useful

**Request parsing**
Right now you ignore the request completely. At minimum parse the first line:
```
GET /index.html HTTP/1.1
```
Extract the method and path. Then you can serve different responses for different paths.

**Static file serving**
Read actual files from disk and serve them. Someone requests `/index.html` — open that file, read it, send it back. This is what makes a web server actually useful.

**Proper error responses**
```
404 Not Found      ← file does not exist
405 Method Not Allowed  ← only handle GET for now
400 Bad Request    ← malformed request
```

## Priority 2 — Make it robust

**Concurrent connections**
Right now one client at a time. Use `fork()` or threads to handle multiple clients simultaneously. Read:
```bash
man 2 fork
```

**Connection timeout**
If a client connects but never sends a request your server hangs forever. Add a timeout.

**Proper `Content-Type` detection**
`.html` → `text/html`
`.css` → `text/css`
`.jpg` → `image/jpeg`
`.js` → `application/javascript`

## Priority 3 — Make it production-like

**Logging**
Every request logged with timestamp, IP, method, path, status code:
```
[2026-05-20 15:33:19] 127.0.0.1 GET /index.html 200
```

**Configuration**
Port number, document root, log file — read from a config file instead of hardcoded.

**Signal handling**
Handle `Ctrl+C` gracefully — close all connections, free memory, exit cleanly. Read:
```bash
man 2 signal
```

## The order I recommend

1. Request parsing — extract method and path
2. Static file serving — serve real files from disk
3. Proper error responses — 404, 405, 400
4. Concurrent connections with `fork()`
5. Logging
6. Content-Type detection

---

# What your server does
- Accepts TCP connections ✅
- Reads HTTP requests ✅
- Sends a hardcoded HTML response ✅
- Handles one request at a time ✅

## What Apache does on top of that

**Concurrency** — Apache handles thousands of simultaneous connections. Your server handles one at a time — while you are handling client 1, client 2 waits. Apache uses multiple processes or threads to handle many clients simultaneously.

**Routing** — Apache reads the request path and serves different content for `/`, `/about`, `/images/photo.jpg`. Your server returns the same thing for everything.

**Static file serving** — Apache reads actual files from disk and serves them. Your server returns a hardcoded string.

**Virtual hosting** — Apache reads the `Host` header and serves different websites. Your server ignores all headers.

**HTTPS/TLS** — Apache encrypts connections with SSL/TLS. Your server is plain HTTP — all data is visible on the network.

**Configuration** — Apache has a rich configuration system — `httpd.conf`. Your server is hardcoded.

**Logging** — Apache logs every request with IP, timestamp, path, status code. Your server logs nothing.

**Security** — Apache handles malformed requests, attacks, timeouts. Your server would crash or hang on bad input.

**CGI/Modules** — Apache can run PHP, Python, and other languages to generate dynamic content.

---

## Your web server
- Single file, ~100 lines of C
- Handles one request at a time
- Returns hardcoded HTML
- No routing
- No HTTPS
- No logging
- No configuration
- No error handling for bad requests
- No static file serving
- **But** — built from scratch with full understanding of every line

## Apache httpd
- 30 years old, millions of lines of C
- Multi-process model — forks a new process per connection
- Rich module system — PHP, Python, SSL, rewrite rules
- Virtual hosting
- `.htaccess` configuration
- Most widely deployed web server historically
- Heavy — uses lots of memory per connection
- Great for dynamic content — PHP apps, WordPress

## Nginx
- Written in 2004 by Igor Sysoev specifically to solve Apache's performance problems
- **Event driven, non blocking** — handles thousands of connections with minimal memory
- Single threaded event loop — no forking, no threading
- Much lighter than Apache
- Better for static files and reverse proxying
- Powers Cloudflare, Netflix, and most high traffic sites
- Configuration is cleaner than Apache

## The key architectural difference

```
Apache — one process/thread per connection
                ↓
10,000 connections = 10,000 processes — heavy

Nginx — one event loop handles all connections
               ↓
10,000 connections = 1 process — lightweight
```

This is called the **C10K problem** — how do you handle 10,000 concurrent connections? Apache struggled. Nginx solved it with event driven architecture.

## The interesting thing about Go

Go's `net/http` standard library uses a model similar to Apache — one goroutine per connection. But goroutines are extremely lightweight compared to OS processes or threads — so Go gets the simplicity of Apache's model with performance close to Nginx.

That is one reason Go became so popular for backend development.

---

## code mapped to TCP/IP model

```
┌─────────────────────────────────────────────────┐
│  Application Layer (HTTP)                        │
│  - read() the request bytes                      │
│  - parse "GET / HTTP/1.1"                        │
│  - write() "HTTP/1.1 200 OK\r\n..."             │
├─────────────────────────────────────────────────┤
│  Transport Layer (TCP)                           │
│  - socket(AF_INET, SOCK_STREAM, 0)              │
│  - bind(), listen(), accept()                    │
│  - reliable byte stream guaranteed               │
├─────────────────────────────────────────────────┤
│  Internet Layer (IP)                             │
│  - AF_INET — IPv4 addressing                    │
│  - 127.0.0.1:8080 — routing to your process     │
├─────────────────────────────────────────────────┤
│  Network Access Layer                            │
│  - your ethernet/wifi card                       │
│  - kernel handles this — you never touch it      │
└─────────────────────────────────────────────────┘
```

## code mapped to OSI model

```
┌─────────────────────────────────────────────────┐
│  Layer 7 — Application (HTTP)                   │
│  - reading and writing HTTP formatted text       │
│  - "GET / HTTP/1.1", "200 OK", headers, body    │
├─────────────────────────────────────────────────┤
│  Layer 6 — Presentation                         │
│  - not relevant for plain HTTP                   │
│  - would matter for HTTPS — TLS encryption       │
├─────────────────────────────────────────────────┤
│  Layer 5 — Session                              │
│  - TCP connection management                     │
│  - kernel handles this                           │
├─────────────────────────────────────────────────┤
│  Layer 4 — Transport (TCP)                      │
│  - SOCK_STREAM                                   │
│  - reliable delivery guaranteed by kernel        │
│  - three way handshake — kernel handles it       │
├─────────────────────────────────────────────────┤
│  Layer 3 — Network (IP)                         │
│  - AF_INET                                       │
│  - sockaddr_in — IP address and port             │
│  - htons() — network byte order                  │
├─────────────────────────────────────────────────┤
│  Layer 2 — Data Link                            │
│  - MAC addresses                                 │
│  - kernel and network driver handle this         │
├─────────────────────────────────────────────────┤
│  Layer 1 — Physical                             │
│  - actual electrical signals on wire             │
│  - hardware handles this                         │
└─────────────────────────────────────────────────┘
```

## The key insight

Your C code only directly touches **two layers**:

**Layer 3/4 — Transport/Network:**
```c
socket(AF_INET, SOCK_STREAM, 0)  // Layer 3 + 4
bind(), listen(), accept()        // Layer 4
```

**Layer 7 — Application:**
```c
read()   // receiving HTTP text
write()  // sending HTTP text
```

Everything below Layer 3 — the actual packet routing, ethernet frames, physical signals — the **kernel handles completely**. You never write a single line of code for those layers.

## Why TCP/IP model is more practical

The OSI model has 7 layers but layers 5 and 6 are mostly theoretical — in practice TCP/IP collapses them:

```
OSI Layer 5 + 6 + 7  →  TCP/IP Application Layer
OSI Layer 4          →  TCP/IP Transport Layer
OSI Layer 3          →  TCP/IP Internet Layer
OSI Layer 1 + 2      →  TCP/IP Network Access Layer
```

That is why engineers use TCP/IP model in practice and OSI model for teaching concepts.

## The beautiful abstraction

You wrote ~100 lines of C and touched only Layer 3/4 and Layer 7. The kernel silently handled Layers 1, 2, 5, and 6 for you. That is the power of abstraction — you got a working HTTP server without knowing anything about ethernet frames or electrical signals.


Start with request parsing — everything else depends on it. Want to tackle that now?
