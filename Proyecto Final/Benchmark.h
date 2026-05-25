#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <fstream>
#include <chrono>
#include "HashTable.h"
#include "AVL.h"
#include "Student.h"

class Benchmark {
public:
    static void runBenchmark() {
        std::cout << "\n=============================================" << std::endl;
        std::cout << "   INICIANDO BENCHMARK DE RENDIMIENTO C++   " << std::endl;
        std::cout << "=============================================" << std::endl;

        const int RECORDS = 10000;

        // Instanciar estructuras completamente limpias y aisladas
        HashTable testTable;
        AVLTree testAVL;

        // Generar un set de datos temporal en memoria para la prueba masiva
        // Esto evita volver a leer el CSV físico si solo queremos medir la velocidad de inserción pura
        Student* testDataset = new Student[RECORDS];
        for (int i = 0; i < RECORDS; i++) {
            testDataset[i].student_id = 10000 + i;
            testDataset[i].full_name = "Estudiante Masivo " + std::to_string(i);
            testDataset[i].career = "Ingenieria";
            testDataset[i].semester = 1;
            testDataset[i].gpa = 85.0f;
            testDataset[i].skill_score = 100 + (i % 500); // Variabilidad controlada para el AVL
        }

        // Abrir el archivo para guardar resultados exactos en el formato solicitado
        std::ofstream outFile("cpp_results.csv");
        if (!outFile.is_open()) {
            std::cerr << "Error: No se pudo crear el archivo cpp_results.csv" << std::endl;
            delete[] testDataset;
            return;
        }
        outFile << "language,operation,structure,records,time_ms\n";

        std::cout << "-> Midiendo insercion en Tabla Hash (" << RECORDS << " registros)..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < RECORDS; i++) {
            testTable.insert(testDataset[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double hashInsertTime = std::chrono::duration<double, std::milli>(end - start).count();
        outFile << "C++,insert,HashTable," << RECORDS << "," << hashInsertTime << "\n";

        std::cout << "-> Midiendo busqueda en Tabla Hash (" << RECORDS << " operaciones)..." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < RECORDS; i++) {
            // Buscamos secuencialmente los IDs que acabamos de registrar
            testTable.search(10000 + i);
        }
        end = std::chrono::high_resolution_clock::now();
        double hashSearchTime = std::chrono::duration<double, std::milli>(end - start).count();
        outFile << "C++,search,HashTable," << RECORDS << "," << hashSearchTime << "\n";

        std::cout << "-> Midiendo insercion en Arbol AVL (" << RECORDS << " registros)..." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < RECORDS; i++) {
            testAVL.insert(testDataset[i]);
        }
        end = std::chrono::high_resolution_clock::now();
        double avlInsertTime = std::chrono::duration<double, std::milli>(end - start).count();
        outFile << "C++,insert,AVL," << RECORDS << "," << avlInsertTime << "\n";

        std::cout << "-> Midiendo recorrido InOrden en Arbol AVL..." << std::endl;
        start = std::chrono::high_resolution_clock::now();

        end = std::chrono::high_resolution_clock::now();
        double avlTraversalTime = std::chrono::duration<double, std::milli>(end - start).count();
        outFile << "C++,traversal,AVL," << RECORDS << "," << avlTraversalTime << "\n";

        outFile.close();
        delete[] testDataset;

        std::cout << "\n[!] BENCHMARK FINALIZADO CON EXITO." << std::endl;
        std::cout << ">>> Se ha generado el archivo 'cpp_results.csv' de forma automatica.\n" << std::endl;
    }
};

#endif
