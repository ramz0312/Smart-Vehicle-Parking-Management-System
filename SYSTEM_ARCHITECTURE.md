# 🏛️ System Architecture - ParkIt
## High-Level Overview
ParkIt is structured into three main layers: The **Mobile Client** (Flutter), the **Backend API** (Node.js/Python), and the **IoT Layer** (Arduino/C++), all connected to a central **Database** (MySQL/PostgreSQL).

## Data Flow for a Successful Booking:
1.  **User Request (Mobile App):** User 📱 $\to$ Selects (Lot ID, Start Time, Duration).
2.  **API Call:** Mobile App $\to$ Sends POST request to **Backend API**.
3.  **Availability Check:** Backend API $\to$ Queries **Database** (Checks if slot is free for the time window using `Bookings` and `Parking_Slots`).
4.  **Reservation & Notification:**
    * If **Available:** Backend API writes a new entry to the `Bookings` table.
    * Backend API sends **FCM Push Notification** for booking confirmation and schedules the **Traffic-Aware Alarm**.
5.  **Confirmation:** Backend API $\to$ Sends confirmation response $\to$ Mobile App displays the ticket/QR code.

## IoT Integration (Slot Status & Entry/Exit):
* **Slot Status Update:** **ParkIt\_Node.ino (Arduino)** polls sensor $\to$ Sends real-time status (Occupied/Available) via HTTP/MQTT $\to$ **Backend API** $\to$ Updates `Parking_Slots` table.
* **Entry/Exit:** An ANPR device (external to the Arduino node) captures the plate $\to$ Sends plate and timestamp to **Backend API** (`entry` or `/exit`) to Backend verifies and updates the `Bookings` table.
