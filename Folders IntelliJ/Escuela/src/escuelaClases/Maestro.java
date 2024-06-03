import javax.swing.JOptionPane;

public class Maestro extends Persona
{
    private String tituloAcademico;

    public Maestro(String nombre, int edad, int matricula,
                   String facultad, String titulo)
    {
        super(nombre, edad, matricula, facultad);
        tituloAcademico = titulo;
    }

    public String getTituloAcademico()
    {
        return tituloAcademico;
    }

    public void imprimirDatos()
    {
        JOptionPane.showMessageDialog(null, "Nombre: " + this.getNombre() + "\nEdad: " + this.getEdad() +
                "\nMatricula: " + this.getMatricula() + "\nFacultad: " + this.getFacultad() +
                "\nTitulo: " + this.getTituloAcademico());
    }

}
