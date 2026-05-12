## Opinnäytetyö 

# Kasvin seuranta- ja automaattinen kastelujärjestelmä

## Projektin kuvaus
Tässä projektissa toteutetaan aurinkoenergialla? toimiva sulautettu laite
sekä siihen liittyvä tietokonesovellus, joiden avulla voidaan seurata
kasvin olosuhteita ja ohjata kastelua automaattisesti.

## Tavoitteet
- Kasvin maaperän kosteuden jatkuva seuranta
- Automaattinen kastelu raja-arvojen perusteella
- Mittaushistorian tallennus ja visualisointi
- Energiatehokas toiminta aurinkovirran avulla

## Järjestelmän osat
- Sulautettu laite (ESP32)
- Tietokonepohjainen backend
- Web-käyttöliittymä (TypeScript)
- Kamera?


+-------------------+
|      Käyttäjä     |
+-------------------+
          |
          v
+---------------------------+
|   Web-käyttöliittymä      |
|  (TypeScript / selain)    |
+---------------------------+
          |
          v  REST / HTTP
+---------------------------+
|   Backend-palvelin        |
|   (Python + REST API)     |
+---------------------------+
          |
          |  Mittausdata,
          |  asetukset
          v
+---------------------------+
|  Sulautettu laite         |
|        (ESP32)            |
+---------------------------+
     |                |
     |                |
     v                v
+-----------+    +-----------+
| Anturit   |    | Kastelu   |
| - kosteus |    | - pumppu  |
| - lämpö   |    |           |
+-----------+    +-----------+

     ^
     |
+---------------------------+
| Aurinkopaneeli + akku     |
+---------------------------+
