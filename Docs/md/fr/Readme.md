# Liste des resources trouvées 

## Liste des villes 

- Base de données des villes contenant plus d'un million de villes par le monde
- Donne la région, le code languE, la longitude la latitude , le nom et la population de la ville
- Site : https://www.maxmind.com/fr/free-world-cities-database
- Inutile car pris en charge par l'API Geobyte

## Liste des POI 

http://www.openpoimap.org

## Liste des routes 

https://openrouteservice.org/


## Api Pollution

- Participant: Julien
- Realisation : Julien 
- Indique la qualité de l'air des villes grâce à:
  - Indice allant de 0 (bon) à 300 (Dangereux)
  - Code couleur
- Site: https://aqicn.org/api/fr/
- API
  - entrée: indique une URL http://aqicn.org/city/paris/
  - sortie: récupère un format JSON
  - Doc : http://aqicn.org/json-api/doc/
- Portée:
  - Monde: Environ 9000 villes
  - France: ne contient pas toutes les villes

## Romain Api meteo, alerte meteo, pollution, UV

- Participan: Romain
- Indique la temperaure, précipitation, pollution, UV, vent
- Site : https://openweathermap.org/api

- API
  - Entree: ville, code-pays/pays, date
  - Sortie: Json,XML ou HTML celon les version d'API utilisé
- Portée:
  - Monde : Environ 37 000 villes

- Donnees meteo journaliere en fonction de la latitude et longitude:
  - http://api.openweathermap.org/data/2.5/weather?lat=40&lon=3&appid=3543ac0c00624ed3bb653359621e5344 :
    - http://api.openweathermap.org/data/2.5 => prefix de l'adresse API
	 - /weather? => type d'API utilisé sur OPENWEATHERMAP
	 - lat=40&long3 => coodonnees lattitude et longitude permettant la geolocalisation 
	 - &appid=3543ac0c00624ed3bb653359621e5344 => clef API permmettant l'utilisation de l'API OPENWEATHERMAP


## Api Carte [OpenStreeMap](https://www.openstreetmap.org)

- Participant: Miguel
- Réalisation : Miguel 
- Ils existent deux possibilités:
  * Utiliser la API de [OpenStreetMap](https://www.openstreetmap.org/about)
    - API v.06: https://wiki.openstreetmap.org/wiki/API_v0.6
    - entrée: indiquer un paramètre *bbox* contennant latitude min et max, ainsi que longitude min et max de la zone à récuperer
    - sortie: fichier XML avec extension *.osm* qu'il faudra traiter afin d'obtenir une image (*rendering*)
  * Utiliser le **plugin osm** offert par Qt en utilisant QML sur QT:
    - entrée: latitude et longitude de l'endroit à faire apparaitre en utilsant un objet **QtPositioning**
    - sortie: on obtient le plan en utilisant un objet **QQmlApplicationEngine** pour le charger sur l'écran
    - E.g.: [Minimal Map (QML)](https://doc-snapshots.qt.io/qt5-5.9/qtlocation-minimal-map-example.html)

## API Carte [OpenRouteServices](https://openrouteservice.org/)

- Participant: Miguel
- Réalisation : non attribué
- Plusieurs services disponibles:
  * Directions:
    - Fournit différents profils: vélos, marche, rando, car, truck
  * Isochrones:
    - Aide à simuler les distances qui seront parcourues dans un temps donné.
  * POIs (*points of interest*)
    - Permet de trouver des points d'intêret (*POIs*) dans une zone donnée.
  * Autres à explorer: Matrix, Geocoding, Openmapsurfer
- API: requêtes via *http GET*
  * entrée: coordonnées du type *bbox* comme sur API OpenStreetMap (voir ci-dessus)
  * sortie: fichier json 
  * E.g [Get Direction](https://api.openrouteservice.org/directions?api_key=your-api-key&coordinates=8.34234%2C48.23424%7C8.34423%2C48.26424&profile=driving-car) 
  * Authentification obligatoire en envoyant une clé d'utilisateur (*paramètre api-key*) obtenue en s'inscrivant sur le site


##Ludovic Api trafic aerien en temps reel
- Participation : Ludovic
- Réalisation : marco 
https://opensky-network.org/
*sortie: Json

## API des Points d'interets
  - Participant: Marco
  - Réalisation : Ludovic


## API OpenPOIs
- API open source qui permet d'avoir les informations sur les  Point of interest en fonction de la zone geographique
- site http://openpoi.ogcnetwork.net/api.php
- request base url: http://openpois.net/poiquery.php?
- zone géographique mondiale
ENTREE
- unique id of the POI
- label du POI
- latitude, longitude, radius
- option de recherche :date de creation du POI/nombre maximum de POI

SORTIE
options de format: text/html, geojson, application/json or application/xml

API OpenPOIs implemente  l' API OGC Web Feature Service (WFS)
- WFS implémente l' API open source Mapserver's (https://mapserver.org/ogc/wfs_server.html) 
- WFS reconnait que certains champs de la POI son ID,  label & coordonnées géographiques.

Fontionnement de la base de données 
- Les requetes à la base de données sont réalisées par bounding box ou par nom  au standard de l'API WFS de OGC
- Chaque POI possède un RESTful URI permanent.
Les réponses des requetes sont retournées au format XML ou JSON en conformité W3C POIWG specification 


## API POI implémentée sur API OpenstreetMap (OSM)

- Voir la description de l'API OSM dans le fichier README

- Construction des POI sur la map OSM
The ideal way, however, is to download the OpenStreetMap data dump and filter it according to your needs. 
The data dump is called planet.osm. 
You can either download the whole world (really huge), or just an extract covering one country or state.
Once you've downloaded it, a Java program called Osmosis will extract the data for you,
 and either loading the result into a database, or outputting it as a file.

- les principales méthodes utilisées sont consultable à l'addresse:
- https://help.openstreetmap.org/questions/4065/getting-specific-poi-data-and-keeping-them-up-to-date
- https://medium.com/ibm-watson-data-lab/easy-access-to-all-points-of-interest-data-acc6569e45b2

Les outils pour la production et le traitement des données selon des critères de recherche des POI :
OpenDatasoft:https://public.opendatasoft.com/explore/?sort=modified

	
## API Sncf

 - Participant: Cheikh 
 - Réalisation : Cheikh
 - données de transport de plusieurs réseaux dans le monde (Île-de-France, Sa Francisco, Berlin, Nantes, NYC, Pays-Bas, etc.)
 - Cet API propose plusieurs services :
    - calcul des itinéraires
    - exploration des données
    - prochains départs
    - fiches horaires
 - Site: http://navitia.io/


## API ville la plus proche
 
- Participant: Kimcheng
- Réalisation : Kimcheng
- Permet d'avoir les informations sur la ville le plus proche
- Site: http://www.geobytes.com/get-nearby-cities-api/
- API
  - entrée: Le nom de la ville où se trouve l'utilisateur ou la longitude et la latitude
  - sortie: Le nom de la ville la plus proche, le pays, le chemin pour y aller et la distance entre la position actuelle et la ville
- Portée: le monde

## Api Space Track

- Participant: Julien 
- Réalisation : Li
- Description : Permet de localiser les satellites en temps réel
- Site: https://www.space-track.org/documentation#api
- API 
  - Pré-requis: obligation d'avoir un compte, pas plus de 20 requêtes par minute.
  - Entrée: URL, exemple: https://www.space-track.org/basicspacedata/query/class/boxscore/format/json
  - Sortie: plusieur formats disponibles (xml, json, html, csv, tle, 3le, kvn, stream)
- Portée: Monde

## Api OpenChargeMap

- Participant: Ludovic
- Réalisation : Khadim
- Open Charge Map le registre public mondial d'emplacements de recharge pour véhicules électriques
- Liste importantes de parametres possibles. Les plus utiles pour nous :
  - distance : return results based on specified distance from specified latitude/longitude 
  - distanceunit : Miles or KM
  - latitude reference for distance calculation
  - longitude reference for distance calculation
- On recupere des infos comme le nom, l'adresse, le contact (site internet, tel, mail)
- Site: https://openchargemap.org/site/develop/api
- API exemple : 
  - entrée: indique une URL https://api.openchargemap.io/v2/poi/?output=json&maxresults=10&latitude=48.85&longitude=2.33&&distance=1&distanceunit=KM
  - sortie: récupère un format JSON (xml, kml aussi mais ils recommandent JSON) 
  - Doc : https://openchargemap.org/site/develop/api
- Portée:
  - Monde: 130073 stations de recharge sur 64113 endroits.
- Difficulté : *

## Api EauFrance

- Participant: ...
- Description: Connaitre la qualité des cours d'eau
- Site: http://hubeau.eaufrance.fr/page/api-qualite-cours-deau-tuto

- API
  - Entrée: URL, exemple http://hubeau.eaufrance.fr/api/v1/qualite_rivieres/station_pc?libelle_commune=Longuyon&pretty
  - Sortie: Format JSON, on obtient beaucoup d'informations
   - le nom du cours d'eau
   - les coordonnées (latitude, longitude, code commune, département, etc)
   - la dureté de l'eau, la contenance en Nitrates, etc


