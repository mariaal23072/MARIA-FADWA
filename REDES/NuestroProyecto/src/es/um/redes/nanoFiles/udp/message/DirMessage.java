package es.um.redes.nanoFiles.udp.message;

import java.util.ArrayList;
import java.util.List;

import es.um.redes.nanoFiles.application.NanoFiles;
import es.um.redes.nanoFiles.util.FileInfo;

/**
 * Clase que modela los mensajes del protocolo de comunicación entre pares para
 * implementar el explorador de ficheros remoto (servidor de ficheros). Estos
 * mensajes son intercambiados entre las clases DirectoryServer y
 * DirectoryConnector, y se codifican como texto en formato "campo:valor".
 * 
 * @author rtitos
 *
 */
public class DirMessage {
	public static final int PACKET_MAX_SIZE = 65507; // 65535 - 8 (UDP header) - 20 (IP header)

	private static final char DELIMITER = ':'; // Define el delimitador
	private static final char END_LINE = '\n'; // Define el carácter de fin de línea

	/**
	 * Nombre del campo que define el tipo de mensaje (primera línea)
	 */
	private static final String FIELDNAME_OPERATION = "operation";
	/*
	 * TODO: (Boletín MensajesASCII) Definir de manera simbólica los nombres de
	 * todos los campos que pueden aparecer en los mensajes de este protocolo
	 * (formato campo:valor)
	 */ // HECHO
	private static final String FIELDNAME_PROTOCOL = "protocol";
	// Para el mensaje de serve, se envían el nickname y el puerto del peer
	private static final String FIELDNAME_NICKNAME = "nickname";
	private static final String FIELDNAME_PORT = "port";

	

	/**
	 * Tipo del mensaje, de entre los tipos definidos en PeerMessageOps.
	 */
	private String operation = DirMessageOps.OPERATION_INVALID; // indica que un mensaje está sin inicializar
	/**
	 * Identificador de protocolo usado, para comprobar compatibilidad del directorio.
	 */
	private String protocolId; // identificador de protocolo, para mensajes ping
	/*
	 * TODO: (Boletín MensajesASCII) Crear un atributo correspondiente a cada uno de
	 * los campos de los diferentes mensajes de este protocolo.
	 */
	
	// Para serve:

	private String nickname; // nickname del peer, para mensajes de serve
	private int port; // puerto del peer, para mensajes de serve
	
	// Getteres y setters
	public String getNickname() {
		return nickname;
	}

	public void setNickname(String nickname) {
		this.nickname = nickname;
	}

	public int getPort() {
		return port;
	}

	public void setPort(int port) {
		this.port = port;
	}
	
	// Para dirfile
	private List<FileInfo> fileList = new ArrayList<>(); // lista de ficheros del peer, para mensajes de dirfile

	public List<FileInfo> getFileList() {
		return fileList;
	}



	public DirMessage(String op) {
		operation = op;
	}

	/*
	 * TODO: (Boletín MensajesASCII) Crear diferentes constructores adecuados para
	 * construir mensajes de diferentes tipos con sus correspondientes argumentos
	 * (campos del mensaje)
	 */ // HECHO

	public DirMessage(String op, String protocolId) {
		operation = op;
		this.protocolId = protocolId;
	}


	public String getOperation() {
		return operation;
	}

	/*
	 * TODO: (Boletín MensajesASCII) Crear métodos getter y setter para obtener los
	 * valores de los atributos de un mensaje. Se aconseja incluir código que
	 * compruebe que no se modifica/obtiene el valor de un campo (atributo) que no
	 * esté definido para el tipo de mensaje dado por "operation".
	 */ // HECHO
	public void setProtocolID(String protocolIdent) {
		if (!operation.equals(DirMessageOps.OPERATION_PING)) {
			throw new RuntimeException(
					"DirMessage: setProtocolId called for message of unexpected type (" + operation + ")");
		}
		protocolId = protocolIdent;
	}

	public String getProtocolId() {
		if (!operation.equals(DirMessageOps.OPERATION_PING)) {
			throw new RuntimeException(
					"DirMessage: getProtocolId called for message of unexpected type (" + operation + ")");
		}
		return protocolId;
	}




	/**
	 * Método que convierte un mensaje codificado como una cadena de caracteres, a
	 * un objeto de la clase PeerMessage, en el cual los atributos correspondientes
	 * han sido establecidos con el valor de los campos del mensaje.
	 * 
	 * @param message El mensaje recibido por el socket, como cadena de caracteres
	 * @return Un objeto PeerMessage que modela el mensaje recibido (tipo, valores,
	 *         etc.)
	 */
	public static DirMessage fromString(String message) {
		/*
		 * TODO: (Boletín MensajesASCII) Usar un bucle para parsear el mensaje línea a
		 * línea, extrayendo para cada línea el nombre del campo y el valor, usando el
		 * delimitador DELIMITER, y guardarlo en variables locales.
		 */ // HECHO

		// System.out.println("DirMessage read from socket:");
		// System.out.println(message);
		String[] lines = message.split(END_LINE + "");
		// Local variables to save data during parsing
		DirMessage m = null;

		for (String line : lines) {
			int idx = line.indexOf(DELIMITER); // Posición del delimitador
			String fieldName = line.substring(0, idx).toLowerCase(); // minúsculas
			String value = line.substring(idx + 1).trim();

			switch (fieldName) {
			case FIELDNAME_OPERATION: {
				assert (m == null);
				m = new DirMessage(value);
				break;
			}

			case FIELDNAME_PROTOCOL: {
				m.setProtocolID(value);
				break;
			}
			
			// Para serve
			case FIELDNAME_NICKNAME: {
				m.setNickname(value);
				break;
			}
			
			case FIELDNAME_PORT: {
				m.setPort(Integer.parseInt(value)); // parseamos el puerto a entero
				break;
			}
			
			// Para dirfile
			case "file": {
				String[] partes = value.split("\\|"); // escapamos el delimitador "|" para separar los campos del fichero
				if (partes.length == 3) {
					String name = partes[0]; // nombre del fichero
					long size = Long.parseLong(partes[1]); // tamaño del fichero
					String hash = partes[2]; // hash del fichero
					// Añadir dichero a la lista
					m.getFileList().add(new FileInfo(hash, name, size, ""));
				}
				break;
			}
			
			default:
				System.err.println("PANIC: DirMessage.fromString - message with unknown field name " + fieldName);
				System.err.println("Message was:\n" + message);
				System.exit(-1);
			}
		}

		return m;
	}

	/**
	 * Método que devuelve una cadena de caracteres con la codificación del mensaje
	 * según el formato campo:valor, a partir del tipo y los valores almacenados en
	 * los atributos.
	 * 
	 * @return La cadena de caracteres con el mensaje a enviar por el socket.
	 */
	public String toString() {

		StringBuffer sb = new StringBuffer();
		sb.append(FIELDNAME_OPERATION + DELIMITER + operation + END_LINE); // Construimos el campo
		/*
		 * TODO: (Boletín MensajesASCII) En función de la operación del mensaje, crear
		 * una cadena la operación y concatenar el resto de campos necesarios usando los
		 * valores de los atributos del objeto.
		 */ // HECHO
		
		switch (operation) {
		case DirMessageOps.OPERATION_PING:
			sb.append(FIELDNAME_PROTOCOL + DELIMITER + NanoFiles.PROTOCOL_ID + END_LINE);
			break;
		
		// Para serve, se envían el nickname y el puerto del peer
		case DirMessageOps.OPERATION_SERVE:
			sb.append("nickname" + DELIMITER + nickname + END_LINE);
			sb.append("port" + DELIMITER + port + END_LINE);
			break;
		
		// Para dirfiles, se envía una línea por cada fichero, con el formato "file:nombre|tamaño|hash"
		case DirMessageOps.OPERATION_DIRFILES:
			if (fileList != null && !fileList.isEmpty()) {
			    for (FileInfo file : fileList) {
			        sb.append("file" + DELIMITER + file.fileName + "|" + file.fileSize + "|" + file.fileHash + END_LINE);
			    }
			}
            break;
			
			
			
		default:
			break;
		}
		
		sb.append(END_LINE); // Marcamos el final del mensaje
		return sb.toString();
	}

}
