import javax.swing.JOptionPane;
public class Persona
{
    private String nombre;
    private int edad;
    private int matricula;
    private String facultad;

    public Persona(String nombre, int edad, int matricula, String facultad)
    {
        super();
        this.nombre = nombre;
        this.edad = edad;
        this.matricula = matricula;
        this.facultad = facultad;
    }

    public String getNombre()
    {
        return nombre;
    }

    public void setNombre(String nombre)
    {
        this.nombre = nombre;
    }

    public int getEdad() {
        return edad;
    }

    public void setEdad(int edad)
    {
        this.edad = edad;
    }

    public int getMatricula()
    {
        return matricula;
    }

    public void setMatricula(int matricula)
    {
        this.matricula = matricula;
    }

    public String getFacultad() {
        return facultad;
    }

    public void setFacultad(String facultad)
    {
        this.facultad = facultad;
    }

    public void imprimirDatos()
    {}

    public void imprimirMaterias()
    {}
}
