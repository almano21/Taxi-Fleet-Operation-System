# Taxi-Fleet-Operation-System
C-based taxi fleet management system for managing taxi orders, driver assignment, online payments, and daily operational reports.

## Team Members

- Giorgi Jajanidze
- Andria Gabadze
- Timur Kabanchuk

## Project Description

The Taxi Fleet Management System is a C-based application designed to manage taxi orders, drivers, vehicles, payments, and operational reports.

Clients place taxi orders through a console application by providing the pickup time, pickup address, contact phone number, and destination. The system checks driver availability and assigns the nearest available driver.

If no free drivers are available, the system checks drivers who are currently en route and assigns a suitable driver within the maximum allowed distance.

The system also supports online simulated payments using registered client profiles with linked bank cards and generates daily reports containing the total number of trips, revenue, and statistics for individual drivers.

The Software Requirements Specification (SRS) is available here:

[View SRS](docs/SRS-R2_Updated.docx) 

Open the file and click View raw to view/download the document.

[View the flowchart](docs/ScenarioFlowchart-R2%20_Updated.pdf)

## Release 2 Test Evidence

Section 3.8.2 of the [SRS](docs/SRS-R2_Updated.docx) contains
a summary of the executed tests and representative console output.

The complete console logs are available separately:

- [E1 — Booking, payment, cancellation and reporting tests](docs/TUDENGITAKSO_R2_Test_Evidence_2026-10-21.txt)
- [E2 — Driver selection and fleet administration tests](docs/TUDENGITAKSO_R2_Fleet_Test_Evidence_2026-10-21.txt)
