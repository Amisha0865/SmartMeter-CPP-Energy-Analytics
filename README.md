#  Smart Meter Pulse Counter & Energy Analytics Agent

### C++17 • Linux • Software Simulation • Energy Analytics

---

##  Project Overview

The **Smart Meter Pulse Counter & Energy Analytics Agent** is an individual C++ project that simulates the basic working of a smart electricity meter.

The system accepts hourly electricity-meter pulse readings, converts pulses into energy consumption, analyzes usage patterns, detects unusually high consumption, estimates electricity cost, and generates reports.

This project is developed and executed in a **Linux environment using Ubuntu/WSL**.

> **Note:** This is a software simulation. No physical smart-meter hardware is connected.

---

##  Objectives

* Simulate smart-meter pulse readings.
* Convert meter pulses into energy consumption.
* Calculate total and average energy usage.
* Identify the peak consumption hour.
* Detect unusually high energy usage.
* Estimate electricity usage cost.
* Store readings in CSV format.
* Generate energy and alert reports.
* Demonstrate C++ programming concepts in a Linux environment.

---

## 🛠️ Technologies Used

| Technology     | Purpose                                |
| -------------- | -------------------------------------- |
| C++17          | Main programming language              |
| Linux / Ubuntu | Development and execution environment  |
| WSL 2          | Linux environment on Windows           |
| Makefile       | Build automation                       |
| CSV            | Data storage                           |
| File Handling  | Reading and writing data               |
| STL            | Vector, string, algorithms and streams |

---

##  Concepts Demonstrated

### 1. C++ Programming

The project demonstrates:

* Variables and constants
* Structures
* Functions
* Loops
* Conditional statements
* `switch` statements
* Vectors
* Strings
* Input validation
* Sorting
* File handling

### 2. Linux

The project is compiled and executed using Ubuntu/Linux commands:

```bash
make
./smartmeter
```

### 3. Hardware Concept

A real smart meter can generate electrical measurement/pulse data.

In this project, the meter is simulated using pulse values.

Example:

```text
1000 pulses = 1 kWh
```

The constant can be changed in the program according to the simulated meter configuration.

### 4. Software Concept

The C++ application processes the simulated meter readings and produces useful information such as:

* Energy consumption
* Peak usage
* Usage alerts
* Estimated cost
* Reports

### 5. Computer Architecture Concept

The project demonstrates a simple flow of information:

```text
Meter Input
    ↓
Pulse Data
    ↓
C++ Processing
    ↓
Energy Calculation
    ↓
Analytics
    ↓
Reports / Output
```

This represents the basic idea of **input → processing → output** in a computer system.

---

##  Project Structure

```text
SmartMeter_CPP/
│
├── data/
│   └── readings.csv
│
├── reports/
│   ├── energy_report.txt
│   └── alerts.csv
│
├── src/
│   └── main.cpp
│
├── tests/
│
├── Makefile
├── README.md
└── smartmeter
```

---

## ⚙️ How the System Works

### Step 1 — Load Data

The program loads previously saved readings from:

```text
data/readings.csv
```

If no saved data exists, demonstration data can be loaded.

### Step 2 — Record Meter Readings

The user can enter:

* Hour
* Number of pulses

The program validates the entered values.

### Step 3 — Convert Pulses to Energy

The project uses:

```text
Energy (kWh) = Pulses / 1000
```

For example:

```text
430 pulses = 0.430 kWh
```

### Step 4 — Analyze Consumption

The program calculates:

* Total pulses
* Total energy
* Average hourly energy
* Peak consumption hour

### Step 5 — Detect High Usage

The analytics agent compares each reading with the average consumption.

The current rule is:

```text
Alert if usage > 1.5 × average usage
```

The alert indicates unusual usage and does not confirm an electrical fault.

### Step 6 — Estimate Cost

The user enters a sample electricity tariff in Rs/kWh.

The estimated cost is calculated as:

```text
Estimated Cost = Total Energy × Tariff
```

Fixed charges, taxes, slabs and other fees are not included.

### Step 7 — Generate Reports

The system generates:

```text
reports/energy_report.txt
reports/alerts.csv
```

---

##  Main Menu

```text
1  Add / update hourly pulse reading
2  Load demonstration data
3  View all readings
4  Energy dashboard
5  Run analytics agent
6  Estimate usage cost
7  Save readings (CSV)
8  Generate text + CSV reports
9  Exit
```

---

##  Demonstration Example

Sample readings include a higher consumption value at **Hour 8**.

Example:

```text
Hour 8 → 430 pulses → 0.430 kWh
```

The analytics agent identifies this as a high-usage reading when it exceeds the configured threshold.

---

##  How to Build and Run

Open Ubuntu/WSL and move to the project directory:

```bash
cd ~/SmartMeter_CPP
```

Compile the project:

```bash
make
```

Run the application:

```bash
./smartmeter
```

---

##  Rebuild the Project

After modifying the source code:

```bash
make
```

To remove the compiled executable:

```bash
make clean
```

Then build it again:

```bash
make
```

---

## 💾 Generated Files

### `data/readings.csv`

Stores:

```text
hour,pulses,energy_kwh
```

### `reports/energy_report.txt`

Contains the overall energy report and individual readings.

### `reports/alerts.csv`

Contains readings that crossed the configured anomaly threshold.

---

##  Input Validation

The program validates user input to prevent invalid values.

Examples:

* Hour must be between **1 and 24**.
* Pulse count must be non-negative.
* Tariff must be within the accepted range.
* Invalid menu choices are rejected.

---

##  Key Features

*  Smart-meter simulation
*  Energy dashboard
*  Consumption analysis
*  High-usage detection
*  Cost estimation
*  CSV data storage
*  Automatic report generation
*  Linux/Ubuntu execution
*  C++17 implementation

---

##  Future Improvements

The project can be extended with:

* Real smart-meter sensor integration
* IoT connectivity
* Real-time monitoring
* Database storage
* Graphical dashboard
* Mobile/web interface
* More advanced energy-consumption prediction

---

##  Project Type

**Individual Academic Training Project**

**Domain:** Energy Monitoring / Smart Meter Simulation

**Language:** C++17

**Platform:** Linux / Ubuntu using WSL 2

---

##  Conclusion

The Smart Meter Pulse Counter & Energy Analytics Agent demonstrates how simulated meter data can be processed using C++ in a Linux environment.

The project combines programming, file handling, data processing, basic analytics, hardware concepts, software concepts, and computer-system fundamentals into one practical application.
