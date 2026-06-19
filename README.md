# 🏠 University Dormitory & Restaurant Management System (UDRMS)

A C++ Dormitory & Restaurant Management System built with Qt. Includes student registration and login, room allocation across dormitories, restaurant menu management, and automatic CSV-based data persistence.

---

## 📦 Features

- 🎓 Student self-registration and login
- 🏢 Multiple dormitories, each with its own rooms and restaurant
- 🚪 Room management with capacity tracking
- 🍽️ Restaurant menu management per dormitory
- 🔑 Role-based login: Student, Dorm Administrator, Restaurant Staff, System Administrator
- 📍 Assign students to dormitories and rooms
- 💾 Automatic data saving/loading via CSV files

---

## 🛠️ Tech Stack

- Language: C++ (C++17)
- Framework: Qt 6 (Qt Widgets)

---

## 🚀 Getting Started

### Login

Use one of the pre-set staff accounts, or sign up as a new student from the login screen.

| Role | Email | Password |
|---|---|---|
| System Administrator | admin@ensia.edu.dz | admin123 |
| Dorm Administrator | dormadmin@ensia.edu.dz | dorm123 |
| Restaurant Staff | chef@ensia.edu.dz | rest123 |
| Student | sign up to create one | — |

Note: Only students can self-register — staff accounts are fixed.

### Main Window

After login, the sidebar gives access to: Students, Dormitories, Rooms, Restaurant, and Logout.

Students — view all students; add a new one; assign an unassigned student to a room (blocked if the room is full).

Dormitories — view all dormitories; add a new one (name + location).

Rooms — view all rooms across dormitories; add a new room to an existing dormitory.

Restaurant — view each dormitory's menu; update breakfast/lunch/dinner.

Logout — confirms, saves all data, and returns to the login screen.

---

## 💾 Data Storage

Stored as CSV files in `data/`:

- `students.csv` — ID, name, email, password, year, dormitory, room
- `dormitories.csv` — dormitory name, location, room number, capacity
- `menus.csv` — dormitory name, breakfast, lunch, dinner

Data loads on startup and saves automatically on logout or app close.

---

## 👩‍💻 Author

Lina Latreche
ENSIA — 2026 · Object-Oriented Programming, 2025–2026
