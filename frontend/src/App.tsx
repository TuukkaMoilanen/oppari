import { useEffect, useState } from "react";
import "./App.css";

import {
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  ReferenceLine,
} from "recharts";



interface Measurement {
  id: number;
  moisture: number;
  temperature: number;
  humidity: number;
  timestamp: string;
}

interface Settings {
  moisture_target: number;
  report_interval: number;
  watering_check_interval: number;
  power_saving: number;
}






function App() {
  const [measurement, setMeasurement] =
    useState<Measurement | null>(null);

  const [measurements, setMeasurements] =
    useState<Measurement[]>([]);

  const [settings, setSettings] =
    useState<Settings | null>(null);




  const getLatestMeasurement = async () => {
    const response = await fetch(
      "http://127.0.0.1:8000/measurements/latest"
    );

    const data = await response.json();

    setMeasurement(data);
  };

  const getMeasurements = async () => {
    const response = await fetch(
     "http://127.0.0.1:8000/measurements"
    );
      const data = await response.json();

    setMeasurements(data);
  };

  const getSettings = async () => {
    const response = await fetch(
    "http://127.0.0.1:8000/settings"
  );

  
  const data = await response.json();

  setSettings(data);
 };


  const saveSettings = async () => {
    await fetch("http://127.0.0.1:8000/settings", {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(settings),
    });

    getSettings();
};

  useEffect(() => {
    getLatestMeasurement();
    getMeasurements();
    getSettings();
  }, []);

  const plantStatus =
    measurement &&
    settings &&
    measurement.moisture < settings.moisture_target
      ? "🔴 Vaatii kastelua"
      : "🟢 Kosteus hyvä";



  return (
    <div className="App">
      <h1>🌱 Smart Plant Monitor</h1>

      <div className="status-card">
        {plantStatus}
      </div>

    {measurement && (
      <div className="overview-card">

        <div className="overview-metrics">

          <div className="overview-item">
            <div className="metric-icon">💧</div>
            <div className="metric-value">
              {measurement.moisture} %
            </div>
            <div className="metric-label">
              Kasvin kosteus
            </div>
          </div>

          <div className="overview-item">
            <div className="metric-icon">🌡️</div>
            <div className="metric-value">
              {measurement.temperature} °C
            </div>
            <div className="metric-label">
              Lämpötila
            </div>
          </div>

          <div className="overview-item">
            <div className="metric-icon">💦</div>
            <div className="metric-value">
              {measurement.humidity} %
            </div>
            <div className="metric-label">
              Ilmankosteus
            </div>
          </div>

        </div>

        <div className="overview-divider"></div>

        <h2>📷 Viimeisin kuva</h2>

        <div className="image-placeholder">
          Ei kuvaa saatavilla
        </div>

      </div>
)}
    

  <div className="chart-container">
    <h2>Kosteushistoria</h2>
    <LineChart width={700} height={380} data={measurements}>
      <XAxis 
        dataKey="timestamp"
        tickFormatter={(value) =>
          new Date(value).toLocaleTimeString([], {
            hour: "2-digit",
            minute: "2-digit",
          })
        }
      />
      <YAxis />
      <Tooltip />
      {settings && (
        <ReferenceLine
          y={settings.moisture_target}
          stroke="red"
          strokeDasharray="5 5"
          label="Tavoite"
        />
      )}

      <ReferenceLine
        y={30}
        stroke="orange"
        strokeDasharray="3 3"
        label="Kasteluraja"
      />

        <Line
          type="monotone"
          dataKey="moisture"
        />

    </LineChart>
    </div>
      {settings && (
  <div className="settings-card">
    <h2>⚙️ Asetukset</h2>

    <div className="settings-grid">

      <div className="setting-card">
        <div className="setting-value">
          {settings.moisture_target} %
        </div>

        <div className="setting-controls">
          <button
            onClick={() =>
              setSettings({
                ...settings,
                moisture_target:
                  settings.moisture_target - 5,
              })
            }
          >
            -
          </button>

          <button
            onClick={() =>
              setSettings({
                ...settings,
                moisture_target:
                  settings.moisture_target + 5,
              })
            }
          >
            +
          </button>
        </div>

        <div className="setting-label">
          Kosteustavoite
        </div>
      </div>

      <div className="setting-card">
        <div className="setting-value">
          {settings.report_interval} min
        </div>

        <div className="setting-controls">
          <button
            onClick={() =>
              setSettings({
                ...settings,
                report_interval:
                  settings.report_interval - 5,
              })
            }
          >
            -
          </button>

          <button
            onClick={() =>
              setSettings({
                ...settings,
                report_interval:
                  settings.report_interval + 5,
              })
            }
          >
            +
          </button>
        </div>

        <div className="setting-label">
          Raportointiväli
        </div>
      </div>

      <div className="setting-card">
        <div className="setting-value">
          {settings.watering_check_interval} min
        </div>

        <div className="setting-controls">
          <button
            onClick={() =>
              setSettings({
                ...settings,
                watering_check_interval:
                  settings.watering_check_interval - 5,
              })
            }
          >
            -
          </button>

          <button
            onClick={() =>
              setSettings({
                ...settings,
                watering_check_interval:
                  settings.watering_check_interval + 5,
              })
            }
          >
            +
          </button>
        </div>

        <div className="setting-label">
          Tarkistusväli
        </div>
      </div>

      <div className="setting-card checkbox-card">
        <div className="setting-value">
          <input
            type="checkbox"
            checked={Boolean(settings.power_saving)}
            onChange={(e) =>
              setSettings({
                ...settings,
                power_saving:
                  e.target.checked ? 1 : 0,
              })
            }
          />
        </div>

        <div className="setting-label">
          Virransäästö
        </div>
      </div>

    </div>

    <button
      className="save-button"
      onClick={saveSettings}
    >
      Tallenna
    </button>
  </div>
)}
 
</div>
  );
}
  
 
export default App;
