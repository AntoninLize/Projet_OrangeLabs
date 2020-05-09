#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
// Attention à bien inclure chaque type de message !
#define RATE 20
int main(int argc, char **argv){
    // Initialisation du node : le troisième argument est son nom
    ros::init(argc, argv, "talker");

    // Connexion au master et initialisation du NodeHandle qui permet d’avoir accès aux topics et services
    ros::NodeHandle n;

    // Création du publisher avec
    // - le type du message
    // - le nom du topic
    // - la taille du buffer de message à conserver en cas de surchage
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("cmd_motor", 1000);

    // La durée de la pause (voir le sleep)
    ros::Rate loop_rate(RATE);

    // Boucle tant que le master existe (ros::ok())
    while (ros::ok()){
        // création d’un message de type String
        std_msgs::String msg;
        
        // affectation la valeur "cmd_motor" au champ data
        msg.data = "100";

        // publication du message
        chatter_pub.publish(msg);

        // fonction utile seulement dans le cas de l’utilisation d’un subscriver ou d’un server
        ros::spinOnce();
        
        // Pause
        loop_rate.sleep();

        // Il est également possible d’utiliser des Timers qui fonctionnent par interruption
        // http://wiki.ros.org/roscpp_tutorials/Tutorials/Timers
        }
    return 0;
}