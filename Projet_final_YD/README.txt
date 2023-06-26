PROJET_FINAL_YD

Pré-requis avant installation du projet:
    -ubuntu: "22.04",
    -python: "3.9.16",
        sudo apt update
        sudo apt install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev wget libbz2-dev
        wget https://www.python.org/ftp/python/3.9.16/Python-3.9.16.tgz
        tar -xf Python-3.9.16.tgz
        cd Python-3.9.16
        ./configure --enable-optimizations
        make -j 12
        sudo make altinstall
        python3.9 --version

    -gcc: "11.3.0",
        dpkg -l gcc*,
        add-apt-repository ppa:ubuntu-toolchain-r/test
        apt-get update
        apt-get install gcc-11.3.0 g++-11.3.0
        update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11.3.0 60 --slave /usr/bin/g++ g++ /usr/bin/g++-11.3.0

Cloner le projet "https://dev.azure.com/YannDUFAURE/_git/Projet_final_YD" dans votre un dossier local, 
    git Clone

Pour faire fonctionner le projet, vous devez utiliser ces librairies:
    -jansson:
        sudo apt-get install -y libjansson-dev
    -sqlite3: 
        sudo apt-get install sqlite3
        sudo apt-get install libsqlite3-dev
    -pthread:
        sudo apt-get install libpthread-stubs0-dev
    -CUnit:
        sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev


Création de la table meteo,
    >sqlite3
    >DROP TABLE IF EXISTS 'meteo'

    CREATE TABLE IF NOT EXISTS 'meteo' ( 
        'id' INTEGER NOT NULL UNIQUE, 
        'villes' TEXT NOT NULL, 
        'pays' TEXT NOT NULL, 
        'temperature' NUMERIC NOT NULL, 
        'temperature_min' NUMERIC NOT NULL, 
        'temperature_max' NUMERIC NOT NULL, 
        'weather' TEXT NOT NULL, 
        'date' INTEGER NOT NULL, 
        'date_txt' TEXT NOT NULL, 
        PRIMARY KEY('id') 
    )

Les informations à modifier sont dans le fichier "config.json".
En utilisant l'API OpenWeather, vous devez vous créez un compte sur  "https://openweathermap.org/api" pour obtenir une Key,
cette Key est à founir dans config.json, "API_Openweather" -"> "appid"

Ne pas oublier de créer un répertoire fichiers_historiques pour les fichiers .csv créés dans bdd_thread.c:
    mkdir assets
    cd assets
    mkdir fichiers_historiques

Pour lancer le projet:
    --> Ouvrir un terminal à l'adresse du projet:
        cd python
        python3 script.py
    --> Ouvrir un autre terminal à l'adresse du projet:
        cd programm_c
        gcc -o main bdd_thread.c main.c bdd.c json.c logMessage.c -lpthread -ljansson -lsqlite3 -lcunit
        ./main

Pour lancer les tests:
    Ouvrir un terminal à l'adresse du projet:
        cd python
        python3 test_bdd_thread.py
    Pour lancer test_json.c:
        gcc -o test_json test_json.c logMessage.c json.c -ljansson -lcunit
        ./test_json

