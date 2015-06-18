# KGuardiant
Repository for final project grade cait

KGuardiant is an OpenSource application wich develop an intelligent survilliance system. 
Built on Qt and OpenCV is modular an solid in its desing.

KGuardiant system involves two systems, a server (KGuardiantServer) and a client (KGuardiantClient):

 - KGuardiantClient: With this app, you can connect to one or more instances of KGuardiantServer, and manage diferent
 rexions of interst (ROI), when the system detects movement in a roi, it fires an Alarm !!!.
 
 - KGuardiantServer: With this app, you can deploy a full multi-thread TCP server with survilliance features,
 each instance of KGuardiantServer, handle various connection to clients (KGuardiantClients). To perform the 
 movement detection, the system use the Gaussian Mixture Model, with a BackgroundSubstraction.
 
 
