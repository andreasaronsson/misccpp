#include <Thread.h>
#include <iostream>


using namespace std;

int main()
{
    cerr << "\nIT's ALIVE" << endl;
    
    Thread player;
    cerr << "\nInstances: " << player.GetInstances() << endl;
    player.Start();
    cerr << "\nInstances: " << player.GetInstances() << endl;
    player.Run();
    cerr << "\nInstances: " << player.GetInstances() << endl;
    Thread listener;
    listener.Start();
    listener.Run();
    listener.Sleep(100);
    player.Stop();
    cerr << "\nInstances: " << player.GetInstances() << endl;
    player.~Thread();
    cerr << "\nInstances: " << player.GetInstances() << endl;
    cerr << "\nIT's DEAD" << endl;
    exit(0);

}


int function(int one) 
{
    
}
    
