from fastapi import FastAPI
from pydantic import BaseModel
from database import engine, SessionLocal
import models
from models import Base, Measurement as MeasurementModel
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI()

app.add_middleware(
CORSMiddleware,
allow_origins=["http://localhost:5173"],
allow_credentials=True,
allow_methods=["*"],
allow_headers=["*"],
)

Base.metadata.create_all(bind=engine)

class Measurement(BaseModel):
   moisture: float
   temperature: float
   humidity: float
   pic_name: str


class SettingsUpdate(BaseModel):
    moisture_target: float
    report_interval: int
    watering_check_interval: int
    power_saving: bool
    watering_threshold: float
    calibration_min: int
    calibration_max: int


@app.get("/measurements")
def get_measurements():

    db = SessionLocal()

    measurements = db.query(MeasurementModel).all()

    db.close()

    return measurements


@app.get("/measurements/latest")
def get_latest_measurement():

    db = SessionLocal()

    measurement = (
        db.query(MeasurementModel)
        .order_by(MeasurementModel.id.desc())
        .first()
    )

    db.close()

    return measurement


@app.post("/measurements")
def create_measurement(data: Measurement):

    db = SessionLocal()

    measurement = MeasurementModel(
        moisture=data.moisture,
        temperature=data.temperature,
        humidity=data.humidity,
        pic_name=data.pic_name
    )
    db.add(measurement)
    db.commit()
    db.close()

    return {
        "status": "saved"
    }

@app.get("/settings")
def get_settings():

    db = SessionLocal()
    settings = db.query(models.Settings).first()

    if settings is None:
        settings = models.Settings()
        db.add(settings)
        db.commit()
        db.refresh(settings)

    db.close()

    return settings

@app.put("/settings")
def update_settings(data: SettingsUpdate):

    db = SessionLocal()

    settings = db.query(models.Settings).first()

    if settings is None:
        settings = models.Settings()
        db.add(settings)

    settings.moisture_target = data.moisture_target
    settings.report_interval = data.report_interval
    settings.watering_check_interval = data.watering_check_interval
    settings.power_saving = data.power_saving
    settings.watering_threshold = data.watering_threshold
    settings.calibration_min = data.calibration_min
    settings.calibration_max = data.calibration_max

    db.commit()

    db.close()

    return {"status": "updated"}