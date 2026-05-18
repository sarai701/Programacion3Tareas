#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

struct Project {
    int project_id;           // ID único del proyecto
    std::string title;        // Título del proyecto
    std::string description;  // Descripción breve
    int completion_year;      // Año de finalización
    Project* next;            // Puntero al siguiente proyecto (Lista Enlazada)

    // Constructor para inicializar proyectos fácilmente
    Project(int id, std::string t, std::string d, int y)
        : project_id(id), title(t), description(d), completion_year(y), next(nullptr) {}
};


struct Student {
    // Datos provenientes del CSV
    int student_id;         // Identificador único (Clave para Hash)
    std::string full_name;  // Nombre completo
    std::string career;     // Carrera universitaria
    int semester;           // Semestre actual
    float gpa;              // Promedio académico (antes 'promedio')
    int skill_score;        // Puntaje para el Ranking (Clave para AVL)

    // Lista de proyectos asociada al estudiante
    Project* projectsHead;

    // Constructor por defecto para inicializar valores limpios
    Student() : student_id(0), semester(0), gpa(0.0f), skill_score(0), projectsHead(nullptr) {}

    bool isGreaterThan(const Student& other) const {
        if (this->skill_score != other.skill_score) {
            return this->skill_score > other.skill_score;
        }
        return this->student_id > other.student_id;
    }
};

#endif
