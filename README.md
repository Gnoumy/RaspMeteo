# RaspMeteo

Pour que la mainwindow soit Resizeable :
Chercher le fichier ui_mainwindow.h dans le dossier correspondant au Kit utilisé.
Ce dossier commence par "build-"
Dans ce fichier faire les modifications suivantes :
	1) Ajouter la ligne #include <QtWidgets/QScrollArea>
	2) REMPLACER "QWidget *centralWidget;"
				par "QScrollArea *centralWidget;"
	3) REMPLACER "centralWidget = new QWidget(MainWindow);"
				par "centralWidget = new QScrollArea(MainWindow);"
