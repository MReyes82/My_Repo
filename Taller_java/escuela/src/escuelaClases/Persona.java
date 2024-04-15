package escuelaClases;

import javax.swing.JOptionPane;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class Persona
{
    private String nombre;
    private int edad;
    private int matricula;
    private String facultad;

    private Map<String, ArrayList<String>> actividades;

    public Persona(String nombre, int edad, int matricula, String facultad)
    {
        super();
        this.nombre = nombre;
        this.edad = edad;
        this.matricula = matricula;
        this.facultad = facultad;

        actividades = new TreeMap<String, ArrayList<String>>();
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

    public void agregarActividad(String fecha, String actividad)
    {
        // si esta, lo agrega
        if (actividades.containsKey(fecha)) { actividades.get(fecha).add(actividad); }
        // si no esta, lo inserta
        else
        {
            ArrayList<String> act = new ArrayList<String>();
            act.add(actividad);
            actividades.put(fecha, act);
        }
    }

    public String muestraActividad()
    {
        String info = "";
        for (HashMap.Entry<String, ArrayList<String>> entrada : actividades.entrySet())
        {
            // entrada.getValue regresa el arraylist
            // cada actDia es un elemento del array de actividades
            for (String actDia : entrada.getValue())
            {
                info += actDia + "\n";
            }
        }

        return info;
    }
}