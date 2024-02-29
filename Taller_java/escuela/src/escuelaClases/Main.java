package escuelaClases;

import javax.swing.JOptionPane;

public class Main 
{
	// arreglos para las instancias, con un maximo de 15 elementos cada uno
	Alumno estudiantes[] = new Alumno[15]; 
	Maestro profesores[] = new Maestro[15];
	Grupo grupos[] = new Grupo[15];
	int contadorEstudiantes = 0, contadorProfesores = 0, contadorGrupos = 0, edadBuffer = 0, matriculaBuffer = 0;
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
	
	public void menu() // TODO: agregar una expresion LAMBDA y ciclo for mejorado
	{
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
				mostrarInstancias(profesores);
				//mostrarMaestros();
				break;
				
			case "Mostrar datos de alumnos":
				mostrarInstancias(estudiantes);
				//mostrarAlumnos();
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
		String esp;
		// pedimos los datos
		nombreBuffer = scanString("Nombre: ");
		edadBuffer = scanUnsignedInteger("Edad: ");
		matriculaBuffer = scanUnsignedInteger("Matricula: ");
		facultadBuffer = scanString("Facultad: ");
		titulo = scanString("Titulo: ");
		esp = scanString("Especialidad: ");
		
		// verificacion en caso de que algun valor no sea valido
		if (nombreBuffer == null || edadBuffer < 0 || 
			matriculaBuffer < 0 || facultadBuffer == null 
			|| titulo == null || esp == null) {
			JOptionPane.showMessageDialog(null, "ERROR: valor invalido ingresado.");
			return;
		}
		
		Persona nuevoProf = new Maestro(nombreBuffer, edadBuffer, matriculaBuffer, facultadBuffer, 
										titulo, esp);
		
		profesores[contadorProfesores++] = (Maestro) nuevoProf;
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
			materias[i] = scanString("Materia" + (i+1) + ": ");
		}
		
		Persona nuevoAlu = new Alumno(nombreBuffer, edadBuffer, matriculaBuffer, facultadBuffer,
										promedio, carrera, materias, semestre);
		estudiantes[contadorEstudiantes++] = (Alumno) nuevoAlu;
		JOptionPane.showMessageDialog(null, "Alumno agreado exitosamente.");
	}
	
	public void altaGrupo() 
	{
		int cant = contadorEstudiantes;	
		int num = scanUnsignedInteger("Ingrese el numero del grupo: ");
		Boolean seEncontro = false;
		String profesor = scanString("Ingrese el nombre del profesor para el grupo: ");
		Maestro profesorDelGrupo = null; 
		String carreraDelGrupo = scanString("Ingrese la carrera del grupo: ");
		
		for (int i = 0 ; i < contadorProfesores ; i++)
		{
			if (profesores[i].getNombre().equals(profesor)) // si el nombre de la iteracion 'i' del arreglo profesores
			{												// es igual al nombre pedido previamente
				profesorDelGrupo = new Maestro(profesores[i].getNombre(),
									profesores[i].getEdad(), profesores[i].getMatricula(),
									profesores[i].getFacultad(), profesores[i].getTituloAcademico(),
									profesores[i].getEspecializacion()) ;
				seEncontro = true;
				break; 
			}
		}
		
		if (!seEncontro || profesorDelGrupo == null)
		{
			JOptionPane.showMessageDialog(null, "No se encontro el profesor.");
			return;
		}
		
		Grupo nuevoGrupo = new Grupo(num, cant, profesorDelGrupo, carreraDelGrupo);
		grupos[contadorGrupos++] = nuevoGrupo;
	}
	/*
	public void mostrarAlumnos()
	{	// si no hay alumnos pero si hay grupos
		if (contadorEstudiantes == 0 && contadorGrupos > 0)
		{
			JOptionPane.showMessageDialog(null, "No hay alumnos para mostrar en el arreglo,"
					                      + ", seleccione la opcion 'mostrar datos de grupos'");
			return;
		}
		// si no hay alumnos pero tampoco grupos
		else if (contadorEstudiantes == 0 && contadorGrupos == 0)
		{
			JOptionPane.showMessageDialog(null, "No hay alumnos para mostrar");
			return;
		}
		
		JOptionPane.showMessageDialog(null, "Mostrando alumnos.");
		
		for (int i = 0 ; i < contadorEstudiantes ; i++)
		{
			JOptionPane.showMessageDialog(null, "Alumno " + (i+1) + "\n");
			estudiantes[i].imprimirDatos();
		}
		
	}
	
	public void mostrarMaestros()
	{
		if (contadorProfesores == 0)
		{
			JOptionPane.showMessageDialog(null, "No hay profesores para mostrar");
			return;
		}
		
		JOptionPane.showMessageDialog(null, "Mostrando profesores.");
		
		for (int i = 0 ; i < contadorProfesores ; i++)
		{
			JOptionPane.showMessageDialog(null, "Profesor " + (i+1) + "\n");
			profesores[i].imprimirDatos();
		}	
		
	}
	 */
	public void mostrarGrupos()
	{
		if (contadorGrupos == 0)
		{
			JOptionPane.showMessageDialog(null, "No hay grupos para mostrar");
			return;
		}
		
		JOptionPane.showMessageDialog(null, "Mostrando grupos.");
		
		for (int i = 0 ; i < contadorGrupos ; i++)
		{
			grupos[i].mostrarDatos();
		}
		
	}
	
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
		/*
		 	mientras que el elemento actual no sea nulo, para evitar obtener
			un NullPointerException, ya que antes tenia un ciclo For que llegaba hazta "personas.length",
			pero como length es un numero fijo, podia iterar sobre elementos nulos.
		 */
		while (personas[i] != NULL) // --> ^^^^^
		{
			JOptionPane.showMessageDialog(null, personas[i].getClass().getSimpleName() + " " + (i + 1) + "\n");
			personas[i].imprimirDatos();
			
			if (personas[i] instanceof Alumno) // si el elemento actual es una instancia de alumno,
			{								   // llama al metodo para imprimir las materias del alumno
				personas[i].imprimirMaterias();
			}

			i++;
		}
		/* el metodo getClass retorna un objeto que en este caso representaria la clase que queremos acceder
		   despues, el metodo getSimpleName retornaria el nombre de la clase a la que queremos acceder
		   hice esto ya que en mi metodo de mostrarAlumno o mostrarMaestro incluyo un mensaje que 
		  menciona el nombre del objeto y el numero de iteracion, ejemplo: "alumno" + (i+1) */
		
	}
}















