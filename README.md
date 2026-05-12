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




# 1. Määrittelyvaihe (definition) eli systeemin ylätason kuvaus: kuvataan mikä systeemi kehitetään (raportin johdannossa on jo kerrottu että miksi kehitystyö tehdään), mitkä ovat systeemin pääominaisuudet, sekä vaatimukset mitä systeemin tulee täyttää, miten systeemi jakautuu osiin eli alisysteemeihin ja mitkä ovat rajapinnat ulospäin ja systeemin sisällä, mitkä ovat systeemin käyttötapaukset (voidaan kuvata esimerkiksi loogisen tason sekvenssikaavioilla), mitkä ovat tarvittavat ohjelmistot ja komponentit, mitä menetelmiä on tarkoitus käyttää, miten vaatimusten todentaminen ja ominaisuuksien testaus on tarkoitus tehdä, ... ; tärkeää on kertoa perustelut kaikelle ja työn arvoa nostaa jos on tehty analyysi eri vaihtoehdoista jonka perusteella on sitten päädytty valittuihin ratkaisuihin; määrittelystä aina oma päälukunsa joka kuvaa kokonaisuutena kehitettävää systeemiä

# 2. Suunnitteluvaihe (design) eli tarkempi alisysteemien ja rajapintojen, jne kuvaus: kuvataan työn aiheeseen sopivilla kuvausmenetelmillä, esim UML notaatioita käyttäen; tärkeää edelleen kertoa perustelut ratkaisuille mahdollisen analyysin pohjalta, kuvat kertovat raportissa enemmän kuin tuhat sanaa..
 
# 3. Toteutusvaihe (implementation) eli alisysteemien ja rajapintojen suunnitelmien toimeenpano määritellyssä laite/ohjelmisto- ympäristössä: kuvataan miten suunnittelu toteutettiin käytäntöön, mihin asioihin törmättiin ja miten ne vaikuttivat projektiin, millainen tuotoksesta tuli, jne..; kuvaustapa varsin vapaamuotoinen

# 4. Todennusvaihe (verification/validation) eli systeemin ominaisuuksien testaus sekä vaatimuksien täyttymisen todentaminen: kuvataan miten toteutuksen onnistumista arvioitiin (esim testimenetelmien käytännön toteutus ja ajetut testit) ja mitkä olivat arvioinnin tulokset (testitulokset); tässä keskitytääm vain testitulosten raportointiin, niiden analyysi on hyvä olla omassa pääluvussaan missä analyysi kootusti koko systeemikehityksen osalta

# 5. Analyysivaihe eli systeemin tekninen analyysi koottuna omassa pääluvussaan: kuvaustapa varsin vapaamuotoinen mutta testituloksista lähtevä analyysi verrattuna alussa määriteltyihin tavoitteisiin on olennaisinta
