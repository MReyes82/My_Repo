package firstProgram;

import javax.swing.JOptionPane;

public class EjemploClase 
{
	private int datoEntero;
	private String datoCadena;
	private Boolean datoBool;
	private float datoFlotante;
	private byte datoByte;
	
	public int getDatoEntero() {
		return datoEntero;
	}

	public void setDatoEntero(int datoEntero) {
		this.datoEntero = datoEntero;
	}

	public String getDatoCadena() {
		return datoCadena;
	}

	public void setDatoCadena(String string) {
		this.datoCadena = string;
	}

	public Boolean getDatoBool() {
		return datoBool;
	}

	public void setDatoBool(Boolean datoBool) {
		this.datoBool = datoBool;
	}

	public float getDatoFlotante() {
		return datoFlotante;
	}

	public void setDatoFlotante(float datoFlotante) {
		this.datoFlotante = datoFlotante;
	}

	public byte getDatoByte() {
		return datoByte;
	}

	public void setDatoByte(byte datoByte) {
		this.datoByte = datoByte;
	}
	
	public void desplegarAtributos()
	{
		JOptionPane.showMessageDialog(null, "Entero: " + this.datoEntero);
		JOptionPane.showMessageDialog(null, "Flotante: " + this.datoFlotante);
		JOptionPane.showMessageDialog(null, "Cadena: " + this.datoCadena);
		JOptionPane.showMessageDialog(null, "Booleano: " + this.datoBool);
		JOptionPane.showMessageDialog(null, "Byte: " + this.datoByte);
	}
	
}
