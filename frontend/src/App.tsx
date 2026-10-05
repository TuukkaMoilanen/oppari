import { useState } from "react";

interface Measurement {
  id: number;
  device_id: string;
  soil_moisture: number;
  temperature: number;
  humidity: number;
  light: number;
}

function App() {
  const [measurement, setMeasurement] =
    useState<Measurement | null>(null);

  const getLatestMeasurement = async () => {
    const response = await fetch(
      "http://127.0.0.1:8000/measurements/latest"
    );

    const data = await response.json();

    setMeasurement(data);
  };

  return (
    <div>
      <h1>🌱 Kasvimonitori</h1>

      <button onClick={getLatestMeasurement}>
        Hae viimeisin mittaus
      </button>

      <pre>
        {JSON.stringify(measurement, null, 2)}
      </pre>
    </div>
  );
}

export default App;