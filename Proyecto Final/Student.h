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

    // Métodos para la gestión manual de la lista de proyectos
    bool addProject(int id, std::string title, std::string desc, int year) {
        // Validación obligatoria: No permitir project_id duplicados en este estudiante
        Project* temp = projectsHead;
        while (temp) {
            if (temp->project_id == id) {
                return false; // Duplicado detectado
            }
            temp = temp->next;
        }

        // Insertar al inicio de la lista enlazada (eficiencia O(1))
        Project* newProj = new Project(id, title, desc, year);
        newProj->next = projectsHead;
        projectsHead = newProj;
        return true;
    }

    void displayProjects() {
        if (!projectsHead) {
            std::cout << "El estudiante no tiene proyectos registrados.\n";
            return;
        }
        Project* temp = projectsHead;
        std::cout << "--- Proyectos de " << full_name << " ---\n";
        while (temp) {
            std::cout << "ID: " << temp->project_id << " | Titulo: " << temp->title << "\n"
                      << "   Descripcion: " << temp->description << "\n"
                      << "   Ano de Finalizacion: " << temp->completion_year << "\n"
                      << "----------------------------------------\n";
            temp = temp->next;
        }
    }

    bool removeProject(int id) {
        Project* temp = projectsHead;
        Project* prev = nullptr;

        while (temp) {
            if (temp->project_id == id) {
                if (prev == nullptr) {
                    projectsHead = temp->next; // Era la cabeza
                } else {
                    prev->next = temp->next; // Desenlazar nodo intermedio o final
                }
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false; // No encontrado
    }

    bool isGreaterThan(const Student& other) const {
        if (this->skill_score != other.skill_score) {
            return this->skill_score > other.skill_score;
        }
        return this->student_id > other.student_id;
    }
};

#endif
