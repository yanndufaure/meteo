DROP TABLE IF EXISTS 'meteo'

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


