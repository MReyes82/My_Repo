package escuelaClases;

import javax.swing.JOptionPane;
import java.util.ArrayList;

public class Main 
{
	int edadBuffer = 0, matriculaBuffer = 0;
	String facultadBuffer = null, nombreBuffer = null;
	
	public static void main(String[] args) 
	{
		Main program = new Main();
		program.start();
	}
	
	public void start()
	{
		menu();
	}
	
	public void menu() // TODO: agregar una expresion LAMBDA
	{
		Control.inicializarArreglos();
		Boolean correPrograma = true;
		String opcion;
		
		while(correPrograma)
		{
			try {
				opcion = (JOptionPane.showInputDialog(null, "Que deseas hacer?", "MENU DE ESCUELA",
				JOptionPane.PLAIN_MESSAGE, null, new Object[] {"Seleccionar", "Dar de alta maestro", "Dar de alta alumno", 
				"Dar de alta grupo", "Mostrar datos de maestros", "Mostrar datos de alumnos", "Mostrar datos de grupos"
				,"Terminar programa"}, "Seleccionar")).toString();
				
			} catch(NullPointerException e){
				correPrograma = false;
				return;
			}
			
			switch(opcion)
			{
			case "Dar de alta maestro":
				altaMaestro();
				break;
			
			case "Dar de alta alumno":
				altaAlumno();
				break;
			
			case "Dar de alta grupo":
				altaGrupo();
				break;
				
			case "Mostrar datos de maestros":
				//mostrarInstancias(Control.getProfesores());
				mostrarMaestros();
				break;
				
			case "Mostrar datos de alumnos":
				//mostrarInstancias(Control.getEstudiantes());
				mostrarAlumnos();
				break;
			
			case "Mostrar datos de grupos":
				mostrarGrupos();
				break;
				
			case "Terminar programa":
				JOptionPane.showMessageDialog(null, "Hasta luego!");
				correPrograma = false;
				break;
			}
			
		}
	}
					// recibe como parametro el texto que vera el usuario 
	public String scanString(String textoInput) // este metodo implementa validacion de datos
	{
		String input = null;
		
		try {
			
			input = JOptionPane.showInputDialog(textoInput);
				
		} catch(NullPointerException e) {
			return null; // regresamos null en caso de que pulse cancelar
		}
			
		return input; //regresa el string que scanea del usuario
	}
	// este metodo scanea un valor entero, implementando validacion de datos
	public int scanUnsignedInteger(String textoInput)
	{
		int input = 0;
		do {
			try {
				input = Integer.parseInt(JOptionPane.showInputDialog(textoInput));
				
				if (input < 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor no negativo.");
				}
				
			} catch (NullPointerException e){
			
				return -1; // regresamos -1 en caso de que pulse cancelar
				
			} catch (NumberFormatException e) {
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico.");
			}
			
		} while(input < 0);
		
		return input;
	}
	
	public float scanUnsignedFloat(String textoInput)
	{
		float input = 0;
		
		do {
			try {
				input = Float.parseFloat(JOptionPane.showInputDialog(textoInput));
				
				if (input < 0.0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor no negativo.");
				}
				
			} catch(NullPointerException e) {
				
				return (float) -1;
				
			} catch (NumberFormatException e) {
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico.");
			}
			
		} while(input < 0);
		
		return input;
	}
	
	public void altaMaestro()
	{
		String titulo;
		// pedimos los datos
		nombreBuffer = scanString("Nombre: ");
		edadBuffer = scanUnsignedInteger("Edad: ");
		matriculaBuffer = scanUnsignedInteger("Matricula: ");
		facultadBuffer = scanString("Facultad: ");
		titulo = scanString("Titulo: ");
		//esp = scanString("Especialidad: ");
		
		// verificacion en caso de que algun valor no sea valido
		if (nombreBuffer == null || edadBuffer < 0 || 
			matriculaBuffer < 0 || facultadBuffer == null 
			|| titulo == null) {
			JOptionPane.showMessageDialog(null, "ERROR: valor invalido ingresado.");
			return;
		}
		
		Maestro nuevoProf = new Maestro(nombreBuffer, edadBuffer, matriculaBuffer, facultadBuffer, titulo);
		
		Control.agregarMaestro(nuevoProf);
		JOptionPane.showMessageDialog(null, "Docente agreado exitosamente.");
	}

	public void altaAlumno()
	{
		nombreBuffer = scanString("Nombre: ");
		edadBuffer = scanUnsignedInteger("Edad: ");
		matriculaBuffer = scanUnsignedInteger("Matricula: ");
		facultadBuffer = scanString("Facultad: ");
		String carrera = scanString("Carrera: ");
		float promedio = scanUnsignedFloat("Promedio: ");
		int semestre = scanUnsignedInteger("Semestre: ");
		int cantidadMaterias = scanUnsignedInteger("Cuantas materias llevara el estudiante? ");
		
		if (nombreBuffer == null || edadBuffer < 0 || 
			matriculaBuffer < 0 || facultadBuffer == null || promedio < 0
			|| carrera == null || cantidadMaterias < 0 || semestre < 0) {
			
			JOptionPane.showMessageDialog(null, "ERROR: valor invalido ingresado.");
			return;
		}
		
		String materias[] = new String[cantidadMaterias];
		
		for (int i = 0 ; i < cantidadMaterias ; i++)
		{
			materias[i] = scanString("Materia " + (i+1) + ": ");
		}
		
		Alumno nuevoAlu = new Alumno(nombreBuffer, edadBuffer, matriculaBuffer, facultadBuffer,
										promedio, carrera, materias, semestre);
		
		Control.agregarAlumnos(nuevoAlu);
		JOptionPane.showMessageDialog(null, "Alumno agreado exitosamente.");
	}
	
	public void altaGrupo() 
	{
		//hacemos las copias de los arraylist	
		ArrayList<Maestro> profesores = Control.getProfesores();
		ArrayList<Alumno> alumnos = Control.getEstudiantes();
		String listaMaestros = generarListaMaestros(profesores);
		String listaAlumnos = generarListaAlumnos(alumnos);
		
		int num = scanUnsignedInteger("Ingrese el numero del grupo: ");
		int cantidad = scanUnsignedInteger("Ingrese la cantidad maxima de alumnos del grupo: ");
		
		Maestro profesorDelGrupo = seleccionarMaestro(profesores, listaMaestros); 
			
		if (profesorDelGrupo == null)
		{
			JOptionPane.showMessageDialog(null, "Indice no valido.");
			return;
		}
		
		Grupo nuevoGrupo = new Grupo(num, cantidad, profesorDelGrupo);
		
		for (int i = 0 ; i < cantidad ; i++)
		{
			Alumno nuevo = seleccionarAlumno(alumnos, listaAlumnos);
			
			if (nuevo == null)
			{
				JOptionPane.showMessageDialog(null, "Indice no valido.");
				break;
			}
			nuevoGrupo.agregarAlumno(nuevo);
		}
		
		Control.agregarGrupo(nuevoGrupo);
	}
	
	public void mostrarAlumnos()
	{
		// hacemos una copia del arraylist original 
		ArrayList<Alumno> alumnosAux = Control.getEstudiantes();
		
		// si no hay elementos en el arreglo
		if (alumnosAux.isEmpty())
		{
			JOptionPane.showMessageDialog(null, "No hay alumnos para mostrar");
			return;
		}
		
		JOptionPane.showMessageDialog(null, "Mostrando alumnos.");
		
		for (Alumno estudiante : alumnosAux)
		{
			estudiante.imprimirDatos();
		}
	}
	
	public void mostrarMaestros()
	{
		// hacemos una copia del arraylist original
		ArrayList<Maestro> maestrosAux = Control.getProfesores();
		
		// si no hay elementos en el arreglo
		if (maestrosAux.isEmpty())
		{
			JOptionPane.showMessageDialog(null, "No hay profesores para mostrar");
			return;
		}
		
		JOptionPane.showMessageDialog(null, "Mostrando profesores.");
		
		for (Maestro profesor : maestrosAux)
		{
			profesor.imprimirDatos();
		}
		
	}
	 
	public void mostrarGrupos()
	{
		// hacemos una copia del arraylist original
		ArrayList<Grupo> gruposAux = Control.getGrupos();
		// si no hay elementos en el arreglo
		if (gruposAux.isEmpty())
		{
			JOptionPane.showMessageDialog(null, "No hay grupos para mostrar");
			return;
		}
		
		JOptionPane.showMessageDialog(null, "Mostrando grupos.");
		
		int i = 1;
		for (Grupo grupo: gruposAux)
		{
			JOptionPane.showMessageDialog(null, "Grupo " + i + ":");
			grupo.mostrarDatos();
			grupo.mostrarListaAlumnos();
		}
		
	}
	
	public Maestro seleccionarMaestro(ArrayList<Maestro> maestros, String listado)
	{
		int indice = scanUnsignedInteger("Maestros\n" + listado + "\nSeleccione un maestro para el grupo: ");	
		Maestro output = null;
		
		try
		{
			 output = maestros.get(indice);
			
		} catch(IndexOutOfBoundsException e){
			return null;
		}
		
		return output;
	}
	
	public Alumno seleccionarAlumno(ArrayList<Alumno> estudiantes, String listado)
	{
		int indice = scanUnsignedInteger("Alumnos\n" + listado + "\nSeleccione un alumno para añadr a el grupo: ");
		
		Alumno output = null;
		try 
		{
			output = estudiantes.get(indice);
			
		} catch(IndexOutOfBoundsException e) {
			
			return null;
		}
		
		return output;
	}
	
	// hice esta funcion para facilitar la generacion del listado que se mostrara al seleccionar un maestro o alumno
	public String generarListaMaestros(ArrayList<Maestro> maestros)
	{
		String lista = "";
		int i = 0;
		for (Maestro profesor: maestros)
		{
			lista += " " + i + ") " + profesor.getNombre() + "";
			i++;
		}
		
		return lista;
	}
	
	public String generarListaAlumnos(ArrayList<Alumno> estudiantes)
	{
		String lista = "";
		int i = 0;
		for (Alumno alumno : estudiantes)
		{
			lista += " " + i + ") " + alumno.getNombre() + "";
			i++;
		}
		
		return lista;
	}
	
	/*
	public static <T extends Persona> void mostrarInstancias(T[] personas)
	{
		// pregunta si la primera posicion del arreglo es nulo, lo que significaria que no hay elementos para mostrar
		// si no los hay, avisa al usuario y sale del motodo.
		if (personas[0] == null)
		{
			JOptionPane.showMessageDialog(null, "No hay personas para mostrar.");
			return;
		}
		
		int i = 0;
		
		 	//mientras que el elemento actual no sea nulo, para evitar obtener
			//un NullPointerException, ya que antes tenia un ciclo For que llegaba hasta "personas.length",
			//pero como length es un numero fijo, podia iterar sobre elementos nulos.
		 
		while (personas[i] != null) // --> ^^^^^
		{
			JOptionPane.showMessageDialog(null, personas[i].getClass().getSimpleName() + " " + (i + 1) + "\n");
			personas[i].imprimirDatos();
			
			if (personas[i] instanceof Alumno) // si el elemento actual es una instancia de alumno,
			{								   // llama al metodo para imprimir las materias del alumno
				personas[i].imprimirMaterias();
			}

			i++;
		}
		// el metodo getClass retorna un objeto que en este caso representaria la clase que queremos acceder
		//   despues, el metodo getSimpleName retornaria el nombre de la clase a la que queremos acceder
		//   hice esto ya que en mi metodo de mostrarAlumno o mostrarMaestro incluyo un mensaje que 
		//  menciona el nombre del objeto y el numero de iteracion, ejemplo: "alumno" + (i+1)
		
	} 
	*/
}


