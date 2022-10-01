//
// Created by cedric on 2022-10-01.
//

#include "Alive.h"

template <typename T>
void Alive<T>::heal(T amount) {
    health += amount;

    if(health > maxHealth)
        health = maxHealth;
}

template<typename T>
void Alive<T>::damage(T amount) {
    health -= amount;

    if(health < static_cast<T>(0.0))
        health = static_cast<T>(0.0);
}

template<typename T>
T Alive<T>::get_health() const {
    return health;
}

template <typename T>
bool Alive<T>::is_dead() const {
    return health <= static_cast<T>(0.0);
}