package figurasClases;

import javax.swing.JOptionPane;

public class Main 
{
	Figura misFiguras[] = new Figura[15];
	
	int contadorFiguras = 0;
	int i;
	
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
				
			//default:
				//JOptionPane.showMessageDialog(null, "Opcion no valida, vuelve a elegir.");
				//break;
			}
		}
		
	}
	
	public void circuloMenu()
	{
		float diametroInput = 0;
		
		do {
		
			try
			{
				diametroInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa el diametro del circulo: "));
				if (diametroInput <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
			
			}catch(NumberFormatException e){
		
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			}catch(NullPointerException e){
				return;
			}
		
		} while(diametroInput <= 0);
		
		
		
		Figura nuevoCirculo = new Circulo(diametroInput);
		nuevoCirculo.compArea();
		nuevoCirculo.compPerimetro();
		
		JOptionPane.showMessageDialog(null, nuevoCirculo.toString());
		
		misFiguras[contadorFiguras++] = nuevoCirculo;
		
	}
	
	public void rectanguloMenu()
	{
		float baseInput = 0;
		float alturaInput = 0;
		
		do {
			try {
				baseInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa la base del rectangulo: "));
				if (baseInput <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
				
			}catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			}catch(NullPointerException e){ // si pulsa a cancelar
				return;
			}
			
		} while(baseInput <= 0);
		
		do {
			try {
				alturaInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa la altura del rectangulo: "));
				if (alturaInput <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
				
			}catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			}catch(NullPointerException e){
				return;
			}
			
		} while(alturaInput <= 0);
		
		 
		Figura nuevoRectangulo = new Rectangulo(baseInput, alturaInput);
		nuevoRectangulo.compArea();
		nuevoRectangulo.compPerimetro();
		
		JOptionPane.showMessageDialog(null, nuevoRectangulo.toString());
		
		misFiguras[contadorFiguras++] = nuevoRectangulo;
		
	}
	
	public void cuadradoMenu()
	{
		float ladoInput = 0;
		
		do {
			try {
				ladoInput = Float.parseFloat(JOptionPane.showInputDialog("Ingresa el lado del cuadrado: "));
				
				if (ladoInput <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
				
			} catch(NumberFormatException e) {
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			} catch(NullPointerException e) {
				return;
			}
			
		} while(ladoInput <= 0);
		
		// utilizando el constructor con parametros
		Figura nuevoCuadrado = new Cuadrado(ladoInput);
		nuevoCuadrado.compArea();
		nuevoCuadrado.compPerimetro();
		
		JOptionPane.showMessageDialog(null, nuevoCuadrado.toString());
		
		misFiguras[contadorFiguras++] = nuevoCuadrado;
		
	}
	
	public void modificarCuadrado()
	{
		int indice = 0;
		
		do {
			try {
				indice = Integer.parseInt(JOptionPane.showInputDialog("Numero de cuadrado a modificar: "));
				
				if (indice > contadorFiguras || indice < 0)
				{
					JOptionPane.showMessageDialog(null, "Indice no valido.");
				}
				
			}catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			}catch(NullPointerException e){ // si selecciona cancelar
				return;
			}
			
		} while(indice > contadorFiguras || indice < 0);
		
		indice--; // regularizamos el indice
		
		Figura aux = misFiguras[indice];
		
		if (!(aux instanceof Cuadrado)) // si la figura NO es un cuadrado
		{
			JOptionPane.showMessageDialog(null, "La figura no es un cuadrado.");
			return;
		}
		
		float nuevoLado = 0;
		
		do {
			try {
				nuevoLado = Float.parseFloat(JOptionPane.showInputDialog("Ingrese el nuevo lado: "));
				
				if (nuevoLado <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
			} catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			} catch(NullPointerException e){
				
				return;
			}
			
		} while (nuevoLado <= 0);
			
		// variable auxiliar para modificar los atributos
		Cuadrado mod = (Cuadrado) aux; // hacemos el cast para acceder a setLado
		mod.setLado(nuevoLado);
		mod.compArea();
		mod.compPerimetro();
	}
	
	public void modificarRectangulo()
	{
		int indice = 0;
		
		do {
			try {
				indice = Integer.parseInt(JOptionPane.showInputDialog("Numero de rectangulo a modificar: "));
				
				if (indice > contadorFiguras || indice < 0)
				{
					JOptionPane.showMessageDialog(null, "Indice no valido.");
				}
				
			}catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			}catch(NullPointerException e){ // si selecciona cancelar
				return;
			}
			
		} while(indice > contadorFiguras || indice < 0);
		
		indice--; // regularizamos el indice
		
		Figura aux = misFiguras[indice];
		
		if (!(aux instanceof Rectangulo))
		{
			JOptionPane.showMessageDialog(null, "La figura no es un rectangulo.");
			return;
		}
		
		float nuevaBase = 0;
		
		do {
			try {
				nuevaBase = Float.parseFloat(JOptionPane.showInputDialog("Ingrese la nueva base: "));
				
				if (nuevaBase <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
			} catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			} catch(NullPointerException e){
				
				return;
			}
			
		} while (nuevaBase <= 0);
		
		float nuevaAltura = 0;
		
		do {
			try {
				nuevaAltura = Float.parseFloat(JOptionPane.showInputDialog("Ingrese la nueva altura: "));
				
				if (nuevaAltura <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
			} catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			} catch(NullPointerException e){
				
				return;
			}
			
		} while (nuevaAltura <= 0);
		
		Rectangulo mod = (Rectangulo) aux; 
		mod.setBase(nuevaBase);
		mod.setAltura(nuevaAltura);
		mod.compArea();
		mod.compPerimetro();
	}
	
	public void modificarCirculo()
	{
		int indice = 0;
		
		do {
			try {
				indice = Integer.parseInt(JOptionPane.showInputDialog("Numero de circulo a modificar: "));
				
				if (indice > contadorFiguras || indice < 0)
				{
					JOptionPane.showMessageDialog(null, "Indice no valido.");
				}
				
			}catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			}catch(NullPointerException e){ // si selecciona cancelar
				return;
			}
			
		} while(indice > contadorFiguras || indice < 0);
		
		indice--;
		
		Figura aux = misFiguras[indice];
		
		if (!(aux instanceof Circulo))
		{
			JOptionPane.showMessageDialog(null, "La figura no es un circulo.");
			return;
		}
		
		float nuevoDiametro = 0;
		
		do {
			try {
				nuevoDiametro = Float.parseFloat(JOptionPane.showInputDialog("Ingrese el nuevo diametro"));
				
				if (nuevoDiametro <= 0)
				{
					JOptionPane.showMessageDialog(null, "Ingrese un valor mayor a cero.");
				}
			} catch(NumberFormatException e){
				
				JOptionPane.showMessageDialog(null, "Ingrese un valor numerico correcto.");
				
			} catch(NullPointerException e){
				
				return;
			}
			
		} while (nuevoDiametro <= 0);
		
		Circulo mod = (Circulo) aux; 
		mod.setDiametro(nuevoDiametro);
		mod.setRadio((nuevoDiametro / 2));
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
		
		String opcion;
		try 
		{
			opcion = (JOptionPane.showInputDialog(null, "Que figuras desea mostrar? ", "Menu de mostrar figuras", 
			JOptionPane.PLAIN_MESSAGE, null, new Object[] {"Seleccionar", "Circulos", "Rectangulos", 
												"Cuadrados"}, "Seleccionar")).toString();
		} catch (NullPointerException error){
			return;
		}
		
		switch(opcion)
		{
		case "Circulos":
		mostrarCirculos();
		break;
		
		case "Rectangulos":
		mostrarRectangulos();
		break;
		
		case "Cuadrados":
		mostrarCuadrados();
		break;
		
		default:
		break;
		}
			
	}
	
	public void mostrarCirculos()
	{
		Boolean seMostro = false;
		for (int i = 0 ; i < contadorFiguras ; i++)
		{
			if (misFiguras[i] instanceof Circulo)
			{
				JOptionPane.showMessageDialog(null, "Figura" + (i+1) + "\n" + misFiguras[i].toString());
				seMostro = true;
			}
		}
		
		if (!(seMostro))
		{
			JOptionPane.showMessageDialog(null, "No hay circulos para mostrar.");
		}
	}
	
	public void mostrarCuadrados()
	{
		Boolean seMostro = false;
		for (int i = 0 ; i < contadorFiguras ; i++)
		{
			if (misFiguras[i] instanceof Cuadrado)
			{
				JOptionPane.showMessageDialog(null, "Figura" + (i+1) + "\n" + misFiguras[i].toString());
				seMostro = true;
			}
		}
		
		if (!(seMostro))
		{
			JOptionPane.showMessageDialog(null, "No hay circulos para mostrar.");
		}
	}
	
	public void mostrarRectangulos()
	{
		Boolean seMostro = false;
		for (int i = 0 ; i < contadorFiguras ; i++)
		{
			if (misFiguras[i] instanceof Rectangulo)
			{
				JOptionPane.showMessageDialog(null, "Figura" + (i+1) + "\n" + misFiguras[i].toString());
				seMostro = true;
			}
		}
		
		if (!(seMostro))
		{
			JOptionPane.showMessageDialog(null, "No hay circulos para mostrar.");
		}
	}
	
	
}






