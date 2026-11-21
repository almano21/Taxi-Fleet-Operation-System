# TUDENGITAKSO – Checkpoint 1

**Course:** ICS0004 Fundamentals of Programming  
**Project:** Variant 5 – Taxi Fleet Operation

> **Submission note:** The required Release 1 scenario flowcharts are provided separately in `ScenarioFlowchart-R1.pdf`.

## 1. Project Goal

TUDENGITAKSO is a console-based, on-demand taxi-service simulation designed for TalTech students. It allows student clients to create an account, link a fictional payment card, order and pay for taxi trips, while fleet administrators can view reports on the total number of trips, revenue, and per-driver statistics.

## 2. Stakeholders

- **Student client:** Directly uses the account-registration, bank-card linking, taxi-ordering, trip-completion, and payment options.
- **Fleet administrator:** Uses the daily fleet report to view the total number of trips, revenue, and statistics for each driver.
- **Taxi driver:** Does not directly operate the current client menu, but receives trip assignments and contributes to the per-driver statistics.

## 3. Short Software Requirements Specification

### 3.1 Scope

#### In Scope

- The system shall register a student using a student ID and telephone number.
- The system shall allow a registered student to link a fictional bank card.
- The system shall receive taxi orders from registered student clients.
- The system shall record the order time, contact phone number, pickup location, and destination location.
- The system shall determine simulated driver availability.
- The system shall assign the nearest suitable driver.
- The system shall complete a trip and simulate an online payment.
- The system shall produce reports containing the total number of trips, total revenue, and per-driver statistics.

#### Out of Scope

- The system will not perform real banking transactions or process real payment cards.
- The system will not provide GPS or live driver tracking.
- The system will not use real maps, address searches, or route calculations.
- The system will not operate as a real web application.
- The system will not use permanent database or file storage.
- The system will not manage multiple simultaneous client accounts.

### 3.2 User Stories

- **US-01:** As a student client, I want to create an account so that I can access the taxi service.
- **US-02:** As a student client, I want to link a fictional bank card so that I can use the simulated online-payment feature.
- **US-03:** As a student client, I want to order a taxi between useful student locations so that I can reach my destination conveniently.
- **US-04:** As a taxi driver, I want to receive a clear trip assignment so that I know when and where to collect the client.
- **US-05:** As a student client, I want to complete and pay for my trip so that the active ride can be closed correctly.
- **US-06:** As a fleet administrator, I want to view the daily fleet report so that I can monitor trips, revenue, and driver performance.

### 3.3 Business Rules

- **BR-01:** A student ID shall contain the letter `S`, followed by 12 digits, and end with the letter `M`. During this checkpoint, the user enters only the 12 digits between `S` and `M`.
- **BR-02:** A registration phone number shall use the Estonian country code `+372`, followed by eight digits.
- **BR-03:** A client must register before linking a bank card.
- **BR-04:** A fictional bank card number shall contain exactly 16 digits. Its expiry month shall be from 1 to 12, and its expiry year shall be from 2026 to 2036.
- **BR-05:** A client must register and link a bank card before ordering a taxi.
- **BR-06:** A valid order time shall be between `00:00` and `23:59`.
- **BR-07:** Pickup and destination locations shall be selected from the six available numbered locations.
- **BR-08:** The pickup location and destination location cannot be the same.
- **BR-09:** A client can have only one active trip during a program session.
- **BR-10:** If free drivers are available, the system shall assign the nearest free driver.
- **BR-11:** If all drivers are busy, only an en-route driver within the maximum allowed distance of 5 km shall be eligible. If several drivers are eligible, the nearest one shall be assigned.
- **BR-12:** If no eligible driver exists, the order shall not be created.
- **BR-13:** A simulated online payment is required when completing a trip.
- **BR-14:** Every completed trip shall contribute to the trip total, revenue total, and assigned driver's statistics.
- **BR-15:** Student clients cannot access daily fleet reports; report access shall be restricted to the fleet administrator.

### 3.4 Technical Constraints

- **CON-01:** The system shall be implemented as a console application using the C programming language.
- **CON-02:** The Checkpoint 1 implementation shall use basic scalar variables, conditional statements, and loops.
- **CON-03:** The Checkpoint 1 implementation shall not use structs, arrays, or program file input/output.
- **CON-04:** Program data shall exist only during the current session and shall be lost when the program closes.
- **CON-05:** Only one student-client profile shall be supported during each program run.
- **CON-06:** The simulated fleet shall contain two drivers: Karl and Gustavo.
- **CON-07:** The system shall use six fixed locations: TalTech Main Building, Akadeemia Student Dormitory, Mustamäe Keskus, Telliskivi/Balti Jaam, Tallinn Airport, and IKEA Tallinn in Kurna.
- **CON-08:** All card information shall be fictional, and no real payment provider shall be connected.
- **CON-09:** The user shall enter the simulated order time manually because the program does not use the system clock.
- **CON-10:** The program shall use fixed simulated driver distances instead of GPS data.
- **CON-11:** The daily fleet report shall represent only the current program session because permanent storage is not available.

## 5. Menu and Loop Implementation

### 5.1 Menu Options

```text
1. Create an account
2. Link a bank card
3. Order a taxi
4. Complete trip and pay
5. View daily fleet report
0. Exit
```

Options 1–4 represent the student client's main journey through the system. Option 5 is intended only for the fleet administrator and shall be restricted in the completed implementation. Option 0 closes the program.

### 5.2 Loop Behaviour

The variable `programRunning` begins with the value `1`, which represents the running state. While `programRunning == 1`, the `while` loop repeatedly displays the menu and asks the user to select an option. The selected number is stored in the `mainMenuChoice` variable and processed using an `if / else if / else` decision structure.

The exit process works as follows:

1. The condition `mainMenuChoice == 0` checks whether the user selected Exit.
2. The program assigns `0` to `programRunning`.
3. The next evaluation of the loop condition becomes false.
4. The `while` loop ends and the program closes.

Invalid numeric menu choices or invalid information produce an error message. Unless Exit is selected, the loop then displays the menu again and allows the user to perform another operation.

## 6. Design Rationale

### 6.1 Why This Scenario Was Chosen

Transport is relevant to both international and local TalTech students because they regularly travel between the university, student accommodation, shopping areas, transport hubs, and other useful destinations. TUDENGITAKSO creates a student-focused version of a taxi service that operates between a small set of fixed locations, keeping the simulation clear, convenient, and manageable for an introductory programming project.

The scenario demonstrates important programming concepts, including input with `scanf_s`, validation and decision-making with `if / else if / else`, state management with variables, and repetition with a `while` loop. Later checkpoints could expand the project with strings, arrays, pointers, structs, persistent storage, more drivers, and additional functionality.

### 6.2 Why This Menu Design Was Chosen

The menu follows the natural order in which a client uses the service. A client first creates an account, then links a fictional bank card, orders a taxi, and finally completes and pays for the trip. This order supports convenience and ensures that the required registration and payment information exists before a taxi can be ordered.

The daily report is kept as a separate administrative option because student clients cannot access fleet statistics; only the fleet administrator can use this feature. Option `0` provides a clear and conventional way to exit the application. The repeating menu allows several actions to be completed during one program session, following the sequence of registration, card linking, taxi ordering, and trip completion/payment.
