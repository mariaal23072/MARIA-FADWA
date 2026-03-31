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
	
	// Para serve
	public static final String OPERATION_SERVE = "serve"; // valor que debe tomar el atributo 'operation' para hacer serve
	public static final String OPERATION_SERVE_OK = "serveOk";
	public static final String OPERATION_SERVE_MAL = "serveMal";
	
	// Para dirfile
	public static final String OPERATION_REQUEST_DIRFILE = "requestDirfiles"; // valor que debe tomar el atributo 'operation' para hacer dirfile
	public static final String OPERATION_DIRFILES = "dirfiles"; // valor que debe tomar el atributo 'operation' para enviar un mensaje dirfile con la lista de ficheros al cliente

	// Para peers
	public static final String OPERATION_REQUEST_PEERS = "requestPeers"; // valor que debe tomar el atributo 'operation' para hacer requestPeers
	public static final String OPERATION_PEERLIST = "peers"; // valor que debe tomar el atributo 'operation' para enviar un mensaje peers con la lista de peers al cliente

}
