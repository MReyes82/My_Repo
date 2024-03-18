import javax.swing.JOptionPane;

public class Alumno extends Persona
{
    private String carrera;
    private String[] materias;
    private float promedio;
    private int semestre;

    public Alumno(String nombre, int edad, int matricula,
                  String facultad, float promedio,
                  String carrera, String[] materias, int semestre)
    {
        super(nombre, edad, matricula, facultad);
        this.carrera = carrera;
        this.materias = materias;
        this.promedio = promedio;
        this.semestre = semestre;
    }

    public String getCarrera()
    {
        return carrera;
    }

    public void setCarrera(String carrera)
    {
        this.carrera = carrera;
    }

    public String[] getMaterias()
    {
        return materias;
    }

    public void setMaterias(String[] materias)
    {
        this.materias = materias;
    }

    public float getPromedio()
    {
        return promedio;
    }

    public void setPromedio(float promedio)
    {
        this.promedio = promedio;
    }

    public int getSemestre()
    {
        return semestre;
    }

    public void setSemestre(int semestre)
    {
        this.semestre = semestre;
    }

    public void imprimirDatos()
    {
        JOptionPane.showMessageDialog(null, "Nombre: " + this.getNombre() + "\nEdad: " + this.getEdad() +
                "\nMatricula: " + this.getMatricula() + "\nFacultad: " + this.getFacultad() +
                "\nCarrera: " + this.getCarrera() + "\nPromedio: " + this.getPromedio() + "\nSemestre: " + this.getSemestre());
    }

    public void imprimirMaterias()
    {
        JOptionPane.showMessageDialog(null, "Materias que lleva el alumno:\n");
        String[] materias = this.getMaterias();

        for (String materia : materias)
        {
            JOptionPane.showMessageDialog(null, materia + "\n");
        }
    }
}

