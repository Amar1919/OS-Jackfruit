# Jackfruit OS Project - Multi Container Runtime

## Team Members
- Amar-PES1UG24AM340
- Ullas-PES1UG24AM309

---

##  Project Description
This project implements a lightweight container runtime in C using Linux system calls.

A container is created as an isolated process with its own filesystem. Multiple containers can run simultaneously and are managed using simple CLI commands.

---

##  Features Implemented
- Multi-container execution
- Process isolation using chroot
- Container creation using fork
- Program execution using exec
- Container termination using kill
- Basic logging inside container
- Running CPU and memory workloads

---

##  System Calls Used
- fork() → creates a new process (container)
- chroot() → isolates filesystem
- chdir() → sets working directory
- exec() → runs container process
- kill() → terminates container

---

##  How to Run

### Step 1: Go to folder
cd ~/OS-Jackfruit/boilerplate

### Step 2: Compile
make

### Step 3: Start containers
sudo ./engine start alpha ../rootfs-alpha /bin/sh
sudo ./engine start beta ../rootfs-beta /bin/sh

### Step 4: View running containers
./engine ps

### Step 5: Stop containers
sudo kill <PID>

---

##  Test Cases

### Test Case 1: Start Container
Command:
sudo ./engine start alpha ../rootfs-alpha /bin/sh

Expected Output:
Container alpha started with PID XXXX

---

### Test Case 2: Multiple Containers
Command:
sudo ./engine start alpha ../rootfs-alpha /bin/sh
sudo ./engine start beta ../rootfs-beta /bin/sh

Expected:
Two container processes running

---

### Test Case 3: View Processes
Command:
./engine ps

Expected:
List of running container processes

---

### Test Case 4: Stop Container
Command:
sudo kill <PID>

Expected:
Container process stops

---

##  Demo Screenshots

### 1. Multiple Containers Running
<img width="970" height="213" alt="Screenshot from 2026-04-21 21-46-25" src="https://github.com/user-attachments/assets/b1ffc8c4-7461-4219-aeec-0eee8bddb90a" />


---

### 2. Process List (engine ps)
<img width="970" height="113" alt="Screenshot from 2026-04-21 22-01-59" src="https://github.com/user-attachments/assets/99bfba87-1fc9-406b-a8b5-aeabe9a85f82" />


---

### 3. System Process View
Command:
ps -ef | grep while

<img width="970" height="113" alt="Screenshot from 2026-04-21 21-49-37" src="https://github.com/user-attachments/assets/67553d34-2bef-4400-8377-2fde680dba12" />


---

### 4. Container Logs Output
Command:
cat ../rootfs-alpha/log.txt
<img width="970" height="599" alt="Screenshot from 2026-04-21 21-48-27" src="https://github.com/user-attachments/assets/0e15b226-8a64-4618-a969-6489e7debb9a" />


---

## 📊 Scheduling Experiment

Commands used:
./cpu_hog
./memory_hog

Observation:
- CPU-bound tasks consume more CPU
- Memory-bound tasks increase memory usage

---

## 🧹 Cleanup
All container processes are terminated using:
sudo kill <PID>

---

##  Future Work
- Supervisor process with IPC
- Kernel module integration
- Advanced logging system
- Memory monitoring using ioctl
- Improved container lifecycle management

---

##  Conclusion
This project demonstrates basic containerization using Linux system calls. It shows how processes can be isolated and managed similar to lightweight containers.
