import unittest
import os
import subprocess
from script import confList

class TestBddThread(unittest.TestCase):
    def test_csv_files_created(self):
        # Exécution du code principal dans un processus séparé
        process = subprocess.Popen(["./bdd_thread"], cwd="/home/yannd/Documents/AUSY/Projet_final_YD/programme_C/bdd_thread.c")
        process.wait()

        # Vérification de l'existence des fichiers CSV pour chaque ville
        villes = confList["ville"]
        fichierHistorique = "../assets/fichiers_historiques"
        for ville in villes:
            filePath = f"{fichierHistorique}/{ville}.csv"
            self.assertTrue(os.path.isfile(filePath))

    def test_csv_files_content(self):
        # Exécution du code principal dans un processus séparé
        process = subprocess.Popen(["./bdd_thread"], cwd="/home/yannd/Documents/AUSY/Projet_final_YD/programme_C/bdd_thread.c")
        process.wait()

        # Vérification du contenu des fichiers CSV pour chaque ville
        villes = confList["ville"]
        fichierHistorique = "../assets/fichiers_historiques"
        expected_headers = "id, ville, pays, temperature, temperature_min, temperature_max, weather, date, date_txt\n"
        for ville in villes:
            filePath = f"{fichierHistorique}/{ville}.csv"
            with open(filePath, "r") as file:
                headers = file.readline()
                self.assertEqual(headers, expected_headers)
                pass

if __name__ == "__main__":
    unittest.main()
