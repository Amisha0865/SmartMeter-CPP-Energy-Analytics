Smart Meter Pulse Counter & Energy Analytics Agent

About the Project

This project is a software-based simulation of a smart electricity meter developed using C++ on Linux.

The main idea behind the project is simple: a smart meter can record electricity usage in the form of pulses. The program takes these pulse readings, converts them into energy consumption, and provides some basic analysis of the usage.

The project was developed as part of my 20-day technical training and is designed to demonstrate the concepts covered during the training, including C++, Linux, file handling, computer architecture, and hardware-software interaction.

This project does not require any physical smart-meter hardware. The meter readings are simulated through software.

---

Project Objectives

The main objectives of this project are:

- To understand how a simple smart-meter system can work.
- To use C++ for developing a Linux-based application.
- To simulate meter pulse readings.
- To convert pulse readings into energy consumption.
- To calculate average and peak energy usage.
- To identify unusually high consumption.
- To estimate electricity cost using a user-provided tariff.
- To store readings in a CSV file.
- To generate simple energy and alert reports.
- To understand the relationship between hardware and software in a metering system.

---

How the Project Works

The application provides a menu-driven interface.

The user can add or update an hourly pulse reading or load sample readings for testing.

The pulse value is then converted into energy using the following assumption:

1000 pulses = 1 kWh

Therefore:

Energy (kWh) = Pulses / 1000

For example, if the meter records 430 pulses:

430 / 1000 = 0.430 kWh

The application uses the recorded values to calculate total consumption, average consumption, and the highest-consuming hour.

It also checks for unusually high consumption. For this project, a reading is considered an alert when it is greater than 1.5 times the average energy consumption.

This threshold is only used for the simulation. It does not represent an official electricity-board fault detection rule.

---

Main Features

1. Add or Update Reading

The user can enter the hour and the number of pulses recorded during that hour.

2. Sample Data

Sample readings can be loaded so that the application can be tested without entering everything manually.

3. View Readings

The stored hourly readings can be displayed from the application.

4. Energy Dashboard

The dashboard displays:

- Total pulses
- Total energy consumed
- Average hourly consumption
- Peak consumption hour
- Peak energy value
- Simple text-based consumption graph

5. Energy Analytics

The analytics section calculates the average consumption and checks the readings against the selected threshold.

If a reading is unusually high, the program generates an alert.

For example:

Alert: Hour 8 has unusually high consumption.

The program also provides a simple suggestion such as checking high-power appliances.

The alert should not be treated as proof of an electrical fault.

6. Tariff Cost Calculation

The user can enter a sample electricity tariff in rupees per kWh.

The program then calculates the estimated cost based on total energy consumption.

7. CSV Export

The meter readings can be saved in:

data/readings.csv

CSV makes the data easy to view and reuse in spreadsheet or data-analysis software.

8. Report Generation

The application creates reports inside the "reports" directory.

These include:

energy_report.txt
alerts.csv

---

Project Structure

SmartMeter_CPP/
│
├── data/
│   └── readings.csv
│
├── reports/
│   ├── energy_report.txt
│   └── alerts.csv
│
├── smartmeter/
│
├── src/
│   ├── main.cpp
│   ├── ...
│
├── tests/
│   └── ...
│
├── Makefile
├── README.md
└── smartmeter

The exact source files may vary depending on the current version of the project.

---

Technologies Used

- C++17
- Linux / Ubuntu
- GCC / G++
- GNU Make
- Git
- GitHub
- CSV file handling
- Standard C++ libraries

---

Hardware and Software Concept

A real smart-meter system contains hardware that measures electricity usage and produces measurement data.

A simplified flow can be considered as:

Smart Meter Hardware
        |
        | Pulse / Meter Reading
        v
Linux Device / Interface
        |
        v
C++ Application
        |
        v
Energy Calculation
        |
        v
Analytics and Reports

In this project, the physical meter and sensor are simulated by software input.

This makes it possible to demonstrate the basic idea without requiring an actual smart-meter device.

---

Linux Device Driver Concept

A real hardware-based version of this project could use a Linux device driver to communicate with the meter hardware.

A device driver acts as an interface between the Linux kernel and a hardware device.

For example:

Hardware Meter
      |
      v
Linux Device Driver
      |
      v
User-Space Application
      |
      v
Energy Analytics

The current project mainly focuses on the user-space C++ application and software simulation. The physical meter hardware is not connected to the system.

This project therefore uses the device-driver concept as part of the hardware-software architecture discussion rather than pretending that a physical meter driver is being used.

---

Computer Architecture Concepts

The project also relates to basic computer architecture concepts.

The CPU executes the C++ program instructions and performs the calculations required for energy and cost analysis.

The system memory is used while the program is running, while files such as CSV data and reports provide persistent storage.

The basic flow is:

Input
  |
  v
CPU Processing
  |
  v
Memory
  |
  v
File Storage
  |
  v
Output / Report

The project helped me understand how software interacts with the operating system and how data moves between input, processing, memory, and storage.

---

Example Sample Data

The application contains sample hourly pulse readings such as:

120
145
130
110
125
160
180
430
155
140
170
135

The reading of 430 pulses is significantly higher than the other readings, so the analytics module can identify it as an unusual reading.

With the project's conversion:

430 pulses = 0.430 kWh

---

Running the Project

1. Open Linux / Ubuntu

Go to the project directory:

cd ~/SmartMeter_CPP

2. Build the Project

Use:

make

If a Makefile is not being used, the project can also be compiled using the appropriate "g++" command specified for the source files.

3. Run the Application

./smartmeter

The program opens a menu similar to:

1. Add/Update Hourly Pulse
2. Load Sample Data
3. View Readings
4. Dashboard
5. Analytics
6. Tariff Cost
7. Save CSV
8. Generate Reports
9. Exit

Select an option by entering its corresponding number.

---

Example Dashboard

After loading the sample data, the dashboard can show information such as:

Total Pulses       : 2000
Total Energy       : 2.000 kWh
Average Energy     : 0.167 kWh
Peak Hour          : 8
Peak Energy        : 0.430 kWh

The application also displays a simple text graph to make the hourly consumption easier to understand.

---

Example Analytics

For the sample readings, the application calculates an average consumption and uses the threshold:

Threshold = Average Energy × 1.5

The high reading at Hour 8 can therefore generate an alert.

The purpose of this feature is to demonstrate basic anomaly detection using C++ calculations.

---

Files Generated by the Program

readings.csv

Contains the meter readings in CSV format.

Example:

Hour,Pulses
1,120
2,145
3,130
...

energy_report.txt

Contains a summary of the energy consumption.

alerts.csv

Contains readings that were identified as unusually high.

---

Why I Made This Project

I selected this project because it connects software programming with a practical hardware-related problem.

Electricity meters are a good example of a system where hardware collects information and software processes that information.

Since I did not have access to an actual smart-meter device, I decided to simulate the meter readings and focus on the software side of the system.

This allowed me to practice C++, Linux commands, file handling, calculations, data processing, and basic hardware-software architecture concepts in one project.

---

Limitations

There are some limitations in the current version:

- It is a software simulation and does not use a physical smart meter.
- The pulse-to-energy conversion is based on a fixed project assumption.
- The anomaly threshold is a simple rule.
- The application does not communicate with a real electricity meter.
- The tariff is entered manually by the user.
- The dashboard is command-line based.

These limitations can be addressed in future versions.

---

Future Improvements

Some possible improvements are:

- Connect the application to an actual smart-meter sensor.
- Add a Linux character device driver for hardware communication.
- Add real-time meter readings.
- Store readings in a database.
- Add a graphical dashboard.
- Add daily, weekly, and monthly consumption analysis.
- Add more advanced anomaly detection.
- Add IoT connectivity for remote monitoring.
- Add support for multiple meters.

---

Conclusion

The Smart Meter Pulse Counter & Energy Analytics Agent is a Linux-based C++ project that simulates the basic working of a smart-meter monitoring system.

It takes pulse readings, converts them into energy consumption, analyzes the readings, identifies unusually high usage, calculates estimated cost, and generates reports.

The project helped me apply the concepts learned during the training in a practical way, especially C++, Linux, file handling, system-level concepts, and the interaction between hardware and software.

---

Author

Amisha Mohanty

B.Tech – Computer Science and Engineering
Cybersecurity Specialization
Siksha 'O' Anusandhan (ITER), Bhubaneswar

---

Project Status

Completed as a software simulation project for the 20-day technical training.
