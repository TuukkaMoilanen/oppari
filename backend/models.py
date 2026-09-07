from sqlalchemy import Column, Integer, Float, String
from sqlalchemy.orm import declarative_base

Base = declarative_base()

class Measurement(Base):
    __tablename__ = "measurements"

    id = Column(Integer, primary_key=True, index=True)
    device_id = Column(String)
    soil_moisture = Column(Float)
    temperature = Column(Float)
    humidity = Column(Float)
    light = Column(Float)