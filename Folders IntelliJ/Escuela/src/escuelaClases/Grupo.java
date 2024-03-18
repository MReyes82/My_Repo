import javax.swing.JOptionPane;

public class Grupo
{
    private int numeroDeGrupo; // clave
    private int cantidadAlumnos;
    private int cantidadMaxAlumnos;

    private Maestro profesor;
    private Alumno alumnos[];

    public Grupo(int numeroDeGrupo, int cantidadMaxAlumnos, Maestro profesor)
    {
        this.numeroDeGrupo = numeroDeGrupo;
        this.cantidadMaxAlumnos = cantidadMaxAlumnos;
        this.profesor = profesor;

        cantidadAlumnos = 0;
        alumnos = new Alumno[cantidadMaxAlumnos];
    }

    public int getCantidadAlumnnos()
    {
        return cantidadAlumnos;
    }

    public void setCantidadAlumnnos(int cantidadAlumnnos)
    {
        this.cantidadAlumnos = cantidadAlumnnos;
    }

    public Maestro getProfesor()
    {
        return profesor;
    }

    public void setProfesor(Maestro profesor)
    {
        this.profesor = profesor;
    }

    public int getNumeroDeGrupo()
    {
        return numeroDeGrupo;
    }

    public void mostrarDatos()
    {
        JOptionPane.showMessageDialog(null, "Numero del grupo: " + this.getNumeroDeGrupo() +
                "\nCantidad de alumnos: " + this.getCantidadAlumnnos() + "\nProfesor: "
                + this.getProfesor().getNombre());

    }

    public void mostrarListaAlumnos()
    {
        for (int i = 0 ; i < cantidadAlumnos ; i++)
        {
            JOptionPane.showMessageDialog(null, "Alumno " + (i+1) + ":");
            alumnos[i].imprimirDatos();
        }
    }

    public int getCantidadMaxAlumnos()
    {
        return cantidadMaxAlumnos;
    }

    public void agregarAlumno(Alumno nuevo)
    {
        alumnos[cantidadAlumnos++] = nuevo;
    }

}
