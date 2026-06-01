import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.TreeMap; 

public class BenchmarkMain {

    public static void main(String[] args) {
        String csvPath = "estudiantes.csv"; 
        String outputPath = "java_results.csv";
        int totalRegistros = 10000; // Volumen controlado para el benchmark
        
        long inicioCarga = System.nanoTime();
        
        // Estructuras nativas requeridas por la consigna
        HashMap<Integer, Estudiante> mapaEstudiantes = new HashMap<>(); // Vs Tabla Hash C++
        TreeMap<Integer, Estudiante> arbolTreeMap = new TreeMap<>();   // Vs Árbol AVL C++
        HashMap<Integer, List<Integer>> grafoNativo = new HashMap<>();   // Vs Grafo C++

        System.out.println("========== EJECUTANDO BENCHMARK EN JAVA ==========");

        // --- 1. MEDICIÓN DE INSERCIONES MASIVAS ---
        
        // Inserción en HashMap
        long startTime = System.nanoTime();
        cargarEstructura(csvPath, mapaEstudiantes, null, null, totalRegistros);
        double tInsertHash = (System.nanoTime() - startTime) / 1e6;

        // Inserción en TreeMap (AVL equivalente)
        startTime = System.nanoTime();
        cargarEstructura(csvPath, null, arbolTreeMap, null, totalRegistros);
        double tInsertAVL = (System.nanoTime() - startTime) / 1e6;

        // Inserción en Grafo (Vértices y relaciones basales)
        startTime = System.nanoTime();
        cargarEstructura(csvPath, null, null, grafoNativo, totalRegistros);
        double tInsertGrafo = (System.nanoTime() - startTime) / 1e6;

        // --- 2. MEDICIÓN DE BÚSQUEDAS INDIVIDUALES ---
        int idABuscar = 5000; // ID intermedio representativo

        // Búsqueda en Tabla Hash (HashMap)
        startTime = System.nanoTime();
        Estudiante bHash = mapaEstudiantes.get(idABuscar);
        double tSearchHash = (System.nanoTime() - startTime) / 1e6;

        // Búsqueda en AVL (TreeMap)
        startTime = System.nanoTime();
        Estudiante bAVL = arbolTreeMap.get(idABuscar);
        double tSearchAVL = (System.nanoTime() - startTime) / 1e6;

        // Búsqueda en Grafo
        startTime = System.nanoTime();
        boolean existeVertice = grafoNativo.containsKey(idABuscar);
        double tSearchGrafo = (System.nanoTime() - startTime) / 1e6;

        // --- 3. MEDICIÓN DE RECORRIDOS ---
        
        // Recorrido InOrden en TreeMap (Al iterar sobre sus valores ya vienen ordenados por clave de forma nativa)
        startTime = System.nanoTime();
        List<Estudiante> recorridoInOrden = new ArrayList<>(arbolTreeMap.values());
        double tTraversalAVL = (System.nanoTime() - startTime) / 1e6;

        // Recorrido BFS Silencioso en el Grafo
        startTime = System.nanoTime();
        bfsSilencioso(1001, grafoNativo); 
        double tTraversalGrafo = (System.nanoTime() - startTime) / 1e6;
        
        double tiempoCargaTotal =
                (System.nanoTime() - inicioCarga) / 1e6;
        
     // --- 4. EXPORTACIÓN AUTOMÁTICA AL ARCHIVO CSV (Formato con Punto Decimal Seguro) ---
        try (PrintWriter pw = new PrintWriter(new FileWriter(outputPath))) {
            // Cabecera exacta solicitada
            pw.println("language,operation,structure,records,time_ms");
            
            // Usamos java.util.Locale.US para garantizar que los decimales se separen con '.' y no con ','
            // Registros de Inserción
            pw.printf(java.util.Locale.US, "Java,insert,HashMap,%d,%.4f\n", mapaEstudiantes.size(), tInsertHash);
            pw.printf(java.util.Locale.US, "Java,insert,TreeMap,%d,%.4f\n", arbolTreeMap.size(), tInsertAVL);
            pw.printf(java.util.Locale.US, "Java,insert,Grafo,%d,%.4f\n", grafoNativo.size(), tInsertGrafo);
            
            // Registros de Búsqueda
            pw.printf(java.util.Locale.US, "Java,search,HashMap,%d,%.4f\n", mapaEstudiantes.size(), tSearchHash);
            pw.printf(java.util.Locale.US, "Java,search,TreeMap,%d,%.4f\n", arbolTreeMap.size(), tSearchAVL);
            pw.printf(java.util.Locale.US, "Java,search,Grafo,%d,%.4f\n", grafoNativo.size(), tSearchGrafo);
            
            // Registros de Recorridos
            pw.printf(java.util.Locale.US, "Java,traversal,TreeMap,%d,%.4f\n", arbolTreeMap.size(), tTraversalAVL);
            pw.printf(java.util.Locale.US, "Java,traversal,Grafo,%d,%.4f\n", grafoNativo.size(), tTraversalGrafo);
            System.out.println("[Éxito] Archivo " + outputPath);
        } catch (IOException e) {
            System.err.println("Error al escribir el archivo csv: " + e.getMessage());
        }

        System.out.println("================================================");
        System.out.println("Benchmark finalizado de manera correcta.");
        System.out.println("Tiempo total de carga: "
                + tiempoCargaTotal + " ms");
    }

    
    //Función modular encargada de aislar la carga limpia por estructura
    private static void cargarEstructura(String path, HashMap<Integer, Estudiante> hash, TreeMap<Integer, Estudiante> tree, HashMap<Integer, List<Integer>> grafo, int maxRecords) {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            br.readLine(); // Saltar cabecera
            String line;
            int count = 0;
            while ((line = br.readLine()) != null && count < maxRecords) {
                if (line.trim().isEmpty()) continue;
                String[] data = line.split(",");
                if (data.length >= 3) {
                    try {
                        int id = Integer.parseInt(data[0].replace("\"", "").trim());
                        String nombre = data[1].replace("\"", "").trim();
                        int score = 0;
                        String columnaScore = data[2].replace("\"", "").trim();
                        
                        if (columnaScore.matches("-?\\d+")) {
                            score = Integer.parseInt(columnaScore);
                        } else if (data.length >= 4) {
                            score = Integer.parseInt(data[3].replace("\"", "").trim());
                        }

                        Estudiante est = new Estudiante(id, nombre, score);

                        if (hash != null) hash.put(id, est);
                        if (tree != null) tree.put(id, est);
                        if (grafo != null) grafo.put(id, new ArrayList<>());
                        count++;
                    } catch (NumberFormatException e) {
                        // Omitir líneas con datos corruptos
                    }
                }
            }
            
            // Si es grafo, generamos relaciones secuenciales controladas en memoria
            if (grafo != null) {
                for (Integer id : grafo.keySet()) {
                    if (grafo.containsKey(id + 1)) {
                        grafo.get(id).add(id + 1);
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Error leyendo CSV: " + e.getMessage());
        }
    }

    
    private static void bfsSilencioso(int startId, HashMap<Integer, List<Integer>> grafo) {
        if (!grafo.containsKey(startId)) return;
        
        HashSet<Integer> visitados = new HashSet<>();
        Queue<Integer> cola = new LinkedList<>();
        
        visitados.add(startId);
        cola.add(startId);
        
        while (!cola.isEmpty()) {
            int actual = cola.poll();
            List<Integer> vecinos = grafo.get(actual);
            if (vecinos != null) {
                for (int vecino : vecinos) { // Variable unificada correctamente
                    if (!visitados.contains(vecino)) {
                        visitados.add(vecino);
                        cola.add(vecino); // ¡Solucionado aquí!
                    }
                }
            }
        }
    }
}