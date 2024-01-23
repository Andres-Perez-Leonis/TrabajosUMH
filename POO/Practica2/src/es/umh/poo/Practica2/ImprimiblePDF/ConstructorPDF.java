/**
 * 
 */
package es.umh.poo.Practica2.ImprimiblePDF;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;

import com.itextpdf.text.BaseColor;
import com.itextpdf.text.Chunk;
import com.itextpdf.text.Document;
import com.itextpdf.text.Element;
import com.itextpdf.text.Image;
import com.itextpdf.text.List;
import com.itextpdf.text.ListItem;
import com.itextpdf.text.Paragraph;
import com.itextpdf.text.pdf.PdfWriter;
import com.itextpdf.text.Font;
import com.itextpdf.text.Font.FontFamily;

import es.umh.poo.Practica2.Examenes.Examen;
import es.umh.poo.Practica2.Preguntas.Pregunta;
import es.umh.poo.Practica2.Preguntas.Relleno.PreguntaRellenar;
import es.umh.poo.Practica2.Preguntas.Teorico.PreguntaDesarrolloPractico;
import es.umh.poo.Practica2.Preguntas.Teorico.PreguntaTeorica;
import es.umh.poo.Practica2.Preguntas.Test.PreguntaOpciones;
import es.umh.poo.Practica2.Preguntas.Test.PreguntaVF;

/**
 * @author Andrés
 *
 */
public class ConstructorPDF {
	static final String cerrarPdf = "Si ha creado el pdf anteriormente y lo tiene abierto, porfavor cierrelo\n";
	
	/**
	 * El metodo "crearPDF" tiene la logica con la cual crear un pdf, y para añadir a este todo lo necesario
	 * para hacer el examen, pudiendo añadir las preguntas del examen con o sin respuestas
	 * @param examen
	 * @param respuestas
	 */
	public void CrearPDF(Examen examen, Boolean respuestas) {
		
		ArrayList<Pregunta> arrayPreguntas = examen.getArrayPreguntas();
		Pregunta pregunta;
		String frases[];
		String respuesta[];
		int porcentajes[];
		Boolean[] respeustasCorrectas;
		try {

			OutputStream file = new FileOutputStream(new File(".\\files\\PDF_Java4s.pdf"));
			Document document = new Document();
			PdfWriter.getInstance(document, file);

			// Inserting Image in PDF
			Image image = Image
					.getInstance("C:\\Users\\Andres\\Desktop\\Ig.Informatica\\POO\\Practica2\\files\\Umh.png");
			image.scaleAbsolute(120f, 120f);// image width,height

			// Now Insert Every Thing Into PDF Document
			document.open();// PDF document opened........

			document.add(image);

			document.add(Chunk.NEWLINE); // Something like in HTML :-)

			document.add(new Paragraph("Examen Creado Por: " + examen.getAutor()));
			document.add(new Paragraph("Examen Realizado: " + examen.getFechaRealizacion().toString()));
			document.add(new Paragraph("Curso -> " + examen.getCurso()));
			document.add(new Paragraph("Asignatura " + examen.getAsignatura().getTitulo() + "(" + examen.getAsignatura().getCodigoAsig() + ")"));

			for(int i = 0; i < arrayPreguntas.size(); i++) {
				pregunta = arrayPreguntas.get(i);
				if(pregunta.getTextoAclaratorio() != null) {
					document.add(new Paragraph("1. " + pregunta.getTextoPregunta() + " " 
							+ pregunta.getTextoAclaratorio() + " (Valor: " + pregunta.getValorPregunta() + ") "));
					if(pregunta instanceof PreguntaRellenar) {
						frases = ((PreguntaRellenar) pregunta).getFrase();
						respuesta = ((PreguntaRellenar) pregunta).getRespuesta();
						for(int j = 0; j < frases.length; j++) {
							document.add(new Paragraph("· " + frases[i]));
							if(respuestas) {
								document.add(new Paragraph("Respuesta -> " + respuesta[i], new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
							}
						}
					}else if(pregunta instanceof PreguntaTeorica) {
						if(respuestas) {
							document.add(new Paragraph("Respuesta -> " + ((PreguntaTeorica) pregunta).getRespuestaCorrecta(), new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
							
						}
					}else if(pregunta instanceof PreguntaDesarrolloPractico) {
						frases = ((PreguntaDesarrolloPractico) pregunta).getTexto();
						porcentajes = ((PreguntaDesarrolloPractico) pregunta).getPorcentaje();
						for(int j = 0; j < frases.length; j++) {
							document.add(new Paragraph("· " + frases[j] + " (" + String.valueOf(porcentajes[j]/100) + ")" , new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
								
						}
					}else if(pregunta instanceof PreguntaOpciones) {
						
						if(respuestas) {
							frases = ((PreguntaOpciones) pregunta).getRespuesta();
							respeustasCorrectas = ((PreguntaOpciones) pregunta).getRespuestaCorrecta();
							for(int j = 0; j < frases.length; j++) {
								document.add(new Paragraph("· " + frases[j] + " (" + imprimirRespuestaTest(respeustasCorrectas[j]) + ")" , new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
								
							}
						}
					}else if(pregunta instanceof PreguntaVF) {
						if(respuestas) {
							frases = ((PreguntaVF) pregunta).getPosiblesRespuestas();
							respeustasCorrectas = ((PreguntaVF) pregunta).getRespuestacorrecta();
							for(int j = 0; j < frases.length; j++) {
								document.add(new Paragraph("· " + frases[j] + " (" + imprimirRespuestaTest(respeustasCorrectas[j]) + ")" , new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
								
							}
						}
					}
				}else {
					document.add(new Paragraph("1. " + pregunta.getTextoPregunta() + " "
							+ " (Valor: " + pregunta.getValorPregunta() + ") "));
					if(pregunta instanceof PreguntaRellenar) {
						frases = ((PreguntaRellenar) pregunta).getFrase();
						respuesta = ((PreguntaRellenar) pregunta).getRespuesta();
						for(int j = 0; j < frases.length; j++) {
							document.add(new Paragraph("· " + frases[i]));
							if(respuestas) {
								document.add(new Paragraph("Respuesta -> " + respuesta[i], new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
							}
						}
					}else if(pregunta instanceof PreguntaTeorica) {
						if(respuestas) {
							document.add(new Paragraph("Respuesta -> " + ((PreguntaTeorica) pregunta).getRespuestaCorrecta(), new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
							
						}
					}else if(pregunta instanceof PreguntaDesarrolloPractico) {
						frases = ((PreguntaDesarrolloPractico) pregunta).getTexto();
						porcentajes = ((PreguntaDesarrolloPractico) pregunta).getPorcentaje();
						for(int j = 0; j < frases.length; j++) {
							document.add(new Paragraph("· " + frases[j] + " (" + String.valueOf(porcentajes[j]/100) + ")" , new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
								
						}
					}else if(pregunta instanceof PreguntaOpciones) {
						
						if(respuestas) {
							frases = ((PreguntaOpciones) pregunta).getRespuesta();
							respeustasCorrectas = ((PreguntaOpciones) pregunta).getRespuestaCorrecta();
							for(int j = 0; j < frases.length; j++) {
								document.add(new Paragraph("· " + frases[j] + " (" + imprimirRespuestaTest(respeustasCorrectas[j]) + ")" , new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
								
							}
						}
					}else if(pregunta instanceof PreguntaVF) {
						if(respuestas) {
							frases = ((PreguntaVF) pregunta).getPosiblesRespuestas();
							respeustasCorrectas = ((PreguntaVF) pregunta).getRespuestacorrecta();
							for(int j = 0; j < frases.length; j++) {
								document.add(new Paragraph("· " + frases[j] + " (" + imprimirRespuestaTest(respeustasCorrectas[j]) + ")" , new Font(FontFamily.HELVETICA, 11, Font.BOLDITALIC, new BaseColor(0, 0, 0))));
								
							}
						}
					}
				}
			}
			
			

			document.close();
			file.close();

			System.out.println("Pdf created successfully..");

		} catch (Exception e) {
			System.out.println(cerrarPdf);
		}
	}
	
	
	private String imprimirRespuestaTest(Boolean VF) {
		if (VF) {
			return "Correcta";
		}else {
			return "Incorrecta";
		}
	}
	
}
