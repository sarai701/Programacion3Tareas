import java.util.HashMap;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;

public class Main {
    public static void main(String[] args) {
        System.out.println("NOMBRE: Priscila Guzmán");
        System.out.println("CARNE: 9941-23-450");
        System.out.println("-----------------------------------");

        //HashMap con clave Integer y valor Estudiante
        HashMap<Integer, Estudiante> mapa = new HashMap<>();

        //Estudiantes desde el archivo .csv
        try (BufferedReader br = new BufferedReader(new FileReader("estudiantes.csv"))) {
            String line;
            br.readLine();
            
            while ((line = br.readLine()) != null) {
                //Dividir la línea por comas
                String[] datos = line.split(",");
                
                //Extraer datos
                int id = Integer.parseInt(datos[0].trim());
                String nombre = datos[1].trim();
                String carrera = datos[2].trim();
                int semestre = Integer.parseInt(datos[3].trim());
                double promedio = Double.parseDouble(datos[4].trim().replace(',', '.'));
                int score = Integer.parseInt(datos[5].trim());

                //Validar que no se inserten estudiantes duplicados
                if (!mapa.containsKey(id)) {
                    mapa.put(id, new Estudiante(id, nombre, carrera, semestre, promedio, score));
                }
            }
            //Mostrar total cargado
            System.out.println("Total de registros: " + mapa.size());
            
        } catch (Exception e) {
            System.out.println("Error al procesar el CSV: " + e.getMessage());
        }

        Scanner sc = new Scanner(System.in);
        int menu = 0;

        while (menu != 3) {
            System.out.println("\n--- SISTEMA DE GESTION ---");
            System.out.println("1. Buscar estudiante por ID");
            System.out.println("2. Eliminar estudiante por ID");
            System.out.println("3. Salir");
            System.out.print("Seleccione una opcion: ");
            menu = sc.nextInt();

            if (menu == 1) {
                //Permitir buscar
                System.out.print("Ingrese el ID a buscar: ");
                int idBusca = sc.nextInt();
                if (mapa.containsKey(idBusca)) {
                    System.out.println("RESULTADO: " + mapa.get(idBusca));
                } else {
                    System.out.println("Error: El estudiante con ID " + idBusca + " no existe.");
                }
            } 
            else if (menu == 2) {
                //Permitir eliminar
                System.out.print("Ingrese el ID a eliminar: ");
                int idBorra = sc.nextInt();
                if (mapa.containsKey(idBorra)) {
                    mapa.remove(idBorra);
                    System.out.println("EXITO: Estudiante eliminado.");
                    System.out.println("Total actual de estudiantes: " + mapa.size());
                } else {
                    System.out.println("Error: No se encontro el ID para eliminar.");
                }
            }
        }
        System.out.println("Cerrando sistema...");
        sc.close();
    }
}