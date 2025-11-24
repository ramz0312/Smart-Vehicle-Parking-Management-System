# ⚙️ ParkIt API Endpoints Specification

This document details the expected input parameters (Request Body) and output formats (Response Body) for the main API routes used by the Mobile App and IoT devices.

## 1. Authentication

### A. User Login
* **Endpoint:** `POST /api/v1/login`
* **Description:** Authenticates a user and returns an access token.
* **Request Body (JSON):**
    ```json
    {
        "email": "user@example.com",
        "password": "secure_password"
    }
    ```
* **Success Response (200 OK):**
    ```json
    {
        "success": true,
        "token": "jwt.access.token.string",
        "user_id": 101,
        "expires_in": 3600
    }
    ```
* **Error Response (401 Unauthorized):**
    ```json
    {
        "success": false,
        "message": "Invalid email or password."
    }
    ```

## 2. Booking Management

### B. Reserve Parking Slot
* **Endpoint:** `POST /api/v1/bookings/reserve`
* **Description:** Checks real-time availability and creates a new booking entry.
* **Request Body (JSON):**
    ```json
    {
        "lot_id": 5,
        "vehicle_number": "MH12AB1234",
        "start_time": "2025-12-01T10:00:00Z",
        "end_time": "2025-12-01T12:30:00Z"
    }
    ```
* **Success Response (201 Created):**
    ```json
    {
        "success": true,
        "booking_id": 45,
        "slot_name": "A15",
        "confirmation_qr_code_url": "[https://api.parkit.com/qr/45](https://api.parkit.com/qr/45)"
    }
    ```
* **Error Response (409 Conflict):**
    ```json
    {
        "success": false,
        "message": "Slot A15 is unavailable for the selected time. Suggestions available."
    }
    ```

## 3. IoT Integration

### C. Update Slot Status (from Arduino)
* **Endpoint:** `POST /api/v1/iot/update-status`
* **Description:** Receives real-time occupancy status from the Arduino node.
* **Request Body (JSON/Form Data):**
    ```json
    {
        "slot_id": 205,
        "status": "OCCUPIED"  // or "AVAILABLE"
    }
    ```
* **Success Response (200 OK):**
    ```json
    {
        "success": true,
        "message": "Status updated."
    }
    ```

---

## 2. PricePro Enhancements (ML & Web)

The goal here is to document the data used by the ML model and how you plan to prove the model's quality.

### **File to Create: `/data/DATA_DICTIONARY.md`**

This defines the features the ML model uses for prediction.

```markdown
# 📊 PricePro Data Dictionary

This document details the features (columns) required for the Machine Learning model's input and the expected target variable (Price).

## 1. Feature Variables (Input to ML Model)

| Feature Name | Data Type | Description | Source / Rationale |
| :--- | :--- | :--- | :--- |
| **`area_sqft`** | Integer | Living area of the house in square feet. | Direct input from user. |
| **`num_bedrooms`** | Integer | Number of bedrooms in the property. | Direct input from user. |
| **`property_age`** | Integer | Age of the property in years (calculated from build date). | User input / Database lookup. |
| **`proximity_score`**| Float (0-1) | Score based on closeness to major transit lines and highways. | Calculated metric (GIS data). |
| **`amenities_index`** | Float (0-10) | Aggregate score based on nearby perks (schools, parks, hospitals). | Calculated metric (Perks Database). |
| **`market_trend_index`**| Float | Indexed price change in the local area over the last 6 months. | Historical data processing. |

## 2. Target Variable (Output)

| Feature Name | Data Type | Description |
| :--- | :--- | :--- |
| **`final_price`** | Float | The final selling price (the variable the model predicts). |

---

### **File to Create: `/model/EVALUATION.md`**

This defines how the performance of your ML model will be measured.

```markdown
# 📈 PricePro Model Evaluation Plan

The primary goal is to build a robust regression model to predict price accurately. The model's performance will be rigorously assessed using industry-standard metrics.

## 1. Core Performance Metrics

The following metrics will be logged and tracked after each training run:

* **Mean Squared Error (MSE):** Measures the average squared difference between the estimated values and the actual value. This is used to penalize large errors heavily.
    $$MSE = \frac{1}{n}\sum_{i=1}^{n}(Y_i - \hat{Y}_i)^2$$
* **Root Mean Squared Error (RMSE):** The square root of the MSE. It provides an error metric in the same units as the price (e.g., Rupees/Dollars), making it easily interpretable.
* **R-squared ($R^2$):** Measures the proportion of the variation in the dependent variable (Price) that is predictable from the independent variables (Features). A value closer to 1 indicates a better fit.

## 2. Cross-Validation Strategy

* The model will utilize **k-Fold Cross-Validation** (typically $k=5$) during training to ensure the model generalizes well across different subsets of the data and avoids overfitting.

## 3. Success Threshold

* **Target RMSE:** The final deployed model must achieve an RMSE within **8-10%** of the average property price in the dataset, ensuring the prediction is accurate enough for investment purposes.
