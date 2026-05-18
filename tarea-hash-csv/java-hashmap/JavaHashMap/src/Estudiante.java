public class Estudiante {
    public int studentId;
    public String fullName;
    public String career;
    public int semester;
    public double gpa;
    public int skillScore;

    public Estudiante(int id, String name, String career, int sem, double gpa, int score) {
        this.studentId = id;
        this.fullName = name;
        this.career = career;
        this.semester = sem;
        this.gpa = gpa;
        this.skillScore = score;
    }

    public String toString() {
        return "ID: " + studentId + 
               " | Estudiante: " + fullName + 
               " | Carrera: " + career + 
               " | Semestre: " + semester + 
               " | GPA: " + gpa + 
               " | Skill Score: " + skillScore;
    }
}