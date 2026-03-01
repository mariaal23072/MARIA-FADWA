package es.um.redes.nanoFiles.udp.message;

public class DirMessageOps {

	/*
	 * TODO: (Boletín MensajesASCII) Añadir aquí todas las constantes que definen
	 * los diferentes tipos de mensajes del protocolo de comunicación con el
	 * directorio (valores posibles del campo "operation").
	 */ //HECHO
	public static final String OPERATION_INVALID = "invalid_operation";
	public static final String OPERATION_PING = "ping"; // valor que debe tomar el 
	// atributo 'operation' al crear el tipo de mensaje que debe ser enviado al
	// directorio al hacer ping
	public static final String OPERATION_PING_OK = "pingOk";
	public static final String OPERATION_PING_MAL = "pingMal";
	
	// TODO: definir las operaciones del protocolo de directorio
	
}
