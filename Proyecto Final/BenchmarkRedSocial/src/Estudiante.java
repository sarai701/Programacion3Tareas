public class Estudiante {
    private int studentId;
    private String fullName;
    private int skillScore; // Usado para el Ranking

    public Estudiante(int studentId, String fullName, int skillScore) {
        this.studentId = studentId;
        this.fullName = fullName;
        this.skillScore = skillScore;
    }

    // Getters necesarios para el procesamiento y ordenamiento
    public int getStudentId() { return studentId; }
    public String getFullName() { return fullName; }
    public int getSkillScore() { return skillScore; }

    public String toString() {
        return "ID: " + studentId + " | Nombre: " + fullName + " | Score: " + skillScore;
    }
}