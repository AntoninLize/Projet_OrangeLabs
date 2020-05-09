# Ces programmes ne sont exécutables que dans un Workspace prédéfini

**Commandes importantes :**

````
$roscore : permet de lancer ROS
````
````
$catkin_make --only-pkg-with-deps test  : permet de compiler seulement le package "test"
dans un workspaceROS
````
````
$rosrun rosserial_python serial_node.py /dev/ttyACM0 : Permet de lancer le ROS
Arduino en indiquant le bon port. Il faut donc brancher l'Arduino sur un port du
NUC ou de l'ordinateur de test
````
````
$rosrun test talker  : permet de lancer le node qui envoie les cmds moteurs
````
````
$rostopic echo cmd_motor  : permet d'écouter le topic cmd_motor contenant la consigne moteur
````
````
$rostopic echo value_encoder  : permet d'écouter le topic value_encoder contenant la veleur encodeur
````
