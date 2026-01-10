# 🌍 AQI & PM2.5 Forecasting System – Phase 2 (Hourly)

## 📌 Project Overview
This project focuses on forecasting **PM2.5 concentration for the next 24–72 hours (hourly)** using a trained **LSTM time-series model**, and converting the predicted PM2.5 values into **AQI values and AQI categories** as per **CPCB (India) standards**.

The backend is being rebuilt cleanly using **FastAPI**, with a clear separation between:
- ML model logic
- AQI rule-based logic
- API layer

This phase is designed to be **production-ready, explainable, and extensible**, and acts as the foundation for dashboards, health advisories, and future scaling.

---

## 🧠 Project Phases Overview (FINAL & LOCKED)

---

### ✅ Phase 2 — PM2.5 Forecasting Backend (Current Phase)
Phase 2 forms the **core forecasting engine** of the system.

#### What Phase 2 includes:
- **LSTM-based PM2.5 forecasting model**
  - Predicts PM2.5 for the next **24 / 48 / 72 hours (hourly)**
- **Saved scaler**
  - Used to normalize and inverse-transform PM2.5 values
- **CPCB AQI rule-based conversion**
  - Converts PM2.5 → AQI value + AQI category
- **FastAPI backend**
  - Loads the trained model and scaler
  - Serves PM2.5 and AQI forecasts via APIs
  - Acts as the base layer for dashboards and analytics

📌 **Important**
- The LSTM model is already trained  
- Backend must **only load and serve predictions**  
- **Backend development is a core part of Phase 2**  
- No retraining happens in backend

---

### 🔜 Phase 3 — AQI Trends, Visualization & Health Advisory Engine
(Planned)

Phase 3 acts as the **interpretation and insight layer** of the system.

#### Features:
- Generate **PM2.5 trends** using:
  - Historical PM2.5 data
  - Current PM2.5 value
  - Forecasted PM2.5 values (from Phase 2)
- Compute **AQI value and AQI category** for each timestamp using CPCB rules
- Provide **time-series data** for PM2.5 and AQI trends (past–present–future)
- Implement a **rule-based health advisory engine** with different guidance for:
  - General population
  - Asthma / respiratory patients
  - Elderly people

#### Visualization:
- Line plots and charts will be created using:
  - **Frontend charting libraries** (e.g., Chart.js / Recharts)
  - **Power BI dashboards**
- Backend will **only supply clean, time-indexed JSON data**
- Backend will **NOT generate plots**

#### Key principles:
- AQI computation remains **rule-based**
- Health advisories are **deterministic and explainable**
- Backend provides logic & data; frontend and dashboards handle visualization

---

### 🔜 Phase 4 — Multi-City & Multi-Station Scaling
(Planned)

This phase focuses on **system scalability**, not new ML models.

#### Features:
- Support **multiple cities** (minimum 3 for prototype)
- Support **multiple monitoring stations per city**
- City and station selection in dashboards
- Station metadata (city, latitude, longitude)
- Map view with AQI bubbles and markers
- Reuse:
  - Same PM2.5 forecasting model
  - Same AQI rules
  - Same health advisory engine

📌 This phase makes the system **realistic, deployable, and smart-city ready**.

---

### 🔜 Phase 5 — Multi-Pollutant PM2.5 Inference (Advanced ML)
(Planned – Separate Module)

This is an **advanced extension** of the system.

#### Features:
- Predict PM2.5 using other pollutant inputs:
  - PM10, NO₂, SO₂, CO, O₃
- Use tree-based regression models (Random Forest / XGBoost)
- AQI value & category derived using CPCB rules
- Acts as a **fallback mechanism** when PM2.5 sensor data is unavailable

📌 This phase is **independent** of Phase 2–4 and does not affect dashboards directly.

---

## 📁 Folder Structure (Phase 2 Backend Focus)

phase2_hourly_forecasting_v1/
│
├── app/
│ ├── main.py # FastAPI entry point
│ ├── routes/
│ │ └── forecast.py # API endpoints
│ ├── services/
│ │ └── forecast_service.py # Model loading & prediction logic
│ └── core/
│ └── config.py # Configuration & paths
│
├── models/
│ ├── stageA_pm25_lstm_72hr.h5 # Trained LSTM model
│ └── stageA_pm25_scaler.pkl # Saved scaler
│
├── data/
│ ├── raw/
│ └── processed/
│
├── aqi_rules/
│ └── cpcb_rules.py # PM2.5 → AQI conversion (CPCB rules)
│
├── notebooks/ # Training & experiments (read-only)
├── saved_plots/ # Training visuals
├── requirements.txt
└── README.md


---

## 🧪 Model & Logic Details

### PM2.5 Forecasting Model (Phase 2)
- Model type: **LSTM (Time Series)**
- Input: Historical PM2.5 values
- Output: Next 72 hours PM2.5 (hourly)
- Status: **Already trained**
- ❌ Do NOT retrain in backend

### AQI Computation & Health Logic
- Based on **CPCB official breakpoints**
- Uses **linear interpolation**
- AQI is **rule-based, not ML-based**
- Health advisories are **category-based and deterministic**

---

## 🚀 Backend (FastAPI)

### Run Backend
```bash
uvicorn app.main:app --reload

API Documentation:
Swagger UI:
http://127.0.0.1:8000/docs

🎯 Example API Output:
{
  "datetime": "2026-01-08 14:00",
  "pm25": 82.4,
  "aqi": 165,
  "category": "Poor"
}

--


⚠️ Important Engineering Rules:

❌ Do NOT retrain ML models in backend

❌ Do NOT predict AQI using ML

❌ Do NOT generate plots in backend

❌ Do NOT mix frontend logic into backend

Backend decides logic.
Frontend and dashboards only visualize

📌 Final Note:

This project is designed to evolve from a single-station PM2.5 forecasting backend into a multi-city, health-aware air quality intelligence platform, following real-world engineering practices