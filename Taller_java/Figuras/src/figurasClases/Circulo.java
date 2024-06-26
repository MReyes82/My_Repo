package figurasClases;

public class Circulo extends Figura
{
	private float radio, diametro;
	
	public Circulo(float diametroInput)
	{
		super(0, "rojo", "circulo"); // inicializa los atributos de la herencia (protected)
		this.diametro = diametroInput;
		radio = diametroInput / 2;
	}
	
	public float getRadio()
	{
		return radio;
	}
	
	public void setRadio(float radioInput)
	{
		this.radio = radioInput;
	}
	
	public float getDiametro()
	{
		return diametro;
	}
	
	public void setDiametro(float diametro)
	{
		this.diametro = diametro;
	}
	
	public float getArea()
	{
		return area;
	}
	
	public float getPerimetro()
	{
		return perimetro;
	}
	
	public void compArea() // en este caso, aunque este metodo se comparte en la herencia, la implementacion es 
							// diferente
	{
		area = (float) (Math.pow(radio, 2) * Math.PI);
	}
	
	public void compPerimetro()
	{
		perimetro = (float) (2 * Math.PI * radio);
	}
	
}
