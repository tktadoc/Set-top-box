//
// Client Java pour communiquer avec le Serveur C++ 
// eric lecolinet - telecom paristech - 2015
//
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.UIManager;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;

import java.io.*;
import java.net.*;

public class Client extends JFrame
{
  // les bouttons dérivant de AbstractAction pour pouvoir les ajouter à la fois dans le menu déroulant et la barre d'outil
  private ButtonSearchG searchGroupe_ = new ButtonSearchG("searchCrew");
	private ButtonSearchM searchMedia_ = new ButtonSearchM("searchMultimedia");
	private ButtonExist exist_ = new ButtonExist("exist");
  private ButtonPlay play_ = new ButtonPlay("play");

  // les éléments de la zone principale
	private JButton searchGroupe = new JButton("search Crew");
	private JButton searchMedia = new JButton("search Multimedia");
	private JButton exist = new JButton("exist");
  private JButton play = new JButton("play");
	private static JTextArea ZoneText = new JTextArea("",10,20);
  private static final long serialVersionUID = 1L;

  //
  static final String DEFAULT_HOST = "localhost";
  static final int DEFAULT_PORT = 3331;
  private Socket sock;
  private BufferedReader input;
  private BufferedWriter output;

  // geteur pouuuuuur manipuler la zone de text
  public static JTextArea getZoneText(){return ZoneText;}

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  ///
  /// Lit une requete depuis le Terminal, envoie cette requete au serveur,
  /// recupere sa reponse et l'affiche sur le Terminal.
  /// Noter que le programme bloque si le serveur ne repond pas.
  /// le Exception c'est poooooooour gérer l'exception sue le look'n feel Nimbus
  ///
  public static void main(String argv[]) throws Exception {

    // création d'un look'n feel pour avoir un certain deeesigne de la fenêtre
		UIManager.setLookAndFeel(new NimbusLookAndFeel());
		
    

    String host = DEFAULT_HOST;
    int port = DEFAULT_PORT;
    if (argv.length >=1) host = argv[0];
    if (argv.length >=2) port = Integer.parseInt(argv[1]);
    
    Client client = null;
    
    try {
      client = new Client(host, port);
    }
    catch (Exception e) {
      System.err.println("Client: Couldn't connect to "+host+":"+port);
      System.exit(1);
    }
    
    System.out.println("Client connected to "+host+":"+port);

    
  //pour rendre l'interface visible 
   client.setVisible(true); 
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ///
  /// Initialise la connexion.
  /// Renvoie une exception en cas d'erreur.
  ///
  public Client(String host, int port) throws UnknownHostException, IOException {
        super("set-top box");

    //l'interface graphique
    
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);// ceci va nous permettre de faire une confirmation avant de fermer la fenêtre
		setSize(700,500);

		// gérer les évenements en utilisant les classes imbriquées anonymes
		searchGroupe.addActionListener(new ActionListener() {
			
			public void actionPerformed(ActionEvent event){
				
        //pour obtenir le contenu de la zone de text c'est-à-dire le JTextArea
        String text = getZoneText().getText();

        //Divise le texte en lignes en utilisant le caractère de saut de ligne
        String[]lines = text.split("\\n");

       //pour lire dans la zone de text
       BufferedReader cin = new BufferedReader(new StringReader(text));
    
    
      if(lines.length>0){
        try {
        if(cin.readLine()!=null){
        String request = "searchGroupe "+lines[lines.length-1];
        String response = send(request);

        //affichage de la réponse dddans     la zone dde text
        getZoneText().append("\n Response: " + response);
        }
      }
      catch (java.io.IOException e) {
        System.err.println("Client: IO error");
        return;
      }
    
					//On ajoute une nouvelle ligne
					ZoneText.append("\n");
      }
      
				
			}
			
		});


    play.addActionListener(new ActionListener() {
			
			public void actionPerformed(ActionEvent event){
				
        //pour obtenir le contenu de la zone de text c'est-à-dire le JTextArea
        String text = getZoneText().getText();

        //Divise le texte en lignes en utilisant le caractère de saut de ligne
        String[]lines = text.split("\\n");

       //pour lire dans la zone de text
       BufferedReader cin = new BufferedReader(new StringReader(text));
    
    
      if(lines.length>0){
        try {
        if(cin.readLine()!=null){
        String request = "play "+lines[lines.length-1];
        String response = send(request);

        //affichage de la réponse dddans     la zone dde text
        getZoneText().append("\n Response: " + response);
        }
      }
      catch (java.io.IOException e) {
        System.err.println("Client: IO error");
        return;
      }
    
					//On ajoute une nouvelle ligne
					ZoneText.append("\n");
      }
      
				
			}
			
		});

		//methode pour gérer les évenements en utilisant les lamda
		exist.addActionListener(event-> System.exit(0));
		
		//methode pour gérer les évenements en utilisant les classes imbriquée
		searchMedia.addActionListener(new searchMultimedia());
		
		// pour rendre rouge le boutton exist
		
		exist.addMouseListener(new MouseAdapter() {
			
      //lorsque la souris n'est pas sur le boutton exist
			public void mouseExited(MouseEvent e) {
				exist.setForeground(Color.BLACK);
				
			}
			
      //lorsque la souris est sur le boutton exist
			public void mouseEntered(MouseEvent e) {
				
				exist.setForeground(Color.RED);
			}
			
		});
		
		
		
		// une barre de défilement au cas ou le text dépasse 
		JScrollPane scrolcontent = new JScrollPane(ZoneText);
		add(scrolcontent, BorderLayout.CENTER);
		
		// un JPanel pour contenir les trois bouttons
		JPanel contentPane = new JPanel() ;
		
		// ajout des bouttons au JPanel
		contentPane.add(searchGroupe);
		contentPane.add(searchMedia);
    contentPane.add(play);
    contentPane.add(exist);
		
		// positionnement du JPanel dans la zone sud de la fenêtre
		add(contentPane, BorderLayout.SOUTH);
		
		
		// pour confirmer la ferméture de la fenêtre
		
		addWindowListener(new WindowAdapter() {
			
			public void windowClosing(WindowEvent e) {
				
				int ClickedButton = JOptionPane.showConfirmDialog(Client.this, "Êtes-vous sûre de vouloir quitter?","exist",
						JOptionPane.YES_NO_OPTION);
				
				if(ClickedButton == JOptionPane.YES_OPTION) {
				 Client.this.dispose();
				}
			}
		});
		
		//Construction et Injection de la barre de menu
		setJMenuBar(createMenuBar());
		
		setLocationRelativeTo(null);
		pack();
		

    try {
      sock = new java.net.Socket(host, port);
    }
    catch (java.net.UnknownHostException e) {
      ZoneText.append("Client: Couldn't find host "+host+":"+port);
      throw e;
    }
    catch (java.io.IOException e) {
      ZoneText.append("Client: Couldn't reach host "+host+":"+port);
      throw e;
    }
    
    try {
      input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
      output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
    }
    catch (java.io.IOException e) {
      ZoneText.append("Client: Couldn't open input or output streams");
      throw e;
    }
    
    
  }
  	
 // Methode de construction de la barre de menu
	private JMenuBar createMenuBar() {
		// Creation de la barre d'outil
		JToolBar contentTool = new JToolBar();
		
		// positionnement de la barre d'outil dans la zone nord de la fenêtre principale
		add(contentTool, BorderLayout.NORTH);
		
		//Ajout des actions qui sont les intances des sous-classes de AbstractAction
		contentTool.add(searchGroupe_);
		contentTool.add(searchMedia_);
    contentTool.add(play_);
    contentTool.add(exist_);
		

		// Creation du menu déroulant
		JMenu menuFile = new JMenu("File");
		
		//Ajout des actions qui sont les intances des sous-classes de AbstractAction
		menuFile.add(searchGroupe_);
		menuFile.add(searchMedia_);
    menuFile.add(play_);
    menuFile.add(exist_);
		
		//Creation de la barre de menus
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(menuFile);
		menuBar.add(contentTool);
		System.setProperty("apple.laf.useScreenMenuBar", "true");
		return menuBar;
	}



	private class searchMultimedia implements ActionListener{
		
		public void actionPerformed(ActionEvent event){
				
        //pour obtenir le contenu de la zone de text c'est-à-dire le JTextArea
        String text = getZoneText().getText();

        //Divise le texte en lignes en utilisant le caractère de saut de ligne
        String[]lines = text.split("\\n");

       //pour lire dans la zone de text
       BufferedReader cin = new BufferedReader(new StringReader(text));
    
    
      if(lines.length>0){
        try {
        if(cin.readLine()!=null){
        String request = "searchMedia "+lines[lines.length-1];
        String response = send(request);

        //affichage de la réponse dddans     la zone dde text
        getZoneText().append("\n Response: " + response);
        }
      }
      catch (java.io.IOException e) {
        System.err.println("Client: IO error");
        return;
      }
    
					//On ajoute une nouvelle ligne
					ZoneText.append("\n");
      }
      
				
			}
	}

	private class ButtonSearchG extends AbstractAction{
		
		public ButtonSearchG(String name) {super(name);}
	
		private static final long serialVersionUID = 2L;
		
		public void actionPerformed(ActionEvent event){
				
        //pour obtenir le contenu de la zone de text c'est-à-dire le JTextArea
        String text = getZoneText().getText();

        //Divise le texte en lignes en utilisant le caractère de saut de ligne
        String[]lines = text.split("\\n");

       //pour lire dans la zone de text
       BufferedReader cin = new BufferedReader(new StringReader(text));
    
    
      if(lines.length>0){
        try {
        if(cin.readLine()!=null){
        String request = "searchGroupe "+lines[lines.length-1];
        String response = send(request);

        //affichage de la réponse dddans     la zone dde text
        getZoneText().append("\n Response: " + response);
        }
      }
      catch (java.io.IOException e) {
        System.err.println("Client: IO error");
        return;
      }
    
					//On ajoute une nouvelle ligne
					ZoneText.append("\n");
      }
      
				
			}
	}
	
   private class ButtonSearchM extends AbstractAction{
		
		public ButtonSearchM(String name) {super(name);}
	
		private static final long serialVersionUID = 3L;
		
		public void actionPerformed(ActionEvent event){
				
        //pour obtenir le contenu de la zone de text c'est-à-dire le JTextArea
        String text = getZoneText().getText();

        //Divise le texte en lignes en utilisant le caractère de saut de ligne
        String[]lines = text.split("\\n");

       //pour lire dans la zone de text
       BufferedReader cin = new BufferedReader(new StringReader(text));
    
    
      if(lines.length>0){
        try {
        if(cin.readLine()!=null){
        String request = "searchMedia "+lines[lines.length-1];
        String response = send(request);

        //affichage de la réponse dddans     la zone dde text
        getZoneText().append("\n Response: " + response);
        }
      }
      catch (java.io.IOException e) {
        System.err.println("Client: IO error");
        return;
      }
    
					//On ajoute une nouvelle ligne
					ZoneText.append("\n");
      }
      
				
			}
	}

  private class ButtonExist extends AbstractAction{
	
	public ButtonExist(String name) {super(name);}

	private static final long serialVersionUID = 4L;
	
	public void actionPerformed(ActionEvent event){	
		System.exit(0);
}	
}

private class ButtonPlay extends AbstractAction{

    public ButtonPlay(String name) {super(name);}
    private static final long serialVersionUID = 5L;

    public void actionPerformed(ActionEvent event){
				
        //pour obtenir le contenu de la zone de text c'est-à-dire le JTextArea
        String text = getZoneText().getText();

        //Divise le texte en lignes en utilisant le caractère de saut de ligne
        String[]lines = text.split("\\n");

       //pour lire dans la zone de text
       BufferedReader cin = new BufferedReader(new StringReader(text));
    
    
      if(lines.length>0){
        try {
        if(cin.readLine()!=null){
        String request = "play "+lines[lines.length-1];
        String response = send(request);

        //affichage de la réponse dddans     la zone dde text
        getZoneText().append("\n Response: " + response);
        }
      }
      catch (java.io.IOException e) {
        System.err.println("Client: IO error");
        return;
      }
    
					//On ajoute une nouvelle ligne
					ZoneText.append("\n");
      }
    }
  }
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  ///
  /// Envoie une requete au server et retourne sa reponse.
  /// Noter que la methode bloque si le serveur ne repond pas.
  ///
  public String send(String request) {
    // Envoyer la requete au serveur
    try {
      request += "\n";  // ajouter le separateur de lignes
      output.write(request, 0, request.length());
      output.flush();
    }
    catch (java.io.IOException e) {
      System.err.println("Client: Couldn't send message: " + e);
      return null;
    }
    
    // Recuperer le resultat envoye par le serveur
    try {
      return input.readLine();
    }
    catch (java.io.IOException e) {
      System.err.println("Client: Couldn't receive message: " + e);
      return null;
    }
  }
  
}