package es.um.redes.nanoFiles.tcp.message;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import es.um.redes.nanoFiles.util.FileInfo;

public class PeerMessage {

	public static final byte HASH_LENGHT = 40;

	private byte opcode;

	/*
	 * TODO: (Boletín MensajesBinarios) Añadir atributos u otros constructores
	 * específicos para crear mensajes con otros campos, según sea necesario
	 * 
	 */
	private boolean last;
	private long fileSize;
	private String fileHash;
	private byte filenameLong;
	private String filenameVal;
	private byte fileData[];


	public PeerMessage() {
		opcode = PeerMessageOps.OPCODE_INVALID_CODE;
	}

	public PeerMessage(byte op) {
		opcode = op;
	}

	/*
	 * TODO: (Boletín MensajesBinarios) Crear métodos getter y setter para obtener
	 * los valores de los atributos de un mensaje. Se aconseja incluir código que
	 * compruebe que no se modifica/obtiene el valor de un campo (atributo) que no
	 * esté definido para el tipo de mensaje dado por "operation".
	 */
	public byte getOpcode() {
		return opcode;
	}
	
	public boolean getLast() {
		return last;
	}
	
	public void setLast(boolean newLast) {
		if (opcode != PeerMessageOps.OPCODE_PEER_FILE) {
			throw new RuntimeException(
					"PeerMessage: setLast called for message unexpected type (" +
					PeerMessageOps.opcodeToOperation(opcode) + ")");
		}
		last = newLast;
	}

	public long getFileSize() {
		return fileSize;
	}
	
	public void setFileSize(long newFileSize) {
	    if (opcode != PeerMessageOps.OPCODE_PEER_FILE && 
	        opcode != PeerMessageOps.OPCODE_DOWNLOAD_REP) {
	        throw new RuntimeException("PeerMessage: setFileSize called for unexpected message type");
	    }
	    fileSize = newFileSize;
	}
	
	public String getFileHash() {
		return fileHash;
	}
	
	public void setFileHash(String newFileHash) {
	    if (opcode != PeerMessageOps.OPCODE_PEER_FILE && opcode != PeerMessageOps.OPCODE_DOWNLOAD && 
	        opcode != PeerMessageOps.OPCODE_DOWNLOAD_REP) {
	        throw new RuntimeException("PeerMessage: setFileHash called for message unexpected type ("
	                + PeerMessageOps.opcodeToOperation(opcode) + ")");
	    }
	    fileHash = new String(newFileHash);
	}

	public byte getFilenameLong() {
		return filenameLong;
	}
	
	public void setFilenameLong(byte newFilenameLong) {
		if (opcode != PeerMessageOps.OPCODE_PEER_FILE) {
			throw new RuntimeException("PeerMessage: setFilenameLong called for message unexpected type ("
					+ PeerMessageOps.opcodeToOperation(opcode) + ")");
		}
		filenameLong = newFilenameLong;
	}
	
	public String getFilenameVal() {
		return filenameVal;
	}
	
	public void setFilenameVal(String newFilenameVal) {
		if (opcode != PeerMessageOps.OPCODE_PEER_FILE) {
			throw new RuntimeException("PeerMessage: setFilenameVal called for message unexpected type ("
					+ PeerMessageOps.opcodeToOperation(opcode) + ")");
		}
		filenameVal = new String(newFilenameVal);
	}
	
	public byte[] getFileData() {
		return fileData;
	}
	
	public void setFileData(byte[] newFileData) {
		if (opcode != PeerMessageOps.OPCODE_DOWNLOAD_REP) {
			throw new RuntimeException("PeerMessage: setFileData called for message unexpected type ("
					+ PeerMessageOps.opcodeToOperation(opcode) + ")");
		}
		fileData = newFileData;
	}

	// Constructor para inicializar todos los atrbutos
	public PeerMessage(byte op, boolean last, long fileSize, String fileHash, byte filenameLong, String filenameVal) {
	    this.opcode = op;
	    this.last = last;
	    this.fileSize = fileSize;
	    this.fileHash = fileHash;
	    this.filenameLong = filenameLong;
	    this.filenameVal = filenameVal;
	}
	
	public PeerMessage(byte op, String hash) {
	    this.opcode = op;
	    this.fileHash = hash;
	} 



	/**
	 * Método de clase para parsear los campos de un mensaje y construir el objeto
	 * DirMessage que contiene los datos del mensaje recibido
	 * 
	 * @param data El array de bytes recibido
	 * @return Un objeto de esta clase cuyos atributos contienen los datos del
	 *         mensaje recibido.
	 * @throws IOException
	 */
	public static PeerMessage readMessageFromInputStream(DataInputStream dis) throws IOException {
		/*
		 * TODO: (Boletín MensajesBinarios) En función del tipo de mensaje, leer del
		 * socket a través del "dis" el resto de campos para ir extrayendo con los
		 * valores y establecer los atributos del un objeto DirMessage que contendrá
		 * toda la información del mensaje, y que será devuelto como resultado. NOTA:
		 * Usar dis.readFully para leer un array de bytes, dis.readInt para leer un
		 * entero, etc.
		 */
		//PeerMessage message = new PeerMessage();
		byte opcode = dis.readByte();
		PeerMessage message = new PeerMessage(opcode);
		switch (opcode) {
		case PeerMessageOps.OPCODE_REQUEST_PEER_FILES:
		case PeerMessageOps.OPCODE_PEER_FILES_ERROR: {
			break;
		}
		case PeerMessageOps.OPCODE_PEER_FILE: {
			boolean last = false;
			byte valOfLast = dis.readByte();
			if (valOfLast == 1) {
				last = true;
			}
			long fileSize = dis.readLong();
			byte[] fileHash = new byte[HASH_LENGHT];
			dis.readFully(fileHash);
			byte filenameLong = dis.readByte();
			byte[] filenameVal = new byte[filenameLong];
			dis.readFully(filenameVal);
			message.setLast(last);
			message.setFileSize(fileSize);
			message.setFileHash(new String(fileHash));
			message.setFilenameLong(filenameLong);
			message.setFilenameVal(new String(filenameVal));
			
			break;
		}
		
		case PeerMessageOps.OPCODE_DOWNLOAD: {
			int length = dis.readInt();
			byte[] hashBytes = new byte[length];
			dis.readFully(hashBytes);
			message.setFileHash(new String(hashBytes));
			break;
		}
		case PeerMessageOps.OPCODE_DOWNLOAD_REP: {
			byte[] hashBytes = new byte[HASH_LENGHT];
			dis.readFully(hashBytes);
			message.setFileHash(new String(hashBytes));
			
			long fileSize = dis.readLong();
			message.setFileSize(fileSize);
			
			byte[] data = new byte[(int) fileSize];
			dis.readFully(data);
			message.setFileData(data);
			break;
		}
		case PeerMessageOps.OPCODE_FILE_NOT_FOUND: {
			break;
		}

		default:
			System.err.println("PeerMessage.readMessageFromInputStream doesn't know how to parse this message opcode: "
					+ PeerMessageOps.opcodeToOperation(opcode));
			System.exit(-1);
		}
		return message;
	}

	public void writeMessageToOutputStream(DataOutputStream dos) throws IOException {
		/*
		 * TODO (Boletín MensajesBinarios): Escribir los bytes en los que se codifica el
		 * mensaje en el socket a través del "dos", teniendo en cuenta opcode del
		 * mensaje del que se trata y los campos relevantes en cada caso. NOTA: Usar
		 * dos.write para leer un array de bytes, dos.writeInt para escribir un entero,
		 * etc.
		 */

		dos.writeByte(opcode);
		switch (opcode) {
		case PeerMessageOps.OPCODE_REQUEST_PEER_FILES:
		case PeerMessageOps.OPCODE_PEER_FILES_ERROR: {
			break;
		}
		case PeerMessageOps.OPCODE_PEER_FILE: {
			byte valOfLast = 0;
			if (last) {
				valOfLast = 1;
			}
			dos.writeByte(valOfLast);
			dos.writeLong(fileSize);
			dos.write(fileHash.getBytes());
			dos.writeByte(filenameLong);
			dos.write(filenameVal.getBytes());
			break;
		}
		case PeerMessageOps.OPCODE_DOWNLOAD: {
		    dos.writeInt(fileHash.length()); // longitud de la subcadena
		    dos.write(fileHash.getBytes()); // caracteres de la subcadena
		    break;
		}
		
		case PeerMessageOps.OPCODE_DOWNLOAD_REP: {
		    // hash original
		    dos.write(fileHash.getBytes());
		    // tamaño del fichero
		    dos.writeLong(fileSize);
		    // datos del fichero
		    dos.write(fileData); 
		    break;
		}
		case PeerMessageOps.OPCODE_FILE_NOT_FOUND: {
		    // enviamos el opcode, y ya se hace al principio
		    break;
		}

		default:
			System.err.println("PeerMessage.writeMessageToOutputStream found unexpected message opcode " + opcode + "("
					+ PeerMessageOps.opcodeToOperation(opcode) + ")");
		}
	}




}
