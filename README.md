# IS2101-Simulate-Interrupt-Handling-for-I-O-Devices-in-Java-C--NNM24IS204-
# 🧠 Interrupt Handling Simulation (Multithreaded C Program)

## 📋 Overview
This project simulates **hardware interrupt handling** in a simple multitasking environment using **POSIX threads (pthreads)**.  
It demonstrates how different devices (keyboard, mouse, and printer) generate interrupts, and how these interrupts can be **masked** (disabled) or **unmasked** (enabled) dynamically at runtime.

Each device runs on its own thread and triggers interrupts at random intervals.  
The user can control which device interrupts are active through terminal commands.

---

## ⚙️ Features
- Simulates interrupts from **Keyboard**, **Mouse**, and **Printer**
- Allows **masking/unmasking** of individual device interrupts
- Demonstrates **mutual exclusion (mutex)** for interrupt handling
- Handles **user input concurrently** with interrupt threads
- Simple and educational — great for learning **OS concepts** like interrupts, masking, and threading

---

## 🧩 Components

| Thread | Function | Description |
|---------|-----------|-------------|
| `keyboard_thread()` | Simulates keyboard interrupts |
| `mouse_thread()` | Simulates mouse interrupts |
| `printer_thread()` | Simulates printer interrupts |
| `user_input_thread()` | Takes user commands (mask/unmask/exit) |
| `handle_interrupt()` | Simulates the Interrupt Service Routine (ISR) for a device |

---

## 🧠 Priority Levels
| Device | Priority |
|---------|-----------|
| Keyboard | 1 (highest) |
| Mouse | 2 |
| Printer | 3 (lowest) |

> ⚠️ Note: Priorities are defined for conceptual understanding — actual scheduling is handled by the OS thread scheduler.

---

## 🧮 Commands

Run the program and use the following commands in the terminal:

| Command | Description |
|----------|--------------|
| `mask keyboard` | Disables (masks) keyboard interrupts |
| `unmask mouse` | Enables (unmasks) mouse interrupts |
| `mask printer` | Disables printer interrupts |
| `exit` | Terminates the program |

Example interaction:
