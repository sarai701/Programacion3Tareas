import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class BenchmarkMain {

    public static void main(String[] args) {
        String csvPath = "estudiantes.csv"; 
        
        HashMap<Integer, Estudiante> mapaEstudiantes = new HashMap<>();
        List<Estudiante> rankingEstudiantes = new ArrayList<>();

        System.out.println("========== INICIANDO BENCHMARK JAVA ==========");

        long startTimeCarga = System.nanoTime();
        int lineasConError = 0;
        
        try (BufferedReader br = new BufferedReader(new FileReader(csvPath))) {
            String line;
            // Leer encabezado para saltarlo
            br.readLine(); 
            
            while ((line = br.readLine()) != null) {
                // Si la línea está vacía, saltarla
                if (line.trim().isEmpty()) continue;
                
                // Separar los campos por comas
                String[] data = line.split(",");
                
                try {
                    if (data.length >= 3) {
                        // Limpiamos espacios y posibles comillas residuales del CSV
                        int id = Integer.parseInt(data[0].replace("\"", "").trim());
                        String nombre = data[1].replace("\"", "").trim();
                        
                        // Buscamos el score de forma dinámica:
                        // Si data[2] es numérico, lo toma. Si es texto (carrera), busca en data[3]
                        int score = 0;
                        String columnaScore = data[2].replace("\"", "").trim();
                        
                        if (columnaScore.matches("-?\\d+")) {
                            score = Integer.parseInt(columnaScore);
                        } else if (data.length >= 4) {
                            score = Integer.parseInt(data[3].replace("\"", "").trim());
                        }
                        
                        Estudiante est = new Estudiante(id, nombre, score);
                        
                        mapaEstudiantes.put(id, est);
                        rankingEstudiantes.add(est);
                    }
                } catch (NumberFormatException nfe) {
                    lineasConError++;
                }
            }
        } catch (IOException e) {
            System.err.println("Error crítico al abrir el archivo: " + e.getMessage());
            return;
        }
        
        long endTimeCarga = System.nanoTime();
        double tiempoCargaMs = (endTimeCarga - startTimeCarga) / 1e6;
        System.out.printf("Tiempo de Carga e Inserción Masiva: %.4f ms\n", tiempoCargaMs);

        // 2. Medición de busquedad  (HashMap)
        // Buscaremos IDs aleatorios distribuidos para medir de manera justa
        int[] idsABuscar = {10, 5000, 25000, 100000, 180000}; 
        
        long startTimeBusqueda = System.nanoTime();
        for (int id : idsABuscar) {
            Estudiante encontrado = mapaEstudiantes.get(id); 
        }
        long endTimeBusqueda = System.nanoTime();
        double tiempoBusquedaMs = (endTimeBusqueda - startTimeBusqueda) / 1e6;
        System.out.printf("Tiempo de Búsqueda (Acceso directo O(1)): %.4f ms\n", tiempoBusquedaMs);

        // 3. Medición de ranking (Simulando AVL)

        long startTimeRanking = System.nanoTime();
        rankingEstudiantes.sort((e1, e2) -> Integer.compare(e2.getSkillScore(), e1.getSkillScore()));
        
        long endTimeRanking = System.nanoTime();
        double tiempoRankingMs = (endTimeRanking - startTimeRanking) / 1e6;
        System.out.printf("Tiempo de Generación de Ranking (Ordenamiento): %.4f ms\n", tiempoRankingMs);

        System.out.println("==============================================");
        System.out.println("Total de registros procesados con éxito: " + mapaEstudiantes.size());
        if (lineasConError > 0) {
            System.out.println("Líneas omitidas por inconsistencia de formato: " + lineasConError);
        }
        System.out.println("Benchmark completado.");
    }
}