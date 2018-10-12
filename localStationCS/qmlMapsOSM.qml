import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {

    property double qlatitude: 48.85341     //Paris latitude
    property double qlongitude: 2.3488      //Paris longitude

    width: 800; height: 480

    Plugin {
        id: osmPlugin
        name: "osm"
        objectName: "plugin"

        PluginParameter { name: "osm.mapping.host"; value: "https://tile.openstreetmap.org/" }
        PluginParameter { name: "osm.geocoding.host"; value: "https://nominatim.openstreetmap.org" }
        PluginParameter { name: "osm.routing.host"; value: "https://router.project-osrm.org/viaroute" }
        PluginParameter { name: "osm.places.host"; value: "https://nominatim.openstreetmap.org/search" }
        //PluginParameter { name: "osm.mapping.copyright"; value: "" }
        //PluginParameter { name: "osm.mapping.highdpi_tiles"; value: true }
    }

    Map {
        anchors.fill: parent
        plugin: osmPlugin
        center: QtPositioning.coordinate(qlatitude, qlongitude) // Paris
        zoomLevel: 15
        minimumZoomLevel: 10
        maximumZoomLevel: 20
    }
}
