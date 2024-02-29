package escuelaClases;

import javax.swing.JOptionPane;

public class Grupo 
{
	private int numeroDeGrupo;
	private int cantidadAlumnos;
	private Maestro profesor;
	private String carrera;
	
	public Grupo(int numeroDeGrupo, int cantidadAlumnos, Maestro profesor, String carrera)
	{
		this.numeroDeGrupo = numeroDeGrupo;
		this.cantidadAlumnos = cantidadAlumnos;
		this.profesor = profesor;
		this.carrera = carrera;
	}
	
	public void setCarrera(String carrera)
	{
		this.carrera = carrera;
	}
	
	public String getCarrera()
	{
		return carrera;
	}
	
	public int getCantidadAlumnnos() 
	{
		return cantidadAlumnos;
	}
	
	public void setCantidadAlumnnos(int cantidadAlumnnos) 
	{
		this.cantidadAlumnos = cantidadAlumnnos;
	}
	
	public Maestro getProfesor() 
	{
		return profesor;
	}
	
	public void setProfesor(Maestro profesor) 
	{
		this.profesor = profesor;
	}
	
	public int getNumeroDeGrupo() 
	{
		return numeroDeGrupo;
	}
	
	public void mostrarDatos()
	{
		JOptionPane.showMessageDialog(null, "Numero del grupo: " + this.getNumeroDeGrupo() + 
		"\nCantidad de alumnos: " + this.getCantidadAlumnnos() + "\nProfesor: "
		 + this.getProfesor().getNombre() + "\nCarrera del grupo: " + this.getCarrera());
		
	}
	
}





