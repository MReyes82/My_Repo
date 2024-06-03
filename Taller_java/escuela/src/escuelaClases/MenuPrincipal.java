package escuelaClases;

import interfaces.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JOptionPane.*;

public class MenuPrincipal extends JFrame {

    public MenuPrincipal() {
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 1024, 768);
        setTitle("MENU DE ESCUELA");
        getContentPane().setLayout(null);

        // Configuración del estilo de los módulos del menú

        JLabel labelRegistroDeElementos = new JLabel("Registro de elementos");
        labelRegistroDeElementos.setBounds(51, 85, 258, 31);
        labelRegistroDeElementos.setFont(new Font("Tahoma", Font.PLAIN, 25));
        getContentPane().add(labelRegistroDeElementos);

        JButton botonAltaMaestro = new JButton("Dar de alta maestro");
        botonAltaMaestro.setBounds(51, 158, 258, 41);
        botonAltaMaestro.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonAltaMaestro.addActionListener(e -> new AltaMaestro().setVisible(true));
        getContentPane().add(botonAltaMaestro);

        JButton botonAltaAlumno = new JButton("Dar de alta alumno");
        botonAltaAlumno.setBounds(348, 158, 300, 41);
        botonAltaAlumno.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonAltaAlumno.addActionListener(e -> new AltaAlumno().setVisible(true));
        getContentPane().add(botonAltaAlumno);

        JButton botonAltaGrupo = new JButton("Dar de alta grupo");
        botonAltaGrupo.setBounds(691, 158, 258, 41);
        botonAltaGrupo.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonAltaGrupo.addActionListener(e -> new AltaGrupo().setVisible(true));
        getContentPane().add(botonAltaGrupo);

        JLabel labelMostrarDatos = new JLabel("Mostrar datos registrados");
        labelMostrarDatos.setBounds(51, 260, 300, 31);
        labelMostrarDatos.setFont(new Font("Tahoma", Font.PLAIN, 25));
        getContentPane().add(labelMostrarDatos);

        JButton botonMostrarMaestros = new JButton("Mostrar datos de maestros");
        botonMostrarMaestros.setBounds(51, 342, 258, 41);
        botonMostrarMaestros.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonMostrarMaestros.addActionListener(e -> new MostrarMaestros().setVisible(true));
        getContentPane().add(botonMostrarMaestros);

        JButton botonMostrarAlumnos = new JButton("Mostrar datos de alumnos");
        botonMostrarAlumnos.setBounds(383, 342, 241, 41);
        botonMostrarAlumnos.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonMostrarAlumnos.addActionListener(e -> new MostrarAlumnos().setVisible(true));
        getContentPane().add(botonMostrarAlumnos);

        JButton botonMostrarGrupos = new JButton("Mostrar datos de grupos");
        botonMostrarGrupos.setBounds(691, 342, 258, 41);
        botonMostrarGrupos.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonMostrarGrupos.addActionListener(e -> new MostrarGrupos().setVisible(true));
        getContentPane().add(botonMostrarGrupos);

        JLabel labelBusquedaElementos = new JLabel("Busqueda de elementos");
        labelBusquedaElementos.setBounds(52, 467, 279, 31);
        labelBusquedaElementos.setFont(new Font("Tahoma", Font.PLAIN, 25));
        getContentPane().add(labelBusquedaElementos);

        JButton botonBuscarMaestro = new JButton("Buscar un maestro");
        botonBuscarMaestro.setBounds(51, 544, 258, 41);
        botonBuscarMaestro.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonBuscarMaestro.addActionListener(e -> new BuscarPersona().setVisible(true));
        getContentPane().add(botonBuscarMaestro);

        JButton botonBuscarAlumno = new JButton("Buscar un alumno");
        botonBuscarAlumno.setBounds(348, 544, 300, 41);
        botonBuscarAlumno.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonBuscarAlumno.addActionListener(e -> new BuscarPersona().setVisible(true));
        getContentPane().add(botonBuscarAlumno);

        JButton botonBuscarGrupo = new JButton("Buscar un grupo");
        botonBuscarGrupo.setBounds(691, 544, 258, 41);
        botonBuscarGrupo.setFont(new Font("Tahoma", Font.PLAIN, 18));
        botonBuscarGrupo.addActionListener(e -> new BuscarGrupo().setVisible(true));
        getContentPane().add(botonBuscarGrupo);

        JButton botonCerrar = new JButton("Cerrar");
        botonCerrar.setBounds(452, 676, 104, 31);
        botonCerrar.setFont(new Font("Tahoma", Font.BOLD, 15));
        botonCerrar.addActionListener(new ActionListener() 
        {
            public void actionPerformed(ActionEvent e) 
            {
                JOptionPane.showMessageDialog(null, "¡Hasta luego!");
                System.exit(0);
            }

        });
        getContentPane().add(botonCerrar);
        
        JLabel lblNewLabel = new JLabel("MENU DE ESCUELA");
        lblNewLabel.setFont(new Font("Tahoma", Font.BOLD, 25));
        lblNewLabel.setBounds(383, 27, 241, 48);
        getContentPane().add(lblNewLabel);
    }
}
