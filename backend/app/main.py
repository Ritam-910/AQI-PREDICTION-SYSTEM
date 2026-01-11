from fastapi import FastAPI

from app.routes.forecast import router as forecast_router
from app.routes.alerts import router as alerts_router
from app.routes.trends import router as trends_router
from app.routes.summaries import router as summaries_router
from app.routes.metadata import router as metadata_router
from app.routes.health_advisory import router as health_advisory_router 

app = FastAPI(
    title="PM2.5 & AQI Forecast Backend",
    description="Forecasting, alerts, trends, summaries & health advisories",
    version="1.0.0"
)

@app.get("/")
def root():
    return {"status": "Backend is running"}

app.include_router(forecast_router)
app.include_router(alerts_router)
app.include_router(trends_router)
app.include_router(summaries_router)
app.include_router(metadata_router)
app.include_router(health_advisory_router)  
