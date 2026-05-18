#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Student.h"
#include "HashTable.h"
#include "AVL.h"

class CSVReader {
public:
    static void loadStudents(std::string fileName, HashTable& hashRef, AVLTree& avlRef) {
        std::ifstream file(fileName);
        std::string line, word;

        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
            return;
        }

        // Omitir la primera línea
        std::getline(file, line);

        int loadedCount = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Student s;
            std::string temp;

            // Leer cada columna separada por comas según la estructura exacta del dataset
            std::getline(ss, temp, ','); s.student_id = std::stoi(temp);
            std::getline(ss, s.full_name, ',');
            std::getline(ss, s.career, ',');
            std::getline(ss, temp, ','); s.semester = std::stoi(temp);
            std::getline(ss, temp, ','); s.gpa = std::stof(temp);
            std::getline(ss, temp, ','); s.skill_score = std::stoi(temp);

            // Insertar en ambas estructuras simultáneamente
            hashRef.insert(s);
            avlRef.insert(s);

            loadedCount++;
        }

        file.close();
        std::cout << ">>> Se cargaron " << loadedCount << " estudiantes exitosamente." << std::endl;
    }
};

#endif
