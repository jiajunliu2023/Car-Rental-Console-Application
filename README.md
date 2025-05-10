# 🚗 Car Rental Console Application

This C# console-based application allows users to register and log in as either customers or admins. Customers can view and book cars, while admins manage car records and rental requests. The system supports rental period validation, cost calculation, and booking status management.

---

## 📌 Table of Contents
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [User Roles](#user-roles)
- [PDF Documentation](#pdf-documentation)
- [Author](#author)

---

## ✅ Features

### 👤 User Management
- Register as **Customer** or **Admin**
- Login with role distinction
- Unique username enforcement

### 🚘 Car Management (Admin Only)
- Add, update, and delete cars
- Car attributes include make, model, year, mileage, availability, rental period limits, and price

### 📅 Rental Booking (Customer)
- View all available cars
- Search cars by make or model
- Book a rental with start/end dates
- Automatically calculates rental fee
- Booking status: `pending`

### 🛠️ Rental Processing (Admin)
- View all booking requests
- Accept or reject bookings
- Auto-update car availability based on booking status
- Delete rental records

---

## 🧰 Tech Stack

- **Language**: C#
- **Platform**: .NET Console App
- **Database**: In-memory data structures (for prototype/demo purposes)

---

## ▶️ Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/car-rental-console-app.git
   cd car-rental-console-app
2.  Open in Visual Studio

    Open the .sln file

    Make sure target framework is .NET 6 or higher

3.  Run the application

    Press Ctrl + F5 or dotnet run in terminal

📘 Usage

1. As a Customer:
- Register and log in

- View available cars

- Search cars

- Book a rental

- View booking confirmation and rental fee

2. As an Admin:
- View all car records

- Add/edit/delete cars

- Process booking requests

- Delete rental records

👥 User Roles
Role	Capabilities
Customer--Browse and book cars
Admin--Manage car inventory, process bookings

📄 PDF Documentation
📙 User Manual (PDF)
[View Project User Manual (PDF)](./User%20Manual-Jiajun%20Liu..pdf)

👨‍💻 Author
Jiajun Liu
Yoobee College, Auckland
