//Priscila Guzmán
#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "HashTable.h"
#include "AVL.h"
#include "Graph.h"
#include "Student.h"

class Benchmark {
public:
    static void runBenchmark() {
        std::cout << "\n=============================================" << std::endl;
        std::cout << "    INICIANDO BENCHMARK DE RENDIMIENTO C++   " << std::endl;
        std::cout << "=============================================" << std::endl;

        const int RECORDS = 10000;

        HashTable testTable;
        AVLTree testAVL;
        Graph testGraph;

        Student* testDataset = new Student[RECORDS];
        for (int i = 0; i < RECORDS; i++) {
            testDataset[i].student_id = 10000 + i;
            testDataset[i].full_name = "Estudiante Masivo " + std::to_string(i);
            testDataset[i].career = "Ingenieria";
            testDataset[i].semester = 1;
            testDataset[i].gpa = 85.0f;
            testDataset[i].skill_score = 100 + (i % 500);
        }

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
        testAVL.runSilentTraversal();
        end = std::chrono::high_resolution_clock::now();
        double avlTraversalTime = std::chrono::duration<double, std::milli>(end - start).count();
        outFile << "C++,traversal,AVL," << RECORDS << "," << avlTraversalTime << "\n";

        std::cout << "-> Inicializando nodos y aristas en el Grafo..." << std::endl;
        for (int i = 0; i < RECORDS; i++) {
            testGraph.addStudentVertex(testDataset[i].student_id);
        }
        for (int i = 0; i < RECORDS - 1; i++) {
            testGraph.connectStudents(testDataset[i].student_id, testDataset[i+1].student_id, true);
        }

        std::cout << "-> Midiendo recorrido BFS en Grafo..." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        testGraph.bfsSilencioso(10000);
        end = std::chrono::high_resolution_clock::now();
        double graphBfsTime = std::chrono::duration<double, std::milli>(end - start).count();
        outFile << "C++,bfs,Graph," << RECORDS << "," << graphBfsTime << "\n";

        std::cout << "-> Midiendo recorrido DFS en Grafo..." << std::endl;
        start = std::chrono::high_resolution_clock::now();

        testGraph.dfsSilencioso(10000);
        end = std::chrono::high_resolution_clock::now();
        double graphDfsTime = std::chrono::duration<double, std::milli>(end - start).count();
        outFile << "C++,dfs,Graph," << RECORDS << "," << graphDfsTime << "\n";

        outFile.close();
        delete[] testDataset;

        std::cout << "\n[!] BENCHMARK FINALIZADO CON EXITO." << std::endl;
        std::cout << ">>> Se ha generado el archivo 'cpp_results.csv' con todas las metricas solicitadas.\n" << std::endl;
    }
};

#endif
