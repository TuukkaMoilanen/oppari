from sqlalchemy import Column, Integer, Float, String, DateTime
from sqlalchemy.orm import declarative_base
from datetime import datetime

Base = declarative_base()

class Measurement(Base):
    __tablename__ = "measurements"

    id = Column(Integer, primary_key=True, index=True)
    moisture = Column(Float)
    temperature = Column(Float)
    humidity = Column(Float)
    pic_name = Column(String)
    timestamp = Column(DateTime, default=datetime.now)


class Settings(Base):
    __tablename__ = "settings"

    id = Column(Integer, primary_key=True, index=True)
    moisture_target = Column(Float, default=40)
    report_interval = Column(Integer, default=60)
    watering_check_interval = Column(Integer, default=30)
    power_saving = Column(Integer, default=1)
