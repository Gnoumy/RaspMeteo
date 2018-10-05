# Liste des resources trouvées 

## Liste des villes 

- Base de données des villes contenant plus d'un million de villes par le monde
- Donne la région, le code languE, la longitude la latitude , le nom et la population de la ville
- Site : https://www.maxmind.com/fr/free-world-cities-database

## Liste des POI 

http://www.openpoimap.org

## Liste des points de recharge pour véhicule électrique 

https://openchargemap.org

## Liste des routes 

https://openrouteservice.org/


## Api la liste des accidents vols, agression autour de une adresse 
Participant:Li

Cherchez la liste des accidents, vols, agressions autour de cette adresse ou clicker sur la carte. Voir les quartiers dangereux, la sécurité autour des colléges et musées

API

entree: clicker sur la carte ou donner une addresse

sortie:		
Liste des zones ayant un nombre élevé de faits divers 



## Api Pollution

- Participant: Julien
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

-Donnees meteo journaliere en fonction de la latitude et longitude:
  -http://api.openweathermap.org/data/2.5/weather?lat=40&lon=3&appid=3543ac0c00624ed3bb653359621e5344 :
    - http://api.openweathermap.org/data/2.5 => prefix de l'adresse API
	 - /weather? => type d'API utilisé sur OPENWEATHERMAP
	 - lat=40&long3 => coodonnees lattitude et longitude permettant la geolocalisation 
	 - &appid=3543ac0c00624ed3bb653359621e5344 => clef API permmettant l'utilisation de l'API OPENWEATHERMAP


## Api Carte OpenStreeMap
- Participant: Miguel
- Ils existent deux possibilités:	
  * Utiliser la API de [OpenStreetMap] (https://www.openstreetmap.org/about)
    - API v.06: https://wiki.openstreetmap.org/wiki/API_v0.6
    - entrée: indiquer un paramètre *bbox* contennant latitude min et max, ainsi que longitude min et max de la zone à récuperer
    - sortie: fichier XML avec extension *.osm* qu'il faudra traiter afin d'obtenir une image (*rendering*)
  * Utiliser le **plugin osm** offert par Qt en utilisant QML sur QT:
    - entrée: latitude et longitude de l'endroit à faire apparaitre en utilsant un objet **QtPositioning**
    - sortie: on obtient le plan en utilisant un objet **QQmlApplicationEngine** pour le charger sur l'écran 	
    - E.g.: [Minimal Map (QML)](https://doc-snapshots.qt.io/qt5-5.9/qtlocation-minimal-map-example.html)	

## Api Carte Google
- Participant: Miguel	
- Service payant: https://cloud.google.com/maps-platform/


##Ludovic Api trafic aerien en temps reel
https://opensky-network.org/
*sortie: Json

## API POI

 - https://public.opendatasoft.com/explore/dataset/points-dinterets-openstreetmap-en-france/api/
 - https://developers.google.com/places/web-service/search
	
## API Sncf

 - Site: //api.sncf.com/v1


## API ville la plus proche
 
- Participant: Kimcheng
- Permet d'avoir les informations sur la ville le plus proche
- Site: http://www.geobytes.com/get-nearby-cities-api/
- API
  - entrée: Le nom de la ville où se trouve l'utilisateur
  - sortie: Le nom de la ville la plus proche, le pays, le chemin pour y aller et la distance entre la position actuelle et la ville
- Portée: le monde
