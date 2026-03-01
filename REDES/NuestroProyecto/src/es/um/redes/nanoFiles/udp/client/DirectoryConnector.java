package es.um.redes.nanoFiles.udp.client;

import java.io.IOException;	
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketTimeoutException;
import java.util.Map;
import java.util.Arrays;
import java.util.LinkedHashMap;
import es.um.redes.nanoFiles.tcp.client.NFConnector;

import es.um.redes.nanoFiles.application.NanoFiles;
import es.um.redes.nanoFiles.udp.message.DirMessage;
import es.um.redes.nanoFiles.udp.message.DirMessageOps;
import es.um.redes.nanoFiles.util.FileInfo;

/**		
 * Cliente con métodos de consulta y actualización específicos del directorio
 */
public class DirectoryConnector {
	/**
	 * Puerto en el que atienden los servidores de directorio
	 */
	private static final int DIRECTORY_PORT = 6868;
	/**
	 * Tiempo máximo en milisegundos que se esperará a recibir una respuesta por el
	 * socket antes de que se deba lanzar una excepción SocketTimeoutException para
	 * recuperar el control
	 */
	private static final int TIMEOUT = 1000;
	/**
	 * Número de intentos máximos para obtener del directorio una respuesta a una
	 * solicitud enviada. Cada vez que expira el timeout sin recibir respuesta se️
	 * cuenta como un intento.
	 */
	private static final int MAX_NUMBER_OF_ATTEMPTS = 5;

	/**
	 * Socket UDP usado para la comunicación con el directorio
	 */
	private DatagramSocket socket;
	/**
	 * Dirección de socket del directorio (IP:puertoUDP)
	 */
	private InetSocketAddress directoryAddress;
	/**
	 * Nombre/IP del host donde se ejecuta el directorio
	 */
	private String directoryHostname;





	public static class DownloadedFile {
		public final String filename;
		public final long filesize;
		public final byte[] data;
		public final String filehash;

		public DownloadedFile(String filename, long fsize, byte[] data, String filehash) {
			this.filename = filename;
			this.filesize = fsize;
			this.data = data;
			this.filehash = filehash;
		}
	}

	public DirectoryConnector(String hostname) throws IOException {
		// Guardamos el string con el nombre/IP del host
		directoryHostname = hostname;
		/*
		 * TODO: (Boletín SocketsUDP) Convertir el string 'hostname' a InetAddress y
		 * guardar la dirección de socket (address:DIRECTORY_PORT) del directorio en el
		 * atributo directoryAddress, para poder enviar datagramas a dicho destino.
		 */ // HECHO
		
		InetAddress serverIP = InetAddress.getByName(directoryHostname);
		directoryAddress = new InetSocketAddress(serverIP, DIRECTORY_PORT);
		
		/*
		 * TODO: (Boletín SocketsUDP) Crea el socket UDP en cualquier puerto para enviar
		 * datagramas al directorio
		 */ // HECHO
		
		socket = new DatagramSocket();
	}

	/**
	 * Método para enviar y recibir datagramas al/del directorio
	 * 
	 * @param requestData los datos a enviar al directorio (mensaje de solicitud)
	 * @return los datos recibidos del directorio (mensaje de respuesta)
	 */
	private byte[] sendAndReceiveDatagrams(byte[] requestData) {
		byte responseData[] = new byte[DirMessage.PACKET_MAX_SIZE];
		byte response[] = null;
		if (directoryAddress == null) {
			System.err.println("DirectoryConnector.sendAndReceiveDatagrams: UDP server destination address is null!");
			System.err.println(
					"DirectoryConnector.sendAndReceiveDatagrams: make sure constructor initializes field \"directoryAddress\"");
			System.exit(-1);

		}
		if (socket == null) {
			System.err.println("DirectoryConnector.sendAndReceiveDatagrams: UDP socket is null!");
			System.err.println(
					"DirectoryConnector.sendAndReceiveDatagrams: make sure constructor initializes field \"socket\"");
			System.exit(-1);
		}
		/*
		 * TODO: (Boletín SocketsUDP) Enviar datos en un datagrama al directorio y
		 * recibir una respuesta. El array devuelto debe contener únicamente los datos
		 * recibidos, *NO* el búfer de recepción al completo.
		 */ // HECHO
		/*
		 * TODO: (Boletín SocketsUDP) Una vez el envío y recepción asumiendo un canal
		 * confiable (sin pérdidas) esté terminado y probado, debe implementarse un
		 * mecanismo de retransmisión usando temporizador, en caso de que no se reciba
		 * respuesta en el plazo de TIMEOUT. En caso de salte el timeout, se debe volver
		 * a enviar el datagrama y tratar de recibir respuestas, reintentando como
		 * máximo en MAX_NUMBER_OF_ATTEMPTS ocasiones.
		 */ // HECHO
		/*
		 * TODO: (Boletín SocketsUDP) Las excepciones que puedan lanzarse al
		 * leer/escribir en el socket deben ser capturadas y tratadas en este método. Si
		 * se produce una excepción de entrada/salida (error del que no es posible
		 * recuperarse), se debe informar y terminar el programa.
		 */ // HECHO
		/*
		 * NOTA: Las excepciones deben tratarse de la más concreta a la más genérica.
		 * SocketTimeoutException es más concreta que IOException.
		 */ // HECHO
		
		// Enviar datos en un datagrama al directorio
		DatagramPacket packetToServer = new DatagramPacket(requestData, requestData.length, directoryAddress);
		// Recibir una respuesta (llenando el array responseData con los datos recibidos)
		DatagramPacket packetFromServer = new DatagramPacket(responseData, responseData.length);

		int intentos = 0; // Número de intentos realizados
	    boolean received = false; // Si se ha recibido una respuesta
		
		// Las excepciones deben ser tratadas, de la más concreta a la más genérica
	    try {
	    	// Implementar mecanismo de retransmisión con temporizador
	    	socket.setSoTimeout(TIMEOUT);
	    	
	    	// Reintentando como máximo en MAX_NUMBER_OF_ATTEMPTS ocasiones
	    	// Mientras que no hayamos recibido respuesta y no hayamos superado el número máximo de intentos
	    	while (intentos < MAX_NUMBER_OF_ATTEMPTS && !received) {
        		try {
        			socket.send(packetToServer); // Enviar el datagrama al directorio
        			socket.receive(packetFromServer); // Intentar recibir la respuesta (si tarda más de TIMEOUT, se lanzará SocketTimeoutException)
        			received = true; // Si se recibe sin excepción, marcar como recibido
        		} catch (SocketTimeoutException e) {
        			// Mas concreta: SocketTimeoutException, el tiempo expiró sin recibir respuesta
        			intentos++; // Incrementar el número de intentos si se produce un timeout
        			System.out.println("TIMEOUT. (Intento " + intentos + "/" + MAX_NUMBER_OF_ATTEMPTS + ") : No se recibió respuesta, reintentando...");
        		}
        	}
	    } catch (IOException e) { // Más genérica: IOException, error de entrada/salida al enviar o recibir datagramas
	    	// Si se produce una excepción de entrada/salida, se debe informar y terminar el programa.
			System.err.println("IOException: Error al enviar o recibir datagramas");
			System.exit(-1);
		}
		
	    // Si después de todos los intentos seguimos sin respuesta, devolvemos null
	    if (!received) {
	        System.err.println("No se obtuvo respuesta del directorio tras " + MAX_NUMBER_OF_ATTEMPTS + " intentos.");
	        return null;
	    }
	    
		// Recortar array solo si se ha recibido algo (debe contener únicamente los datos recibidos, *NO* el búfer de recepción al completo)
		response = Arrays.copyOf(responseData, packetFromServer.getLength());

		return response;
	}

	/**
	 * Método para probar la comunicación con el directorio mediante el envío y
	 * recepción de mensajes sin formatear ("en crudo")
	 * 
	 * @return verdadero si se ha enviado un datagrama y recibido una respuesta
	 */
	public boolean testSendAndReceive() {
		/*
		 * TODO: (Boletín SocketsUDP) Probar el correcto funcionamiento de
		 * sendAndReceiveDatagrams. Se debe enviar un datagrama con la cadena "ping" y
		 * comprobar que la respuesta recibida empieza por "pingok". En tal caso,
		 * devuelve verdadero, falso si la respuesta no contiene los datos esperados.
		 */
		// HECHO
		boolean success = false;
		
		// Convertimos el mensaje a bytes para enviarlo al directorio
		String message = "ping";
		byte[] requestData = message.getBytes();
		
		// Enviamos y recibimos usando el método sendAndReceiveDatagrams
		byte[] responseData = sendAndReceiveDatagrams(requestData);
		
		// Convertimos la respuesta a string para procesarla
		if (responseData == null) {
			return false;
		}
		String responseMessage = new String(responseData);
		
		// Comprobamos si la respuesta recibida empieza por "pingok"
		if (responseMessage.startsWith("pingok")) {
			success = true;
		}

		return success;
	}

	public String getDirectoryHostname() {
		return directoryHostname;
	}

	/**
	 * Método para "hacer ping" al directorio, comprobar que está operativo y que
	 * usa un protocolo compatible. Este método no usa mensajes bien formados.
	 * 
	 * @return Verdadero si
	 */
	public boolean pingDirectoryRaw() {
		boolean success = false;
		/*
		 * TODO: (Boletín EstructuraNanoFiles) Basándose en el código de
		 * "testSendAndReceive", contactar con el directorio, enviándole nuestro
		 * PROTOCOL_ID (ver clase NanoFiles). Se deben usar mensajes "en crudo" (sin un
		 * formato bien definido) para la comunicación.
		 * 
		 * PASOS: 1.Crear el mensaje a enviar (String "ping&protocolId"). 2.Crear un
		 * datagrama con los bytes en que se codifica la cadena : 4.Enviar datagrama y
		 * recibir una respuesta (sendAndReceiveDatagrams). : 5. Comprobar si la cadena
		 * recibida en el datagrama de respuesta es "welcome", imprimir si éxito o
		 * fracaso. 6.Devolver éxito/fracaso de la operación.
		 */ // HECHO
				
		// 1 y 2.
		byte[] pingData = ("ping&" + NanoFiles.PROTOCOL_ID).getBytes();
		// 4. ( El método crea un datagrama con los bytes)
		byte[] response = sendAndReceiveDatagrams(pingData);
		if (response != null) {
			String receivedMessage = new String(response, 0, response.length);
			System.out.println("Receiving... " + receivedMessage);
			// 5.
			if (receivedMessage.equals("welcome")) {
				success = true;
			}
			else {
				System.err.println("Error: Se esperaba 'welcome', pero se recibió: " + receivedMessage);
				success = false;
			}
		}

		// 6.
		return success;
	}


	/**
	 * Método para "hacer ping" al directorio, comprobar que está operativo y que es
	 * compatible.
	 * 
	 * @return Verdadero si el directorio está operativo y es compatible
	 */
	public boolean pingDirectory() {
		boolean success = false;
		/*
		 * TODO: (Boletín MensajesASCII) Hacer ping al directorio 1.Crear el mensaje a
		 * enviar (objeto DirMessage) con atributos adecuados (operation, etc.) NOTA:
		 * Usar como operaciones las constantes definidas en la clase DirMessageOps :
		 * 2.Convertir el objeto DirMessage a enviar a un string (método toString)
		 * 3.Crear un datagrama con los bytes en que se codifica la cadena : 4.Enviar
		 * datagrama y recibir una respuesta (sendAndReceiveDatagrams). : 5.Convertir
		 * respuesta recibida en un objeto DirMessage (método DirMessage.fromString)
		 * 6.Extraer datos del objeto DirMessage y procesarlos 7.Devolver éxito/fracaso
		 * de la operación
		 */ //HECHO
		
		// 1.
		DirMessage pingMessage = new DirMessage(DirMessageOps.OPERATION_PING);
		pingMessage.setProtocolID(NanoFiles.PROTOCOL_ID);
		
		//2.
		String pingMessageString = pingMessage.toString();
		
		//3.
		byte[] pingData = pingMessageString.getBytes();
		
		//4. ( El método crea un datagrama con los bytes)
		byte[] response = sendAndReceiveDatagrams(pingData);
		
		if (response != null) {
			String responseString = new String(response, 0, response.length);
			System.out.println("Receiving... " + responseString);

			// 5.
			DirMessage responseMessage = DirMessage.fromString(responseString);

			// 6. Comprobar si la operación de la respuesta es OPERATION_PING_OK
			if (responseMessage.getOperation().equals(DirMessageOps.OPERATION_PING_OK)) {
				success = true;
			} else {
				System.err.println("Error: Ping Falló. Se esperaba la operación: " + DirMessageOps.OPERATION_PING_OK
						+ ". Pero se recibió: " + responseMessage.getOperation());
				success = false;
			}
		}
		
		// 7.
		return success;
	}

	/**
	 * Método para dar de alta como servidor de ficheros en el puerto indicado.
	 * 
	 * @param serverPort El puerto TCP en el que este peer sirve ficheros a otros
	 * @return Verdadero si el directorio tiene registrado a este peer como servidor
	 *         y acepta la lista de ficheros, falso en caso contrario.
	 */
	public boolean registerFileServer(int serverPort) {
		boolean success = false;

		// TODO: Ver TODOs en pingDirectory y seguir esquema similar



		return success;
	}

	/**
	 * Método para obtener la lista de ficheros alojados en el directorio. Para cada
	 * fichero se debe obtener un objeto FileInfo con nombre, tamaño y hash.
	 * 
	 * @return Los ficheros disponibles en el directorio, o null si el directorio no
	 *         pudo satisfacer nuestra solicitud
	 */
	public FileInfo[] getFileList() {
		FileInfo[] filelist = new FileInfo[0];
		// TODO: Ver TODOs en pingDirectory y seguir esquema similar



		return filelist;
	}

	public Map<String, InetSocketAddress> getPeerList() {
		Map<String, InetSocketAddress> peers = new LinkedHashMap<String, InetSocketAddress>();



		return peers;
	}

	public Map<String, InetSocketAddress[]> searchFilesByHash(String hashSubstring) {
		Map<String, InetSocketAddress[]> results = new LinkedHashMap<String, InetSocketAddress[]>();



		return results;
	}

	public DownloadedFile downloadFileFromDirectory(String hashSubstring) {
		byte[] fileData = null;
		String filename = null;
		long filesize = -1;
		String filehash = null;



		return new DownloadedFile(filename, filesize, fileData, filehash);
	}

	/**
	 * Método para darse de baja como servidor de ficheros.
	 * 
	 * @return Verdadero si el directorio tiene registrado a este peer como servidor
	 *         y ha dado de baja sus ficheros.
	 */
	public boolean unregisterFileServer() {
		boolean success = false;




		return success;
	}



}


