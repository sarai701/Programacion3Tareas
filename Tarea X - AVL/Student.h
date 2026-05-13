#ifndef STUDENT_H
#define STUDENT_H

#include <string>

struct Student {
    int student_id;
    std::string full_name;
    std::string career;
    int semester;
    float promedio;
    int skill_score;

    // Lógica de comparación de estudiantes
    // Retorna true si el estudiante actual es superior al otro(mayor score o desempate id)
    bool isGreaterThan(const Student& other) const {
        if (this->skill_score != other.skill_score) {
            return this->skill_score > other.skill_score;
        }
        return this->student_id > other.student_id; // Desempate por ID
    }
};

#endif
