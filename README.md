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


 Esimerkki arkkitehtuurikaaviosta: 
 <img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/7d8ef1ed-78bd-41a2-ae4c-f2b52f9f1f41" />




## 1. Määrittelyvaihe (definition) eli systeemin ylätason kuvaus: kuvataan mikä systeemi kehitetään (raportin johdannossa on jo kerrottu että miksi kehitystyö tehdään), mitkä ovat systeemin pääominaisuudet, sekä vaatimukset mitä systeemin tulee täyttää, miten systeemi jakautuu osiin eli alisysteemeihin ja mitkä ovat rajapinnat ulospäin ja systeemin sisällä, mitkä ovat systeemin käyttötapaukset (voidaan kuvata esimerkiksi loogisen tason sekvenssikaavioilla), mitkä ovat tarvittavat ohjelmistot ja komponentit, mitä menetelmiä on tarkoitus käyttää, miten vaatimusten todentaminen ja ominaisuuksien testaus on tarkoitus tehdä, ... ; tärkeää on kertoa perustelut kaikelle ja työn arvoa nostaa jos on tehty analyysi eri vaihtoehdoista jonka perusteella on sitten päädytty valittuihin ratkaisuihin; määrittelystä aina oma päälukunsa joka kuvaa kokonaisuutena kehitettävää systeemiä

# Yleiskuvaus järjestelmästä
Työssä kehitetään aurinkoenergialla toimiva kasvin seuranta- ja automaattinen kastelujärjestelmä, joka koostuu sulautetusta laitteesta ja tietokonepohjaisesta ohjelmistosovelluksesta.
Järjestelmän tarkoituksena on:

mitata kasvin olosuhteita jatkuvasti
tehdä kastelupäätöksiä automaattisesti
tarjota käyttäjälle näkyvyys kasvin tilaan

Järjestelmä toimii hajautettuna kokonaisuutena, jossa sulautettu laite vastaa fyysisestä mittaamisesta ja ohjauksesta, ja ohjelmisto vastaa datan käsittelystä ja esittämisestä.

# Systeemin pääominaisuudet
Järjestelmän keskeiset ominaisuudet ovat:

Maaperän kosteuden mittaus
Ympäristön lämpötilan mittaus
Automaattinen kastelu raja-arvojen perusteella
Mittausdatan siirto backend-palvelimelle
Mittaushistorian tallennus
Tietokonepohjainen käyttöliittymä kasvin tilan tarkasteluun
Energiatehokas toiminta aurinkovirran avulla

Ominaisuudet on valittu siten, että järjestelmä on riittävän laaja mutta toteutettavissa opinnäytetyön aikataulussa.

# Vaatimukset
Toiminnalliset vaatimukset

Järjestelmän tulee mitata maaperän kosteutta säännöllisesti
Järjestelmän tulee käynnistää kastelu, kun kosteus alittaa raja-arvon
Järjestelmän tulee lähettää mittausdata backend-palvelimelle
Käyttäjän tulee voida tarkastella mittaushistoriaa
Käyttäjän tulee voida muuttaa raja-arvoja käyttöliittymän kautta


Ei-toiminnalliset vaatimukset

Järjestelmän tulee olla energiatehokas
Järjestelmän tulee toimia ilman jatkuvaa käyttäjän valvontaa
Järjestelmän tulee olla modulaarinen ja laajennettavissa
Rajapintojen tulee olla selkeästi määriteltyjä


# Järjestelmän jakautuminen alisysteemeihin
Järjestelmä jakautuu kolmeen pääalisysteemiin:
1. Sulautettu laite (ESP32)

mittaukset (kosteus, lämpötila)
kastelun ohjaus
datan lähetys

2. Backend-palvelin

datan vastaanotto
datan tallennus (SQLite)
rajapinta frontendille

3. Web-käyttöliittymä

datan visualisointi
asetusten hallinta
käyttäjärajapinta

Tämä jako mahdollistaa alisysteemien itsenäisen kehittämisen ja testauksen.

# Rajapinnat
Ulkoiset rajapinnat


Käyttäjä ↔ käyttöliittymä
(graafinen käyttöliittymä selaimessa)


ESP32 ↔ backend
(HTTP / REST / JSON)



Sisäiset rajapinnat

Backend ↔ tietokanta
Backend ↔ frontend (REST API)

Rajapinnat on toteutettu REST-arkkitehtuurin mukaisesti, koska se on yksinkertainen ja hyvin tuettu ratkaisu.

# Käyttötapaukset
Keskeiset käyttötapaukset ovat:
1. Mittaus ja kastelu

Laite mittaa maaperän kosteuden
Laite vertaa arvoa raja-arvoihin
Kastelu käynnistetään tarvittaessa
Mittaustieto lähetetään backendille


2. Käyttäjä tarkastelee tilaa

Käyttäjä avaa web‑sovelluksen
Sovellus hakee mittaustiedot backendiltä
Mittaukset näytetään käyttöliittymässä


3. Asetusten muuttaminen

Käyttäjä syöttää uudet raja-arvot
Frontend lähettää tiedot backendille
Backend tallentaa asetukset
Laite hyödyntää uusia arvoja


# Ohjelmistot ja komponentit
Laitteisto

ESP32 mikrokontrolleri
kapasitiivinen maaperän kosteusanturi
lämpötila-anturi
vesipumppu / rele
aurinkopaneeli + akku


Ohjelmistot

ESP32 firmware (C/C++)
Backend: Python (FastAPI)
Frontend: TypeScript (web-sovellus)
Tietokanta: SQLite


# Menetelmät ja tekniset valinnat
Järjestelmässä käytetään:

REST-arkkitehtuuria tiedonsiirrossa
JSON-muotoa datassa
Wi‑Fi-yhteyttä kommunikointiin
modulaarista rakennetta

Perustelut:

REST on yksinkertainen ja laajennettava
JSON on helppo käsitellä eri järjestelmissä
ESP32 tarjoaa riittävän suorituskyvyn ja langattomat ominaisuudet


# Vaihtoehtojen analyysi (lyhyesti)
Seuraavia vaihtoehtoja tarkasteltiin:

MQTT vs REST → valittiin REST yksinkertaisuuden vuoksi
Desktop vs web → valittiin web käytettävyyden vuoksi
Resistive vs capacitive sensori → valittiin capacitive kestävyyden vuoksi

Valinnat tehtiin toteutuksen yksinkertaisuuden ja luotettavuuden perusteella.

# Testaus ja todentaminen
Järjestelmän toimivuus todennetaan:

vertaamalla mittausarvoja todelliseen tilanteeseen
testaamalla kastelun käynnistyminen raja-arvojen perusteella
testaamalla datan siirtyminen laite → backend → frontend
tarkastamalla historiadatan tallennus

Testaus kattaa sekä yksittäiset alisysteemit että koko järjestelmän toiminnan.



# 2. Suunnitteluvaihe (design) eli tarkempi alisysteemien ja rajapintojen, jne kuvaus: kuvataan työn aiheeseen sopivilla kuvausmenetelmillä, esim UML notaatioita käyttäen; tärkeää edelleen kertoa perustelut ratkaisuille mahdollisen analyysin pohjalta, kuvat kertovat raportissa enemmän kuin tuhat sanaa..
 
# 3. Toteutusvaihe (implementation) eli alisysteemien ja rajapintojen suunnitelmien toimeenpano määritellyssä laite/ohjelmisto- ympäristössä: kuvataan miten suunnittelu toteutettiin käytäntöön, mihin asioihin törmättiin ja miten ne vaikuttivat projektiin, millainen tuotoksesta tuli, jne..; kuvaustapa varsin vapaamuotoinen

# 4. Todennusvaihe (verification/validation) eli systeemin ominaisuuksien testaus sekä vaatimuksien täyttymisen todentaminen: kuvataan miten toteutuksen onnistumista arvioitiin (esim testimenetelmien käytännön toteutus ja ajetut testit) ja mitkä olivat arvioinnin tulokset (testitulokset); tässä keskitytääm vain testitulosten raportointiin, niiden analyysi on hyvä olla omassa pääluvussaan missä analyysi kootusti koko systeemikehityksen osalta

# 5. Analyysivaihe eli systeemin tekninen analyysi koottuna omassa pääluvussaan: kuvaustapa varsin vapaamuotoinen mutta testituloksista lähtevä analyysi verrattuna alussa määriteltyihin tavoitteisiin on olennaisinta
