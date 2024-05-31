package interfaces;

import  escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class MostrarAlumnos extends JFrame 
{
    public MostrarAlumnos() {
        setTitle("Mostrar Alumnos");
        setSize(600, 400);
        setLocationRelativeTo(null);

        String[] columnNames = {"Nombre", "Edad", "Matricula", "Facultad", "Carrera", "Promedio", "Semestre"};
        List<Alumno> alumnos = Control.getEstudiantes();
        String[][] data = new String[alumnos.size()][7];
        for (int i = 0; i < alumnos.size(); i++) {
            Alumno alumno = alumnos.get(i);
            data[i][0] = alumno.getNombre();
            data[i][1] = String.valueOf(alumno.getEdad());
            data[i][2] = String.valueOf(alumno.getMatricula());
            data[i][3] = alumno.getFacultad();
            data[i][4] = alumno.getCarrera();
            data[i][5] = String.valueOf(alumno.getPromedio());
            data[i][6] = String.valueOf(alumno.getSemestre());
        }

        JTable table = new JTable(data, columnNames);
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);

        setVisible(true);
    }
}

