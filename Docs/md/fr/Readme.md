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

Site: http://ddata.over-blog.com/xxxyyy/1/26/64/19/Paris/site02-Geo-VH92.html?Address=XX492%20ANTONY

API

entree: donner une addresse, departement, ville, rue etc.

sortie:		
Liste des zones ayant un nombre élevé de faits divers 

## Api Système d'information géographique de la politique de la ville

Participant:Li

Site: https://sig.ville.gouv.fr/

API

entree: donner une addresse, code postal, nom de la ville, nom de la voie et numero dans la voie.

sortie: 
Si l'adresse est identifiée comme étant située dans un quartier, l’utilisateur obtient une réponse positive.
Si l'adresse est identifiée comme étant située hors quartier, l’utilisateur obtient une réponse négative. 
Si la recherche est sans résultat, un message en informe l’utilisateur.

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

- Donnees meteo journaliere en fonction de la latitude et longitude:
  - http://api.openweathermap.org/data/2.5/weather?lat=40&lon=3&appid=3543ac0c00624ed3bb653359621e5344 :
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

 - Participant: Cheikh 
 - données de transport de plusieurs réseaux dans le monde (Île-de-France, Sa Francisco, Berlin, Nantes, NYC, Pays-Bas, etc.)
 - Cet API propose plusieurs services :
    - calcul des itinéraires
    - exploration des données
    - prochains départs
    - fiches horaires
 - Site: http://navitia.io/


## API ville la plus proche
 
- Participant: Kimcheng
- Permet d'avoir les informations sur la ville le plus proche
- Site: http://www.geobytes.com/get-nearby-cities-api/
- API
  - entrée: Le nom de la ville où se trouve l'utilisateur ou la longitude et la latitude
  - sortie: Le nom de la ville la plus proche, le pays, le chemin pour y aller et la distance entre la position actuelle et la ville
- Portée: le monde

## Api Space Track
- Participant: ...
- Description : Permet de localiser les satellites en temps réel
- Site: https://www.space-track.org/documentation#api
- API 
  - Pré-requis: obligation d'avoir un compte, pas plus de 20 requêtes par minute.
  - Entrée: URL, exemple: https://www.space-track.org/basicspacedata/query/class/boxscore/format/json
  - Sortie: plusieur formats disponibles (xml, json, html, csv, tle, 3le, kvn, stream)
- Portée: Monde

## Api OpenChargeMap

- Participant: Ludovic
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

