# Jackfruit OS Project - Container Runtime

## Team Members
- Amar - PES1UG24AM340
- Ullas -PES1UG24AM309

---

## Project Description
This project implements a basic container runtime using Linux system calls.

Each container is created as a separate process using:
- fork()
- chroot()
- exec()

---

## Features
- Start container
- View running containers
- Stop container
- Process isolation

---

## System Calls Used
- fork() → create process
- chroot() → isolate filesystem
- exec() → run program
- kill() → terminate process

---

## How to Run

### Step 1: Compile
make

### Step 2: Start container
sudo ./engine start alpha ../rootfs-alpha /bin/sh

### Step 3: View processes
./engine ps

### Step 4: Stop container
sudo kill <PID>

---

## Test Cases

### Test 1: Start container
Command:
sudo ./engine start alpha ../rootfs-alpha /bin/sh

Output:
Container started successfully

---

### Test 2: View running process
Command:
./engine ps

Output:
Shows container process

---

### Test 3: Stop container
Command:
sudo kill <PID>

Output:
Container stopped

---

## Conclusion
This project demonstrates basic containerization using Linux system calls and process management.
