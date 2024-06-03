//package escuelaClases;
import java.util.ArrayList;

public class Control
{
    public static ArrayList<Grupo> grupos;
    public static ArrayList<Alumno> estudiantes;
    public static ArrayList<Maestro> profesores;

    public static void inicializarArreglos()
    {
        grupos = new ArrayList<Grupo>();
        estudiantes = new ArrayList<Alumno>();
        profesores = new ArrayList<Maestro>();
    }

    public static void agregarGrupo(Grupo elemento)
    {
        grupos.add(elemento);
    }

    public static void agregarMaestro(Maestro elemento)
    {
        profesores.add(elemento);
    }

    public static void agregarAlumnos(Alumno elemento)
    {
        estudiantes.add(elemento);
    }

    public static ArrayList<Grupo> getGrupos()
    {
        return grupos;
    }

    public static ArrayList<Alumno> getEstudiantes()
    {
        return estudiantes;
    }

    public static ArrayList<Maestro> getProfesores()
    {
        return profesores;
    }

    // metodos para añadir instancias predefinidas y no tener que escribir tanto
    public static void testAlumnos()
    {
        Alumno nuevo = new Alumno("Pancho", 19, 1299131, "FCQI", (float)9.1, "Ing. Software", null, 4);
        Alumno nuevo1 = new Alumno("Juan", 23, 1298001, "FCQI", (float)8.5, "Ing. Software", null, 3);
        Alumno nuevo2 = new Alumno("María", 20, 1297123, "FCQI", (float)7.8, "Ing. Software", null, 5);
        Alumno nuevo3 = new Alumno("Luisa", 22, 1296004, "FCQI", (float)8.9, "Ing. Software", null, 2);
        Alumno nuevo4 = new Alumno("Carmelo", 18, 1295405, "FCQI", (float)8.2, "Ing. Software", null, 4);
        Alumno nuevo5 = new Alumno("Ana", 20, 1294006, "FCQI", (float)7.5, "Ing. Software", null, 6);

        estudiantes.add(nuevo);
        estudiantes.add(nuevo1);
        estudiantes.add(nuevo2);
        estudiantes.add(nuevo3);
        estudiantes.add(nuevo4);
        estudiantes.add(nuevo5);
    }

    public static void testMaestros()
    {
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
}
