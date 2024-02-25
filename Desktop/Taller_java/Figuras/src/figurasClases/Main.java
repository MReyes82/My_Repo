package figurasClases;

import javax.swing.JOptionPane;

public class Main 
{
	Figura misFiguras[] = new Figura[15];
	
	int contadorFiguras = 0;
	int i;
	//TODO: Hacer los trycatch de las opciones de modificar y crear figuras 
	
	public static void main(String[] args) 
	{
		Main p = new Main();
		p.inicio();
	}

	public void inicio()
	{
		Boolean correPrograma = true;
		String opcion;
		
		while (correPrograma)
		{
			try { // manejar expecion si el usuario elige la opcion cancelar
			opcion = (JOptionPane.showInputDialog(null, "Que deseas hacer?", "MENU DE FIGURAS", 
			JOptionPane.PLAIN_MESSAGE, null, new Object[] {"Seleccionar", "Crear circulo", "Crear rectangulo", "Crear cuadrado",
			"Mostrar figuras", "Modificar figuras", "Terminar programa"}, "Seleccionar")).toString();
				
			} catch (NullPointerException error){
				correPrograma = false;
				break;
			}
			
			
			switch(opcion)
			{
			case "Crear circulo":
				circuloMenu();
				break;
				
			case "Crear rectangulo":
				rectanguloMenu();
				break;
				
			case "Crear cuadrado":
				cuadradoMenu();
				break;
				
			case "Mostrar figuras":
				mostrarFiguras();
				break;
			
			case "Modificar figuras":
				modificarFiguras();
				break;
			
			case "Terminar programa":
				JOptionPane.showMessageDialog(null, "Hasta luego!");
				correPrograma = false;
				break;
				
			default:
				JOptionPane.showMessageDialog(null, "Opcion no valida, vuelve a elegir.");
				break;
			}
		}
		
	}
	
	public void circuloMenu()
	{
		float diametroInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa el diametro del circulo: "));
		Figura nuevoCirculo = new Circulo(diametroInput);
		nuevoCirculo.compArea();
		nuevoCirculo.compPerimetro();
		
		JOptionPane.showMessageDialog(null, nuevoCirculo.toString());
		
		misFiguras[contadorFiguras++] = nuevoCirculo;
		
	}
	
	public void rectanguloMenu()
	{
		float baseInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa la base del rectangulo: "));
		float alturaInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa la altura del rectangulo: "));
		Figura nuevoRectangulo = new Rectangulo(baseInput, alturaInput);
		nuevoRectangulo.compArea();
		nuevoRectangulo.compPerimetro();
		
		JOptionPane.showMessageDialog(null, nuevoRectangulo.toString());
		
		misFiguras[contadorFiguras++] = nuevoRectangulo;
		
	}
	
	public void cuadradoMenu()
	{
		float ladoInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa el lado del cuadrado: "));
		// utilizando el constructor con parametros
		Figura nuevoCuadrado = new Cuadrado(ladoInput);
		nuevoCuadrado.compArea();
		nuevoCuadrado.compPerimetro();
		
		JOptionPane.showMessageDialog(null, nuevoCuadrado.toString());
		
		misFiguras[contadorFiguras++] = nuevoCuadrado;
		
	}
	
	public void modificarCuadrado()
	{
		int indice = Integer.parseInt(JOptionPane.showInputDialog("Numero de cuadrado a modificar: "));
		indice--; // regularizamos el indice
		
		if (indice > contadorFiguras || indice < 0)
		{
			JOptionPane.showMessageDialog(null, "Indice no valido.");
			return;
		}
		
		Figura aux = misFiguras[indice];
		
		if (!(aux instanceof Cuadrado)) // si la figura NO es un cuadrado
		{
			JOptionPane.showMessageDialog(null, "La figura no es un cuadrado.");
			return;
		}
		
		float nuevoLado = Float.parseFloat(JOptionPane.showInputDialog("Ingrese el nuevo lado: "));
			
		Cuadrado mod = (Cuadrado) aux; // hacemos el cast para acceder a setLado
		mod.setLado(nuevoLado);
		mod.compArea();
		mod.compPerimetro();
	}
	
	public void modificarRectangulo()
	{
		int indice = Integer.parseInt(JOptionPane.showInputDialog("Numero de rectangulo a modificar: "));
		indice--; // regularizamos el indice
		
		if (indice > contadorFiguras || indice < 0)
		{
			JOptionPane.showMessageDialog(null, "Indice no valido.");
			return;
		}
		
		Figura aux = misFiguras[indice];
		
		if (!(aux instanceof Rectangulo))
		{
			JOptionPane.showMessageDialog(null, "La figura no es un rectangulo.");
			return;
		}
		
		float nuevaBase = Float.parseFloat(JOptionPane.showInputDialog("Ingrese el nuevo lado: "));
		float nuevaAltura = Float.parseFloat(JOptionPane.showInputDialog("Ingrese el nuevo lado: "));
	
		Rectangulo mod = (Rectangulo) aux;
		mod.setBase(nuevaBase);
		mod.setAltura(nuevaAltura);
		mod.compArea();
		mod.compPerimetro();
	}
	
	public void modificarCirculo()
	{
		int indice = Integer.parseInt(JOptionPane.showInputDialog("Numero de circulo a modificar: "));
		indice--;
		
		if (indice > contadorFiguras || indice < 0)
		{
			JOptionPane.showMessageDialog(null, "Indice no valido.");
			return;
		}
		
		Figura aux = misFiguras[indice];
		
		if (!(aux instanceof Circulo))
		{
			JOptionPane.showMessageDialog(null, "La figura no es un circulo.");
			return;
		}
		
		float nuevoRadio = Float.parseFloat(JOptionPane.showInputDialog("Ingrese el nuevo diametro"));
		
		Circulo mod = (Circulo) aux;
		mod.setRadio(nuevoRadio);
		mod.compArea();
		mod.compPerimetro();
	}
	
	public void modificarFiguras()
	{
		if (contadorFiguras == 0)
		{
			JOptionPane.showMessageDialog(null, "Arreglo vacio.");
			return;
		}
		
		String opcion;
		try 
		{
			opcion = (JOptionPane.showInputDialog(null, "Que figura desea modificar? ", "Menu de modificar figuras", 
			JOptionPane.PLAIN_MESSAGE, null, new Object[] {"Seleccionar", "Circulo", "Rectangulo", 
												"Cuadrado"}, "Seleccionar")).toString();
		} catch (NullPointerException error){
			return;
		}
		
		switch(opcion)
		{
		case "Cuadrado":
			modificarCuadrado();
			break;
		
		case "Rectangulo":
			modificarRectangulo();
			break;
		
		case "Circulo":
			modificarCirculo();
			break;
		
		default:
			JOptionPane.showMessageDialog(null, "Opcion no valida");
			break;
		}
	}
	
	public void mostrarFiguras()
	{
		if (contadorFiguras == 0)
		{
			JOptionPane.showMessageDialog(null, "Arreglo vacio.");
			return;
		}
		
		for (i = 0 ; i < contadorFiguras ; i++)
		{
			JOptionPane.showMessageDialog(null, "Figura" + (i+1) + "\n" + misFiguras[i].toString());
		}
		
	}
	 
}






