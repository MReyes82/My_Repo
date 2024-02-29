package escuelaClases;

import javax.swing.JOptionPane;

public class Maestro extends Persona
{
	private String tituloAcademico;
	private String especializacion;
	
	public Maestro(String nombre, int edad, int matricula,
			String facultad, String titulo, String esp)
	{
		super(nombre, edad, matricula, facultad);
		tituloAcademico = titulo;
		especializacion = esp;
	}

	public String getTituloAcademico() {
		return tituloAcademico;
	}

	public String getEspecializacion() {
		return especializacion;
	}
	
	public void imprimirDatos() 
	{
		JOptionPane.showMessageDialog(null, "Nombre: " + this.getNombre() + "\nEdad: " + this.getEdad() +
				"\nMatricula: " + this.getMatricula() + "\nFacultad: " + this.getFacultad() + 
				"\nTitulo: " + this.getTituloAcademico() + "\nEspecializacion: " + this.getEspecializacion());
	}
	
}
