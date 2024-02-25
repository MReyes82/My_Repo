package figurasClases;

public class Cuadrado extends Figura
{
	private float lado;
	// metodo constructor

	public Cuadrado(float lado) // este constructor crea el objeto usando el parametro lado
	{
		super(4, "azul", "cuadrado");
		this.lado = lado;
	}
	
	// metodos gets y sets de atributos propios de la clase
	public float getLado() 
	{
		return lado;
	}

	public void setLado(float lado) 
	{
		this.lado = lado;
	}

	public void compArea()
	// ejemplo de clase entidad: representa algo de la figura 
	{
		area = lado * lado;
	}
	
	public void compPerimetro()	
	{
		perimetro = lado * 4;
	}
	
}
