package firstProgram;
import javax.swing.JOptionPane;

public class Main 
{

	public static void main(String[] args) 
	{
		Main comienzo = new Main();
		comienzo.programaPrueba();
	}

	public void programaPrueba()
	{
		EjemploClase objeto1 = new EjemploClase(); 
		EjemploClase objeto2 = new EjemploClase();
		
		objeto1.setDatoEntero(10);
		objeto1.setDatoFlotante((float) 2.1);
		objeto1.setDatoCadena("Hola");
		objeto1.setDatoBool(true);
		objeto1.setDatoByte((byte) 12);
		
		objeto2.setDatoEntero(5);
		objeto2.setDatoFlotante((float) 0.25);
		objeto2.setDatoCadena("Adios");
		objeto2.setDatoBool(false);
		objeto2.setDatoByte((byte) 8);
		
		int condicion1 = objeto1.getDatoEntero();
		
		if (condicion1 == 10)
		{
			JOptionPane.showMessageDialog(null, "El dato es igual a 10");
		}
		
		else
		JOptionPane.showMessageDialog(null, "El dato NO es igual a 10");
		
		int i;
		for (i = 0; i < 3; i++)
		{
			JOptionPane.showMessageDialog(null, (i+1));
		}
		
	}
}
