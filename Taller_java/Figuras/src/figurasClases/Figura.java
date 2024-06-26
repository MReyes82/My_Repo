package figurasClases;

public class Figura 
{
	
	private String nombre;
	private int numeroLados;
	private String color;
	protected float area; // protected quiere decir que solo dentro de la herencia se puede acceder
	protected float perimetro;
	
	public Figura(int numeroLados, String color, String nombre) 
	{
		super();
		this.nombre = nombre;
		this.numeroLados = numeroLados;
		this.color = color;
	}

	public int getNumeroLados() 
	{
		return numeroLados;
	}
	
	public void setNumeroLados(int numeroLados) 
	{
		this.numeroLados = numeroLados;
	}
	
	public String getColor() 
	{
		return color;
	}
	
	public void setColor(String color) 
	{
		this.color = color;
	}
	
	public float getArea() 
	{
		return area;
	}
	
	public float getPrerimetro() 
	{
		return perimetro;
	}
	
	public String getNombre()
	{
		return nombre;
	}
	
	public String toString()
	{
		String cadena = "El area del" + " " + this.nombre + " " + "es: " + area + 
						" y su perimeteo es: " + perimetro;
		
		return cadena;
	}
	
	public void compArea() // definimos aqui los metodos
	{}					   // pero cada clase hija la implementara de forma diferente
	
	public void compPerimetro()
	{}
		
}
