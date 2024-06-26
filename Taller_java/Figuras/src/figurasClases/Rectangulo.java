package figurasClases;

public class Rectangulo extends Figura
{						// rectangulo es clase hija de Figura
	private float base, altura;
	//float area, perimetro;
	
	public Rectangulo(float baseInput, float alturaInput)
	{
		super(4, "Naranja", "rectangulo");
		this.base = baseInput;
		this.altura = alturaInput;
	}
	
	public float getBase() 
	{
		return base;
	}
	
	public void setBase(float baseInput) 
	{
		this.base = baseInput;
	}
	
	public float getAltura() 
	{
		return altura;
	}
	
	public void setAltura(float alturaInput) 
	{
		this.altura = alturaInput;
	}
	public float getArea() 
	{
		return area;
	}
	public float getPerimetro() 
	{
		return perimetro;
	}
	
	public void compArea()
	{
		area = base * altura;
	}
	
	public void compPerimetro()
	{
		perimetro = (2 * base) + (2 *altura);
	}

}
