PM25_BREAKPOINTS = [
    {"aqi_lo": 0,   "aqi_hi": 50,  "pm_lo": 0,   "pm_hi": 30,  "category": "Good"},
    {"aqi_lo": 51,  "aqi_hi": 100, "pm_lo": 31,  "pm_hi": 60,  "category": "Satisfactory"},
    {"aqi_lo": 101, "aqi_hi": 200, "pm_lo": 61,  "pm_hi": 90,  "category": "Moderate"},
    {"aqi_lo": 201, "aqi_hi": 300, "pm_lo": 91,  "pm_hi": 120, "category": "Poor"},
    {"aqi_lo": 301, "aqi_hi": 400, "pm_lo": 121, "pm_hi": 250, "category": "Very Poor"},
    {"aqi_lo": 401, "aqi_hi": 500, "pm_lo": 251, "pm_hi": 500, "category": "Severe"},
]

def pm25_to_aqi(pm25):
    for bp in PM25_BREAKPOINTS:
        if bp["pm_lo"] <= pm25 <= bp["pm_hi"]:
            aqi = (
                (bp["aqi_hi"] - bp["aqi_lo"])
                / (bp["pm_hi"] - bp["pm_lo"])
            ) * (pm25 - bp["pm_lo"]) + bp["aqi_lo"]

            return round(aqi), bp["category"]

    return 500, "Severe"
