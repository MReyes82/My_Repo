package escuelaClases;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Control {
    public static ArrayList<Grupo> grupos;
    public static ArrayList<Alumno> estudiantes;
    public static ArrayList<Maestro> profesores;

    public static void inicializarArreglos() {
        grupos = new ArrayList<>();
        estudiantes = new ArrayList<>();
        profesores = new ArrayList<>();
    }

    public static void agregarGrupo(Grupo elemento) {
        grupos.add(elemento);
    }

    public static void agregarMaestro(Maestro elemento) {
        profesores.add(elemento);
    }

    public static void agregarAlumnos(Alumno elemento) {
        estudiantes.add(elemento);
    }

    public static ArrayList<Grupo> getGrupos() {
        return grupos;
    }

    public static ArrayList<Alumno> getEstudiantes() {
        return estudiantes;
    }

    public static ArrayList<Maestro> getProfesores() {
        return profesores;
    }

    public static void testAlumnos() {
        Alumno nuevo = new Alumno("Pancho", 19, 1299131, "FCQI", 9.1f, "Ing. Software", null, 4);
        Alumno nuevo1 = new Alumno("Juan", 23, 1298001, "FCQI", 8.5f, "Ing. Software", null, 3);
        Alumno nuevo2 = new Alumno("María", 20, 1297123, "FCQI", 7.8f, "Ing. Software", null, 5);
        Alumno nuevo3 = new Alumno("Luisa", 22, 1296004, "FCQI", 8.9f, "Ing. Software", null, 2);
        Alumno nuevo4 = new Alumno("Carmelo", 18, 1295405, "FCQI", 8.2f, "Ing. Software", null, 4);
        Alumno nuevo5 = new Alumno("Ana", 20, 1294006, "FCQI", 7.5f, "Ing. Software", null, 6);

        estudiantes.add(nuevo);
        estudiantes.add(nuevo1);
        estudiantes.add(nuevo2);
        estudiantes.add(nuevo3);
        estudiantes.add(nuevo4);
        estudiantes.add(nuevo5);
    }

    public static void testMaestros() {
        Maestro maestro1 = new Maestro("Pedro", 35, 1234567, "FCQI", "Ing. Computacion");
        Maestro maestro2 = new Maestro("Matilda", 40, 1245678, "FCQI", "Ing. Computacion");
        Maestro maestro3 = new Maestro("Anastacia", 45, 1156789, "FCQI", "Ing. Computacion");
        Maestro maestro4 = new Maestro("Luis", 50, 1267890, "FCQI", "Ing. Computacion");
        Maestro maestro5 = new Maestro("Alejandro", 55, 1078901, "FCQI", "Ing. Computacion");
        Maestro maestro6 = new Maestro("Carlos", 60, 1189012, "FCQI", "Ing. Computacion");

        profesores.add(maestro1);
        profesores.add(maestro2);
        profesores.add(maestro3);
        profesores.add(maestro4);
        profesores.add(maestro5);
        profesores.add(maestro6);
    }

    public static List<Alumno> ordenarAlumnosPorNombre() {
        return estudiantes.stream()
                .sorted((a, b) -> a.getNombre().compareToIgnoreCase(b.getNombre()))
                .collect(Collectors.toList());
    }

    public static List<Maestro> ordenarMaestrosPorNombre() {
        return profesores.stream()
                .sorted((a, b) -> a.getNombre().compareToIgnoreCase(b.getNombre()))
                .collect(Collectors.toList());
    }

    public static List<Alumno> ordenarAlumnosPorEdad() {
        return estudiantes.stream()
                .sorted((a, b) -> Integer.compare(a.getEdad(), b.getEdad()))
                .collect(Collectors.toList());
    }

    public static List<Maestro> ordenarMaestrosPorEdad() {
        return profesores.stream()
                .sorted((a, b) -> Integer.compare(a.getEdad(), b.getEdad()))
                .collect(Collectors.toList());
    }

    public static boolean eliminarAlumnoPorNombre(String nombre) {
        return estudiantes.removeIf(alumno -> alumno.getNombre().equalsIgnoreCase(nombre));
    }

    public static boolean eliminarMaestroPorNombre(String nombre) {
        return profesores.removeIf(maestro -> maestro.getNombre().equalsIgnoreCase(nombre));
    }

    public static boolean eliminarGrupoPorNumero(int numero) {
        return grupos.removeIf(grupo -> grupo.getNumeroDeGrupo() == numero);
    }

    public static Alumno buscarAlumnoPorNombre(String nombre) {
        return estudiantes.stream()
                .filter(alumno -> alumno.getNombre().equalsIgnoreCase(nombre))
                .findFirst()
                .orElse(null);
    }

    public static Maestro buscarMaestroPorNombre(String nombre) {
        return profesores.stream()
                .filter(maestro -> maestro.getNombre().equalsIgnoreCase(nombre))
                .findFirst()
                .orElse(null);
    }
}
