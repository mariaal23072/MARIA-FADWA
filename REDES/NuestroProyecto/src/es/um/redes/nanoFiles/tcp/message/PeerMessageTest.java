package es.um.redes.nanoFiles.tcp.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class PeerMessageTest {

	public static void main(String[] args) throws IOException {
		String nombreArchivo = "peermsg.bin";
		
		// 1. Creamos datos de prueba para el fichero
		byte[] datosPrueba = "Hola, esto es el contenido del fichero".getBytes();
		
		// 2. Creamos el mensaje de envío de fichero
		PeerMessage msgOut = new PeerMessage(PeerMessageOps.OPCODE_DOWNLOAD_REP);
		msgOut.setFileHash("1234567890123456789012345678901234567890"); // 40 caracteres.setFileHash("a3f");
		msgOut.setFileSize(datosPrueba.length);
		msgOut.setFileData(datosPrueba);
		
		// Lo escribimos
		DataOutputStream fos = new DataOutputStream(new FileOutputStream(nombreArchivo));
		msgOut.writeMessageToOutputStream(fos);
		fos.close(); 

		// 3. Lo leemos
		DataInputStream fis = new DataInputStream(new FileInputStream(nombreArchivo));
		PeerMessage msgIn = PeerMessage.readMessageFromInputStream(fis);
		fis.close();

		// 4. Comprobamos los datos recibidos
		System.out.println("Opcode correcto: " + msgIn.getOpcode());
		System.out.println("Hash correcto: " + msgIn.getFileHash());
		System.out.println("Tamaño correcto: " + msgIn.getFileSize());
		System.out.println("Datos del fichero recibidos: " + new String(msgIn.getFileData()));
	}

}

