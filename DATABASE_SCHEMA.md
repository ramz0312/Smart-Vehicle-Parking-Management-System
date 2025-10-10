-- MySQL Queries for the ParkIt: Smart Vehicle Parking Management System

-- --------------------------------------------------------
-- Table: Users
-- Stores user authentication and primary vehicle information.
-- --------------------------------------------------------
CREATE TABLE Users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    vehicle_number VARCHAR(15), 
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- --------------------------------------------------------
-- Table: Parking_Lots
-- Stores information about each parking facility.
-- --------------------------------------------------------
CREATE TABLE Parking_Lots (
    lot_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    address TEXT,
    total_slots INT NOT NULL
);

-- --------------------------------------------------------
-- Table: Parking_Slots
-- Stores information about individual slots and their real-time status.
-- --------------------------------------------------------
CREATE TABLE Parking_Slots (
    slot_id INT AUTO_INCREMENT PRIMARY KEY,
    lot_id INT NOT NULL,
    slot_name VARCHAR(10) NOT NULL,
    is_occupied_sensor BOOLEAN NOT NULL DEFAULT FALSE, -- Status from Arduino
    
    FOREIGN KEY (lot_id) REFERENCES Parking_Lots(lot_id),
    UNIQUE KEY (lot_id, slot_name) -- Ensures slot name is unique within a lot
);

-- --------------------------------------------------------
-- Table: Bookings
-- Stores all reservation details, entry/exit times, and status.
-- --------------------------------------------------------
CREATE TABLE Bookings (
    booking_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    slot_id INT NOT NULL,
    vehicle_number VARCHAR(15) NOT NULL,
    
    booked_start_time DATETIME NOT NULL,
    booked_end_time DATETIME NOT NULL,
    
    actual_entry_time DATETIME DEFAULT NULL,  -- Recorded by IoT
    actual_exit_time DATETIME DEFAULT NULL,   -- Recorded by IoT
    
    status ENUM('PENDING', 'ACTIVE', 'COMPLETED', 'CANCELED') NOT NULL DEFAULT 'PENDING',
    
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
    FOREIGN KEY (slot_id) REFERENCES Parking_Slots(slot_id)
);
