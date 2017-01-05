#include <iostream>
#include <math.h>
#include <time.h>
#include <cstdlib>
using namespace std;

float set_maneuverability(short _health, short _max_health, float _max_maneuverability)
{
    return 0.2f * _max_maneuverability * ceil(5 * (double(_health) / double(_max_health)));
}

float set_morale_effect()
{
    return 0.0025f * (rand() % 101) + 1.0f;
}

float set_morale_effect(short _morale)
{
    if (_morale > 0)
        return 1.0f + 0.005f * _morale;
    else
        return 1.0f;
}

int main()
{
    srand(time(0));

    float recharge_1;
    float recharge_2;
    float round_ammo_shot_1;
    float round_ammo_shot_2;
    float round_damage_1;
    float round_damage_2;
    
    short morale = 75;
    float morale_effect_1 = set_morale_effect(morale);
    cout << "Player morale effect: " << morale_effect_1 << endl;
    float morale_effect_2 = set_morale_effect();
    cout << "NPC morale effect: " << morale_effect_2 << endl;
    cout << endl;
    
    short ship1_crew = 177;
    short ship1_max_crew = 177;
    short ship2_crew = 448;
    short ship2_max_crew = 448;
    
    short ship1_cannons = 16;
    short ship2_cannons = 32;
    
    short ship1_ammo = ship1_cannons * 5;
    short ship2_ammo = ship2_cannons * 5;
    
    short ship1_health = 135;
    short ship1_max_health = 115;
    short ship2_health = 280;
    short ship2_max_health = 280;
    
    float ship1_maneuverability;
    float ship1_max_maneuverability = 0.65; 
    float ship2_maneuverability;
    float ship2_max_maneuverability = 0.3; 
    
    int round_number = 0;
    bool run = true;
    
    while (run)
    {
        round_number ++;
        cout << "Round: " << round_number << endl;
        cout << endl;
        
        // set and normalize recharge speed (higher recharging speed - more fires in round)
        recharge_1 = morale_effect_1 * float(ship1_crew) / (ship1_cannons * ship1_max_crew);
        recharge_2 = morale_effect_2 * float(ship2_crew) / (ship2_cannons * ship2_max_crew);
        if (recharge_1 > recharge_2)
        {
            recharge_2 /= recharge_1;
            recharge_1 = 1.0f;
        } else
        {
            recharge_1 /= recharge_2;
            recharge_2 = 1.0f;
        }
        
        cout << "Player recharge: " << recharge_1 << endl;
        cout << "NPC recharge: " << recharge_2 << endl;
        cout << endl;
    
        // calculate amount of cannonballs shot and reset amount of ammo
        round_ammo_shot_1 = short(float(ship1_cannons*recharge_1*0.5));
        round_ammo_shot_2 = short(float(ship2_cannons*recharge_2*0.5));
        if (ship1_ammo >= round_ammo_shot_1)
            ship1_ammo -= round_ammo_shot_1;
        else
            ship1_ammo = 0;
        if (ship2_ammo >= round_ammo_shot_2)
            ship2_ammo -= round_ammo_shot_2;
        else
            ship2_ammo = 0;
        
        cout << "Player round ammo shot: " << round_ammo_shot_1 << endl;
        cout << "NPC round ammo shot: " << round_ammo_shot_2 << endl;
        cout << endl;
    
        // reset maneuverability
        ship1_maneuverability = set_maneuverability(ship1_health, ship1_max_health, ship1_max_maneuverability);
        ship2_maneuverability = set_maneuverability(ship2_health, ship2_max_health, ship2_max_maneuverability);
        
        cout << "Player maneuverability: " << ship1_maneuverability << endl;
        cout << "NPC maneuverability: " << ship2_maneuverability << endl;
        cout << endl;
    
        // calculate damage
        round_damage_1 = short(3.0 * double(round_ammo_shot_1) * (1 - 0.5*ship2_maneuverability) *
                               0.01*(rand()%31 + 70.0) * morale_effect_1);
        round_damage_2 = short(3.0 * double(round_ammo_shot_2) * (1 - 0.5*ship1_maneuverability) *
                               0.01*(rand()%31 + 70.0) * morale_effect_2);
                               
        cout << "Player round damage: " << round_damage_1 << endl;
        cout << "NPC round damage: " << round_damage_2 << endl;
        cout << endl;                    
    
        // change health
        ship1_health -= round_damage_2;
        ship2_health -= round_damage_1;
    
        // change crew
        ship1_crew = short(float(ship1_crew) *
                         (1 - 0.3f * float(round_damage_2)/ship1_max_health));
        ship2_crew = short(float(ship2_crew) *
                         (1 - 0.3f * float(round_damage_1)/ship2_max_health));
    
        // change amount of cannons
        if (ship1_cannons >= 10)
            ship1_cannons -= rand() % 3;
        if (ship1_cannons >= 10)
        ship2_cannons -= rand() % 3;
        
        cout << "Player:" << endl;
        cout << "Health: " << ship1_health << endl;
        cout << "Crew: " << ship1_crew << endl;
        cout << "Ammo: " << ship1_ammo << endl;
        cout << "Cannons: " << ship1_cannons << endl;
        cout << endl;
        
        cout << "NPC:" << endl;
        cout << "Health: " << ship2_health << endl;
        cout << "Crew: " << ship2_crew << endl;
        cout << "Ammo: " << ship2_ammo << endl;
        cout << "Cannons: " << ship2_cannons << endl;
        cout << endl;
        
        if (ship2_health < 0.2 * ship2_max_health || !ship2_ammo)
        {
            cout << "NPC beaten in " << round_number << "th round."<< endl;
            run = false;
        } else
        if (ship1_health < 0.2 * ship1_max_health || !ship1_ammo)
        {
            cout << "Player run away in " << round_number << "th round." << endl;
            run = false;
        }
    }
   
   return 0;
}