from fastapi import FastAPI
from pydantic import BaseModel
from database import engine, SessionLocal
from models import Base, Measurement as MeasurementModel    

app = FastAPI()

Base.metadata.create_all(bind=engine)

class Measurement(BaseModel):
    deviceId: str
    soilMoisture: float
    temperature: float
    humidity: float
    light: float

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
        device_id=data.deviceId,
        soil_moisture=data.soilMoisture,
        temperature=data.temperature,
        humidity=data.humidity,
        light=data.light  
    )
    db.add(measurement)
    db.commit()
    db.close()

    return {
        "status": "saved"
    }