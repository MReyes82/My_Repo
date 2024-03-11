/*
clase control, para gestionar los arreglos de instancias; alumnos, profesores y grupos, con sus respectivos metodos
*/
package escuelaClases;

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
}
