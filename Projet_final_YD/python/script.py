import requests
import json
import sqlite3
import time
from datetime import datetime

fichierConf = open('/home/yannd/Documents/AUSY/Projet_final_YD/config.json', 'r')       #ouvrir le fichier de config en JSON
jsonContent = fichierConf.read()                #lire le fichier de config
confList = json.loads(jsonContent)              #faire une liste exploitable en python

def execute_script():                           #initialisation pour executer le script une fois par heure

    results = []                                # Liste pour stocker les résultats de chaque requête API

    for ville in confList['villes']:            #boucle du tableau des villes dans le fichier de config
        r = requests.get(url=confList['API_Openweather']['api_url'], params=dict(q=ville, units='metric', lang='fr', APPID=confList['API_Openweather']['appid']))
        res = r.json()
        results.append(res)                     #requête vers l'API openweather, r en JSON

    baseDeDonnees = sqlite3.connect(confList['chemin'])    #connexion avec la BDD
    curseur = baseDeDonnees.cursor()
    sql = "DELETE FROM meteo"                   #On vide la table météo pour n'avoir que les dernières données de l'API sur la BDD
    curseur.execute(sql)
    print("Table meteo vidée")
    
    for item in results:
        description = item['weather'][0]['description']
        sql2 = "INSERT INTO meteo VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"
        valeurs = (
            item['id'],
            item['name'],
            item['sys']['country'],
            item['main']['temp'],
            item['main']['temp_min'],
            item['main']['temp_max'],
            description, 
            item['dt'],
            datetime.fromtimestamp(item['dt'])
        )
        curseur.execute(sql2, valeurs)          #requête SQL pour insérer les bonnes données au bon endroit dans la table

    baseDeDonnees.commit()
    baseDeDonnees.close()
    print("valeurs insérées")

execute_script()

while True:
    time.sleep(int(confList['timer']))          #timer pour exécuter le script une fois par heure
    execute_script()