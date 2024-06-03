package calculadora;

public class Inicio {

	public static void main(String[] args) {
		
		// creo objeto
		Procesador p = new Procesador();
		int r = p.suma(2, 3);
		
		System.out.println("Resultado " + r);
	}

}
